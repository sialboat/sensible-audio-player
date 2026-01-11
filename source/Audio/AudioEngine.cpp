#include "AudioEngine.h"

AudioEngine::AudioEngine() : state(Stopped), totalSeconds(0), currentSeconds(0),
    paused(false), playheadSamples{0}, sampleRate(DEFAULT_SAMPLE_RATE), songGain{0.0f}
{
    formatManager.registerBasicFormats(); // create readers for wav and aiff
    transportSource.addChangeListener(this);
    songGain.addListener(this);
    setAudioChannels(2, 2);
}

AudioEngine::~AudioEngine()
{
    // shutdown audio here to prevent an application quit unexpectedly!
    transportSource.removeChangeListener(this);
    songGain.removeListener(this);
    shutdownAudio();
}

void AudioEngine::releaseResources()
{
    transportSource.releaseResources();
}

void AudioEngine::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // hand off processing to AudioTransportSource object by passing
    // said object the AudioSourceChannelInfo struct that was passed by
    // the AudioAppComponent class.
    if(readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    // if(transportSource.isPlaying()) {
    transportSource.getNextAudioBlock(bufferToFill);
    playheadSamples += bufferToFill.numSamples;
    // }
    // waveViewer.pushBuffer(bufferToFill->buffer);
}

void AudioEngine::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioEngine::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if(source == &transportSource)
    {
        if(transportSource.isPlaying())
            changeState(Playing);
        else if (state == Paused)
            changeState(Paused);
        else
            changeState(Stopped);
    }
}

bool AudioEngine::loadFile(juce::File f)
{
    auto* reader = formatManager.createReaderFor(f);
    if(reader != nullptr)
    {
        paused = false;
        playheadSamples.store(0);
        totalSeconds = transportSource.getLengthInSeconds();

        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        return true;
    }
    return false;
}

void AudioEngine::changeState(TransportState newState)
{
    if(state != newState) {
        state = newState;
        switch(state)
        {
            case Stopped:
                transportSource.setPosition(0.0);
                break;
            case Starting:
                if(paused) {
                    transportSource.setPosition(getCurrentSeconds());
                    paused = false;
                }
                transportSource.start();
                break;
            case Stopping:
                transportSource.stop();
                playheadSamples.store(0);
                break;
            case Paused:
                paused = true;
                transportSource.stop();
            case Playing:
                break;
            // default:
            //     break;
        }

    }
    
}

// void AudioEngine::timerCallback()
// {
//     currentSeconds = transportSource.getCurrentPosition();
// }

void AudioEngine::valueChanged(juce::Value& value)
{
    transportSource.setGain(
        juce::Decibels::decibelsToGain((float) value.getValue())
    );
}