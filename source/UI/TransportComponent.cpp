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

    audioEngine.addChangeListener(this);
    audioEngine.getTransportSource().addChangeListener(this);
    // duration("", "");
    addAndMakeVisible(duration);
    duration.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    duration.setColour(juce::Label::textColourId, juce::Colours::white);
    duration.setJustificationType(juce::Justification::centred);

    // transportSource.addChangeListener(this);
}

void TransportComponent::resized()
{
    openButton.setBounds(10, 10, getWidth() - 20, 20);
    playButton.setBounds(10, 40, getWidth() - 20, 20);
    stopButton.setBounds(10, 70, getWidth() - 20, 20);
    duration.setBounds(10, 110, getWidth() - 20, 20);
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
            stopTimer();
            break;
        case Starting:
            playButton.setEnabled(false);
            DBG("timer starting");
            break;
        case Playing:
            startTimer(DEFAULT_TIMER_INTERVAL_MS);
            stopButton.setEnabled(true);
            break;
        case Stopping:
            stopTimer();
            DBG("timer stopping");
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

void TransportComponent::timerCallback()
{
    juce::String totalTime = convertTime(audioEngine.getTotalSeconds());
    juce::String currentTime = convertTime(audioEngine.getCurrentSeconds());
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



// void TransportComponent::paint(juce::Graphics& g)
// {

// }

void TransportComponent::openButtonClicked()
{
    chooser = std::make_unique<juce::FileChooser> (
        "Select an audio file to play", juce::File{},
        "*.wav;*.aiff;*.aif;*.mp3");

    auto chooserFlags = juce::FileBrowserComponent::openMode 
                      | juce::FileBrowserComponent::canSelectFiles; 

    chooser->launchAsync (chooserFlags, [this] (const juce::FileChooser& fc)
    {
        auto file = fc.getResult();
        if(audioEngine.loadFile(file)) {
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