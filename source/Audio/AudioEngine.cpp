#include "AudioEngine.h"

AudioEngine::AudioEngine() : state(Stopped), currentSeconds(0), totalSeconds(0)
{
    formatManager.registerBasicFormats(); // create readers for wav and aiff
    transportSource.addChangeListener(this);
    setAudioChannels(2, 2);
}

AudioEngine::~AudioEngine()
{
    // shutdown audio here to prevent an application quit unexpectedly!
    transportSource.removeChangeListener(this);
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
    transportSource.getNextAudioBlock(bufferToFill);
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
        else   
            changeState(Stopped);
    }
}

bool AudioEngine::loadFile(juce::File f)
{
    auto* reader = formatManager.createReaderFor(f);
    if(reader != nullptr)
    {
        auto newSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
        totalSeconds = transportSource.getLengthInSeconds();
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
                transportSource.start();
                break;
            case Stopping:
                transportSource.stop();
                break;
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