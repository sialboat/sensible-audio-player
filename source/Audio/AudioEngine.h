#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <JuceHeader.h>
#include "Types.h"

class AudioEngine : public juce::AudioAppComponent,
                    public juce::ChangeListener,
                    public juce::ChangeBroadcaster,
                    private juce::Value::Listener
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
    double getPlayheadSeconds() {
        return playheadSamples.load() / sampleRate;
    }
    bool isPaused() { return paused; }
    double getTotalSeconds() { return totalSeconds; }
    float getGainValue() { return ((float) songGain.getValue()); }
    juce::Value& getSongGain() { return songGain; }

private:
    void valueChanged(juce::Value& value) override;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    TransportState state;

    bool paused;

    double currentSeconds;
    double totalSeconds;
    std::atomic<uint64_t> playheadSamples;
    double sampleRate;
    juce::Value songGain;
};

#endif