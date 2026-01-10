#pragma once
#ifndef TRANSPORT_COMPONENT_H
#define TRANSPORT_COMPONENT_H

#include <JuceHeader.h>
#include "Audio/AudioEngine.h"
#include "Types.h"

// label object to interface that displays current time position of 
    // audioTransportSource object.
    // use AudioTransportSource::getCurrentPosition() to obtain position
    // Make MainContentComponent inherit from Timer class
    // perform periodic timer updatses in timerCallback()
    // relativeTime class can also be used to convert raw time in seconds 
    // for minutes, seconds, milliseconds.

class TransportComponent : public juce::Component,
                           public juce::ChangeListener,
                           public juce::HighResolutionTimer
{
public:
    TransportComponent(AudioEngine& e); 
    ~TransportComponent() override;

    void hiResTimerCallback() override;

    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void openButtonClicked();
    void stopButtonClicked();
    void playButtonClicked();
    void changeState(TransportState newState);
    void updateButtons();

private:

    juce::String convertTime(double r);

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    juce::Label duration;

    std::unique_ptr<juce::FileChooser> chooser;

    AudioEngine& audioEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportComponent)
};

#endif