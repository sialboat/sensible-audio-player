#pragma once
#ifndef TRANSPORT_CONTROLS_H
#define TRANSPORT_CONTROLS_H

#include <JuceHeader.h>
#include "Audio/AudioEngine.h"
#include "Utils/Types.h"

class TransportControls : public juce::Component,
                          public juce::ChangeListener,
                          public TransportStateListener
{
public:
    TransportControls(AudioEngine& a, TransportStateManager& t);
    ~TransportControls() override;

    void resized() override;

    void onTransportStateChange(TransportState state) override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override {}

    void openButtonClicked();
    void stopButtonClicked();
    void playButtonClicked();
    void pauseButtonClicked();
    void loopButtonClicked();

private:
    AudioEngine& audioEngine;
    TransportStateManager& transportState;

    juce::GroupComponent playerControls;
    juce::DrawableButton openButton;
    juce::DrawableButton playButton;
    juce::DrawableButton pauseButton;
    juce::DrawableButton stopButton;
    // juce::ToggleButton loopButton;

    std::unique_ptr<juce::FileChooser> chooser;
    juce::String fileName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportControls)
};

#endif