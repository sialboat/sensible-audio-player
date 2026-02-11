#pragma once

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include <JuceHeader.h>
#include "Utils/TransportStateManager.h"
#include "Utils/Types.h"

class AudioEngine : public juce::AudioAppComponent,
                    public juce::ChangeListener,
                    public juce::ChangeBroadcaster,
                    public TransportStateListener,
                    private juce::Value::Listener
{
public:
    AudioEngine(TransportStateManager& m);
    ~AudioEngine() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    bool loadFile(juce::File f);

    void onTransportStateChange(TransportState s) override; 

    juce::AudioTransportSource& getTransportSource() noexcept 
    { 
        return transportSource;
    }
    
    bool isPaused() { return paused; }
    double getCurrentSeconds() { return transportSource.getCurrentPosition(); }
    double getTotalSeconds() { return transportSource.getLengthInSeconds(); }
    float getGainValue() { return ((float) songGain.getValue()); }
    juce::Value& getSongGain() { return songGain; }

    void updateReaderSource(bool shouldLoop);

private:
    void valueChanged(juce::Value& value) override;

    TransportStateManager& transportState;

    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    // TransportState state;

    bool paused;

    [[maybe_unused]] double currentSeconds;
    double totalSeconds;
    [[maybe_unused]] double sampleRate;
    juce::Value songGain;
};

#endif