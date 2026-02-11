#pragma once
#ifndef TRANSPORT_COMPONENT_H
#define TRANSPORT_COMPONENT_H

#include <JuceHeader.h>
#include "Audio/AudioEngine.h"
#include "UI/TransportControls.h"
#include "UI/TransportDisplay.h"
#include "Utils/Types.h"

// label object to interface that displays current time position of 
    // audioTransportSource object.
    // use AudioTransportSource::getCurrentPosition() to obtain position
    // Make MainContentComponent inherit from Timer class
    // perform periodic timer updatses in timerCallback()
    // relativeTime class can also be used to convert raw time in seconds 
    // for minutes, seconds, milliseconds.

class TransportComponent : public juce::Component,
                           public juce::ChangeListener
{
public:
    TransportComponent(AudioEngine& e, TransportStateManager& m); 
    ~TransportComponent() override;
    
    void resized() override;
    void changeListenerCallback(juce::ChangeBroadcaster* b) override {}
    void updateTime(double d, double t) { transportDisplay.updateTime(d, t); }
    // juce::String getCurrentFileDuration() { return currentFileDuration; }

    void openButtonClicked() { buttonControls.openButtonClicked(); }
    void stopButtonClicked() { buttonControls.stopButtonClicked(); }
    void playButtonClicked() { buttonControls.playButtonClicked(); }
    void pauseButtonClicked() { buttonControls.pauseButtonClicked(); }
    void loopButtonClicked() { buttonControls.loopButtonClicked(); }

private:

    AudioEngine& audioEngine;
    TransportControls buttonControls;
    TransportDisplay transportDisplay;
    TransportStateManager& transportState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportComponent)
};

#endif