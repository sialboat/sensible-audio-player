#pragma once

#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H

#include <JuceHeader.h>

/*
    AudioFile.h

    Abstraction that houses information relevant to an audio file
    (Metadata & loading audio file).
*/

class AudioFile
{
public:
    void loadFile(const juce::File& f);
    double getDuration() const;
    juce::AudioSource* getAudioSource();
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioFile)
};

#endif