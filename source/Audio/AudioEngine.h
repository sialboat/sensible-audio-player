#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <JuceHeader.h>
#include "Types.h"

class AudioEngine : public juce::AudioAppComponent,
                    public juce::ChangeListener,
                    public juce::ChangeBroadcaster
{
public:
    AudioEngine();
    ~AudioEngine() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    bool loadFile(juce::File f);
    void changeState(TransportState newState);
    TransportState getState() { return state; }

    juce::AudioTransportSource& getTransportSource() noexcept 
    { 
        return transportSource;
    }
    
    double getCurrentSeconds() { 
        double temp = transportSource.getCurrentPosition();
        if(temp != currentSeconds)
            currentSeconds = temp;
        return currentSeconds;
    }
    double getTotalSeconds() { return totalSeconds; }

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    TransportState state;

    double currentSeconds;
    double totalSeconds;
};

#endif