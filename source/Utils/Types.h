#pragma once

#ifndef TYPES_H
#define TYPES_H

/*
    Types.h

    Utility header file for enums, structs, and namespaces 
    that multiple simple pieces of software that may be
    useful across multiple different files, such as time
    conversion.
*/

#include <juce_core/juce_core.h>

#define MAX_INPUT_CHANNELS 16
#define MAX_OUTPUT_CHANNELS 16
#define DEFAULT_TIMER_INTERVAL_MS 1000
#define FAST_TIMER_INTERVAL_MS 20
#define DEFAULT_SAMPLE_RATE 48000
#define BUTTON_HEIGHT 32
#define BUTTON_WIDTH 32
#define DURATION_WIDTH getWidth() - 20
#define DURATION_HEIGHT 32

#define TEXTBOX_HEIGHT 16
#define TEXTBOX_WIDTH 64

#define APP_WIDTH 600
#define APP_HEIGHT 400

#define TEST_WIDTH 50
#define TEST_HEIGHT 50
#define TEST_CONTROLS_WIDTH 300
#define TEST_CONTROLS_HEIGHT 50

struct TIME_VALUES {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int milliseconds = 0;
};

inline TIME_VALUES getTimeValues(double timeInSeconds)
{
    TIME_VALUES out;
    out.hours = 0;
    juce::RelativeTime time(timeInSeconds);
    // out.hours = ((int) time.inHours()); // find a fix to this silas pls thanks
    out.minutes = (int) time.inMinutes() % 60;
    out.seconds = (int) time.inSeconds() % 60;
    out.milliseconds = (int) time.inMilliseconds() % 1000;
    return out;
}

inline juce::String convertTime(double d)
{
    TIME_VALUES values = getTimeValues(d);

    juce::String out;
    if(values.hours > 0)
        out = juce::String::formatted("%d : %02d : %02d . %03d", 
            values.hours, values.minutes, values.seconds, values.milliseconds);
    else
        out = juce::String::formatted("%02d : %02d . %03d",
            values.minutes, values.seconds, values.milliseconds);
    
    return out;
}

#endif