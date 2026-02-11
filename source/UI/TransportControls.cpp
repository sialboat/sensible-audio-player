#include "TransportControls.h"

TransportControls::TransportControls(AudioEngine& e, TransportStateManager& t) : audioEngine(e), 
    transportState(t),
    openButton("Open", juce::DrawableButton::ButtonStyle::ImageFitted),
    playButton("Play", juce::DrawableButton::ButtonStyle::ImageFitted),
    pauseButton("Pause", juce::DrawableButton::ButtonStyle::ImageFitted),
    stopButton("Stop", juce::DrawableButton::ButtonStyle::ImageFitted)
{
    playerControls.addAndMakeVisible(&openButton);  
    openButton.onClick = [this] { openButtonClicked(); };

    playerControls.addAndMakeVisible(&playButton);
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled(false);

    playerControls.addAndMakeVisible(&stopButton);
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(false);

    playerControls.addAndMakeVisible(&pauseButton);
    pauseButton.onClick = [this] { pauseButtonClicked(); };
    pauseButton.setColour(juce::TextButton::buttonColourId, juce::Colours::blue);
    pauseButton.setEnabled(false);

    transportState.addListener(this);

    // playerControls.addAndMakeVisible(&loopButton);
    // loopButton.onClick = [this] { loopButtonClicked(); };

    addAndMakeVisible(&playerControls);
}

TransportControls::~TransportControls()
{
    transportState.removeListener(this);
}

void TransportControls::resized()
{
    openButton.setBounds(10, 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    // more here later
}

void TransportControls::onTransportStateChange(TransportState state)
{
    switch(state)
    {
        case Stopped:
            stopButton.setEnabled(false);
            playButton.setEnabled(true);
            pauseButton.setEnabled(false);
            break;
        case Starting:
            playButton.setEnabled(false);
            break;
        case Playing:
            stopButton.setEnabled(true);
            pauseButton.setEnabled(true);
            playButton.setEnabled(false);
            break;
        case Stopping:
            break;
        case Paused:
            playButton.setEnabled(true);
            pauseButton.setEnabled(false);
            stopButton.setEnabled(true);
            break;
        case Looping:
            break;
        default:
            break;
    }
}

void TransportControls::openButtonClicked()
{
    // rewrite this such that it works with the AudioFile class
    // chooser = std::make_unique<juce::FileChooser> (
    //     "Select an audio file to play", juce::File{},
    //     "*.wav;*.aiff;*.aif;*.mp3;*.m4a"
    // );

    // auto chooserFlags = juce::FileBrowserComponent::openMode
    //                     | juce::FileBrowserComponent::canSelectFiles;
    
    // auto safePointer = juce::Component::SafePointer<TransportControls>(this);

    // chooser->launchAsync(chooserFlags, [safePointer](const juce::FileChooser& fc)
    // {
    //     if(!safePointer)
    //         return;
    //     safePointer->onFileSelected(fc.getResult());
    // });
}

void TransportControls::stopButtonClicked()
{
    // this belongs in the TransportDisplay part.
    transportState.changeState(Stopping);
}

void TransportControls::playButtonClicked()
{
    transportState.changeState(Starting);
}

void TransportControls::pauseButtonClicked()
{
    transportState.changeState(Paused);
}

void TransportControls::loopButtonClicked()
{
    transportState.changeState(Looping);
    // audioEngine.updateReaderSource(loopButton.getToggleState());
    // if(loopButtonClicked)
    //     loopButtonClicked();
}

// juce::String convertTime(double r)
// {
//     TIME_VALUES values = getTimeValues(r);

//     juce::String out;
//     if (values.hours > 0)
//         out = juce::String::formatted("%d : %02d : %02d . %03d",
//             values.hours, values.minutes, values.seconds, values.milliseconds);
//     else
//         out = juce::String::formatted("%02d : %02d . %03d", 
//             values.minutes, values.seconds, values.milliseconds);

//     return out;
// }
