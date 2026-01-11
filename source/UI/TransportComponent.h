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
    bool keyPressed(const juce::KeyPress& k) override;

    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void changeState(TransportState newState);
    void updateButtons();

private:
    void openButtonClicked();
    void stopButtonClicked();
    void playButtonClicked();
    void pauseButtonClicked();

    juce::String convertTime(double r);

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton pauseButton;
    juce::TextButton stopButton;

    juce::Label duration;
    juce::Label nowPlaying;

    juce::Slider songTransport;

    juce::Label songGainLabel;
    juce::Slider songGain;

    std::unique_ptr<juce::FileChooser> chooser;
    juce::String fileName;

    AudioEngine& audioEngine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportComponent)
};

#endif