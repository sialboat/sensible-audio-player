#include "MainComponent.h"

/* 
    MainComponent.cpp

    anything that needs the interaction of multiple components 
    (audioEngine and transportDisplay, etc.) should be implemented 
    here.
*/ 

//==============================================================================
MainComponent::MainComponent() : audioEngine(transportState), 
    transportComponent(audioEngine, transportState)
{
    // addAndMakeVisible(transportComponent);

    // audioEngine.addChangeListener(this);
    // audioEngine.getTransportSource.addChangeListner(this);

    // the callback lambdas go here


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

    setSize (APP_WIDTH, APP_HEIGHT);
}

MainComponent::~MainComponent()
{
    // audioEngine.removeChangeListener(this);
    // audioEngine.getTransportSource().removeChangeListener(this);
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

bool MainComponent::keyPressed(const juce::KeyPress& k)
{
    if(k == juce::KeyPress::spaceKey)
    {
        if(audioEngine.isPaused())
            transportComponent.playButtonClicked();
        else
            transportComponent.pauseButtonClicked();
        return true;
    }
    if(k == juce::KeyPress::escapeKey)
    {
        transportComponent.stopButtonClicked();
    }
    return false; // we shouldn't get here.
}