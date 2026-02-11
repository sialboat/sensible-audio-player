#pragma once

#ifndef TRANSPORT_DISPLAY_H
#define TRANSPORT_DISPLAY_H

#include <JuceHeader.h>
#include "Audio/AudioEngine.h"
#include "UI/TransportControls.h"
#include "Utils/TransportStateListener.h"
#include "Utils/TransportStateManager.h"
#include "Utils/Types.h"

class TransportDisplay : public juce::Component,
                         public TransportStateListener,
                         public juce::HighResolutionTimer
{
public:
    TransportDisplay(TransportStateManager& t);
    ~TransportDisplay() override;

    void hiResTimerCallback() override;

    void resized() override;

    void onTransportStateChange(TransportState s) override;
    void setDuration(juce::String s) { duration.setText(s, juce::dontSendNotification); }
    void updateTime(double c, double t)
    {
        currentSeconds = c;
        totalSeconds = t;
    }

private:
    TransportStateManager& transportState;

    juce::GroupComponent transportInfo;
    juce::Label duration;
    juce::Label nowPlaying;
    juce::Slider songTransport;
    juce::Label loopingStatusText;

    juce::Label songGainLabel;
    juce::Slider songGain;

    double currentSeconds;
    double totalSeconds;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TransportDisplay)
};

#endif