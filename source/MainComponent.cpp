#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : transportComponent(audioEngine)
{
    addAndMakeVisible(transportComponent);
    // otherDeviceManager.initialise(2, 2, nullptr, true);
    // waveViewer.setRepaintRate(30); // rate at which it will redraw itself
    // waveViewer.setBufferSize(256); // how many samples it will draw
    
    // audioSettings.reset(new AudioDeviceSelectorComponent(otherDeviceManager, 
        // 0, MAX_INPUT_CHANNELS, 0, MAX_OUTPUT_CHANNELS, true, true, true, true));
    // addAndMakeVisible(audioSettings.get());

    // addAndMakeVisible(&waveViewer);

    // addAndMakeVisible(&openButton);
    // openButton.setButtonText("Open");
    // openButton.onClick = [this] { openButtonClicked(); };
    
    // addAndMakeVisible(&playButton);
    // playButton.setButtonText("Play");
    // playButton.onClick = [this] { playButtonClicked(); };
    // playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    // playButton.setEnabled(false);

    // addAndMakeVisible(&stopButton);
    // stopButton.setButtonText("Stop");
    // stopButton.onClick = [this] { stopButtonClicked(); };
    // stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    // stopButton.setEnabled(false);

    // find out how to enable other formats silas
    // formatManager.registerBasicFormats(); // create readers for wav and aiff
                                                   // state changes

    // setAudioChannels(2, 2);                     // forgot this lmao

    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}
//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setFont (juce::FontOptions (16.0f));
    g.setColour (juce::Colours::white);
    // g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    transportComponent.setBounds(getLocalBounds().reduced(10));
    // openButton.setBounds(10, 10, getWidth() - 20, 20);
    // playButton.setBounds(10, 40, getWidth() - 20, 20);
    // stopButton.setBounds(10, 70, getWidth() - 20, 20);
    // audioSettings->setBounds(10, 100, getWidth() - 20, 20);

    // waveViewer.setBounds(10, audioSettings->getBottom() + 30, getWidth() - 20, 20);
}