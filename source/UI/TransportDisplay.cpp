#include "TransportDisplay.h"

TransportDisplay::TransportDisplay(TransportStateManager& t) : transportState(t)
{
    transportInfo.addAndMakeVisible(&duration);
    duration.setColour(juce::Label::backgroundColourId, juce::Colours::black);
    duration.setColour(juce::Label::textColourId, juce::Colours::white);
    duration.setJustificationType(juce::Justification::centred);

    transportInfo.addAndMakeVisible(&nowPlaying);
    nowPlaying.setJustificationType(juce::Justification::centred);
    nowPlaying.setText("No Audio File Selected.", juce::dontSendNotification);

    transportInfo.addAndMakeVisible(&songTransport);
    // song transport visual goes here

    transportInfo.addAndMakeVisible(&songGain);
    songGain.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    songGain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
    false, TEXTBOX_WIDTH, TEXTBOX_HEIGHT
    );

    songGain.getProperties().set("drawFromMiddle", true);
    songGain.setRotaryParameters(1.25f * juce::MathConstants<float>::pi,
    2.75f * juce::MathConstants<float>::pi, true);
    songGain.setTextValueSuffix("dB");
    songGain.setRange(-12, 12, 0.01);
    songGain.setDoubleClickReturnValue(true, 0);

    transportState.addListener(this);

    // songGain.getValueObject().referTo(audioEngine.getSongGain)
}

void TransportDisplay::hiResTimerCallback()
{
    // currentFileDuration = convertTime(currentSeconds);
}

TransportDisplay::~TransportDisplay()
{
    transportState.removeListener(this);
}

void TransportDisplay::resized()
{
    transportInfo.setBounds(getLocalBounds());
    // set bounds of objects beneath here
}

void TransportDisplay::onTransportStateChange(TransportState state)
{
    // switch(state)
    // {
    //     case Stopped:
    //         duration.setText(convertTime(0) + " / " + convertTime(totalSeconds),
    //             juce::dontSendNotification);
    //         nowPlaying.setText(juce::String("Stopped: ") + fileName, 
    //             juce::dontSendNotification);
    //         stopTimer();
    //         break;
    //     case Starting:
    //         break;
    //     case Playing:
    //         startTimer(FAST_TIMER_INTERVAL_MS);
    //         nowPlaying.setText(juce::String("Now Playing: ") + fileName,
    //             juce::dontSendNotification);
    //         break;
    //     case Stopping:
    //         stopTimer();
    //         break;
    //     case Paused:
    //         nowPlaying.setText(juce::String("Paused: ") + fileName,
    //         juce::dontSendNotification);
    //         stopTimer();
    //         break;
    // }

    // switch(state)
    // {
    //     case Stopped:
    //         duration.setText(convertTime(0) + " / " + convertTime(totalSeconds),
    //             juce::dontSendNotification);
    //         nowPlaying.setText(juce::String("Stopped: ") + fileName, 
    //             juce::dontSendNotification);
    //         break;
    // }
}