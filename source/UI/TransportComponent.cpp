#include "TransportComponent.h"

TransportComponent::TransportComponent(AudioEngine& e, TransportStateManager& m) : audioEngine(e),
    transportDisplay(m), buttonControls(e, m), transportState(m)
{
    addAndMakeVisible(&buttonControls);
    addAndMakeVisible(&transportDisplay);
}

void TransportComponent::resized()
{
    buttonControls.setBounds(10, 10, TEST_CONTROLS_WIDTH, TEST_CONTROLS_HEIGHT);
    transportDisplay.setBounds(10, 30, TEST_CONTROLS_WIDTH, TEST_CONTROLS_HEIGHT);
    // openButton.setBounds(10, 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    // playButton.setBounds(openButton.getRight() + 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    // pauseButton.setBounds(10, playButton.getRight() + 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    // stopButton.setBounds(10, pauseButton.getRight() + 10, BUTTON_WIDTH, BUTTON_HEIGHT);
    // duration.setBounds(10, openButton.getBottom() + 20, BUTTON_WIDTH, BUTTON_HEIGHT);
    // nowPlaying.setBounds(10, duration.getBottom() + 20, DURATION_WIDTH, DURATION_HEIGHT);
    
    // songGainLabel.setBounds(10, nowPlaying.getBottom() + 20, 75, 25);
    // songGain.setBounds(10, songGainLabel.getBottom() + 10, 75, 75);
}
TransportComponent::~TransportComponent()
{
    // Not sure if something needs to go here or not.
    // audioEngine.removeChangeListener(this);
    // audioEngine.getTransportSource().removeChangeListener(this);
    // stopTimer();
}