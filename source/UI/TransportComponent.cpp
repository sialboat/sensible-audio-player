#include "TransportComponent.h"

TransportComponent::TransportComponent(AudioEngine& e) : audioEngine(e)
{
    addAndMakeVisible(&openButton);
    openButton.setButtonText("Open");
    openButton.onClick = [this] { openButtonClicked(); };

    addAndMakeVisible(&playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { 
        playButtonClicked();
        // audioEngine.changeState(Starting); 
    };
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled(false);

    addAndMakeVisible(&stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { 
        stopButtonClicked();
        // audioEngine.changeState(Stopping); 
    };
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(false);

    addAndMakeVisible(&pauseButton);
    pauseButton.setButtonText("Pause");
    pauseButton.onClick = [this] {
        pauseButtonClicked();
    };
    pauseButton.setColour(juce::TextButton::buttonColourId, juce::Colours::blue);
    pauseButton.setEnabled(false);

    audioEngine.addChangeListener(this);
    audioEngine.getTransportSource().addChangeListener(this);
    // duration("", "");
    addAndMakeVisible(&duration);
    duration.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    duration.setColour(juce::Label::textColourId, juce::Colours::white);
    duration.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(&nowPlaying);
    nowPlaying.setJustificationType(juce::Justification::centred);
    nowPlaying.setText("No Audio File Selected.", juce::dontSendNotification);

    addAndMakeVisible(&songGain);
    addAndMakeVisible(&songGainLabel);
    songGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    songGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, 
        false, 75, 25
    );
    songGain.getProperties().set("drawFromMiddle", true);
    songGain.setRotaryParameters(1.25f * juce:: MathConstants<float>::pi, 
        2.75f * juce::MathConstants<float>::pi, true
    );
    songGain.setTextValueSuffix("dB");
    songGain.setRange(-12, 12, 0.01);
    songGain.setDoubleClickReturnValue(true, 0);

    // the non-apvts way of doing it
    songGain.getValueObject().referTo(audioEngine.getSongGain());

    songGainLabel.setText("Volume", juce::dontSendNotification);
    songGainLabel.setJustificationType(juce::Justification::horizontallyCentred);
    songGainLabel.attachToComponent(&songGain, false);
}

void TransportComponent::resized()
{
    openButton.setBounds(10, 10, getWidth() - 20, 20);
    playButton.setBounds(10, 40, getWidth() - 20, 20);
    pauseButton.setBounds(10, 70, getWidth() - 20, 20);
    stopButton.setBounds(10, 100, getWidth() - 20, 20);
    duration.setBounds(10, 130, getWidth() - 20, 20);
    nowPlaying.setBounds(10, 160, getWidth() - 20, 20);
    songGainLabel.setBounds(10, 190, 75, 25);
    songGain.setBounds(10, songGainLabel.getBottom() + 10, 75, 75);
}
TransportComponent::~TransportComponent()
{
    // Not sure if something needs to go here or not.
    audioEngine.removeChangeListener(this);
    audioEngine.getTransportSource().removeChangeListener(this);
    stopTimer();
}

void TransportComponent::updateButtons()
{
    switch(audioEngine.getState())
    {
        case Stopped:
            stopButton.setEnabled(false);
            playButton.setEnabled(true);
            pauseButton.setEnabled(false);
            nowPlaying.setText(juce::String("Stopped: ") + fileName,
                juce::dontSendNotification
            );
            stopTimer();
            break;
        case Starting:
            playButton.setEnabled(false);
            DBG("timer starting");
            break;
        case Playing:
            startTimer(DEFAULT_TIMER_INTERVAL_MS);
            stopButton.setEnabled(true);
            pauseButton.setEnabled(true);
            playButton.setEnabled(false);
            nowPlaying.setText(juce::String("Now Playing: ") + fileName,
                juce::dontSendNotification
            );
            break;
        case Stopping:
            stopTimer();
            DBG("timer stopping");
            break;
        case Paused:
            playButton.setEnabled(true);
            pauseButton.setEnabled(false);
            stopButton.setEnabled(true);
            stopTimer();
            break;
        // default:
        //     break;
    }
}

void TransportComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if(source == &audioEngine || source == &audioEngine.getTransportSource())
        updateButtons();
}

void TransportComponent::hiResTimerCallback()
{
    juce::String totalTime = convertTime(audioEngine.getTotalSeconds());
    juce::String currentTime = convertTime(audioEngine.getPlayheadSeconds());
    juce::String toPrint = currentTime + " / " + totalTime;
    duration.setText(toPrint, juce::dontSendNotification);
    // juce::String toPrint = juce::String(currentSeconds, 1) + " / " + juce::String(totalSeconds);
    // duration.setText(toPrint, juce::dontSendNotification);
    // duration.setText("00.00/00.00", juce::dontSendNotification);
    // repaint();
}

juce::String TransportComponent::convertTime(double r)
{
    TIME_VALUES values = getTimeValues(r);

    int seconds = static_cast<int>(values.seconds);

    juce::String out;

    if (values.hours > 0)
        out = juce::String(values.hours) + " : " +
              juce::String(values.minutes).paddedLeft('0', 2) + ":" +
              juce::String(seconds).paddedLeft('0', 2);
    else
        out = juce::String(values.minutes) + " : " +
              juce::String(seconds).paddedLeft('0', 2);

    return out;
}

void TransportComponent::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser> (
        "Select an audio file to play", juce::File{},
        "*.wav;*.aiff;*.aif;*.mp3;*.m4a");

    auto chooserFlags = juce::FileBrowserComponent::openMode 
                      | juce::FileBrowserComponent::canSelectFiles; 

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
    {
        auto file = fc.getResult();
        if(audioEngine.loadFile(file)) {
            fileName = file.getFileName();
            playButton.setEnabled(true);
            duration.setText(
                convertTime(audioEngine.getCurrentSeconds()) + " / " + 
                convertTime(audioEngine.getTotalSeconds()),
                juce::dontSendNotification
            );
        }
    });
}

void TransportComponent::stopButtonClicked()
{
    duration.setText(convertTime(0) + " / " + 
            convertTime(audioEngine.getTotalSeconds()),
            juce::dontSendNotification
    );
    audioEngine.changeState(Stopping);
}

void TransportComponent::playButtonClicked()
{
    audioEngine.changeState(Starting); 
}

void TransportComponent::pauseButtonClicked()
{
    audioEngine.changeState(Paused);
}

bool TransportComponent::keyPressed(const juce::KeyPress& key)
{
    if(key == juce::KeyPress::spaceKey)
    {
        if(audioEngine.isPaused())
            playButtonClicked();
        else
            pauseButtonClicked();
        return true;
    }
    if(key == juce::KeyPress::escapeKey)
    {
        stopButtonClicked();
    }
    return false; // we shouldn't get here.
}

// void TransportComponent::valueChanged(juce::Value& value)
// {

// }