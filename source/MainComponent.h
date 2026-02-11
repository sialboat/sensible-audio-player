#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <JuceHeader.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "Audio/AudioEngine.h"
#include "UI/TransportComponent.h"
#include "Utils/Types.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent final : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool keyPressed(const juce::KeyPress& k) override;

private:
    AudioEngine audioEngine;
    TransportComponent transportComponent;

    TransportStateManager transportState;
    
    // label object to interface that displays current time position of 
    // audioTransportSource object.
    // use AudioTransportSource::getCurrentPosition() to obtain position
    // Make MainContentComponent inherit from Timer class
    // perform periodic timer updatses in timerCallback()
    // relativeTime class can also be used to convert raw time in seconds 
    // for minutes, seconds, milliseconds.

    // change third file patternsallowed argument when creating filechooser
    // object to allow application to load AIFF as well.
    //==============================================================================
    // Your private member variables go here...

    // display stuff
    // juce::TextButton openButton;
    // juce::TextButton playButton;
    // juce::TextButton stopButton;
    // TransportState state; // audio

    // std::unique_ptr<juce::FileChooser> chooser; // file chooser

    // juce::AudioFormatManager formatManager; // audio
    // std::unique_ptr<juce::AudioFormatReaderSource> readerSource; // audio
    // juce::AudioTransportSource transportSource; // audio

    // juce::AudioDeviceManager otherDeviceManager; // audio
    // juce::AudioVisualiserComponent waveViewer;  // audio

    // // best used for things that can changed in real time
    // // (unique ptrs)
    // std::unique_ptr<juce::AudioDeviceSelectorComponent> audioSettings;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
