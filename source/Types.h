#pragma once

#ifndef TYPES_H
#define TYPES_H

#define MAX_INPUT_CHANNELS 16
#define MAX_OUTPUT_CHANNELS 16
#define DEFAULT_TIMER_INTERVAL_MS 1000


enum TransportState {
    Stopped, Starting, Playing, Stopping
};

struct TIME_VALUES {
    uint32_t hours = 0;
    uint32_t minutes = 0;
    double seconds = 0;
    // unsigned double miliseconds = 0;
};

inline TIME_VALUES getTimeValues(double timeInSeconds)
{
    TIME_VALUES out;
    out.hours = static_cast<uint32_t>(timeInSeconds) / 3600;
    double temp = std::fmod(timeInSeconds, 3600);
    out.minutes = (static_cast<uint32_t>(timeInSeconds) % 3600) / 60;
    out.seconds = std::fmod(temp, 60);
    return out;
}

#endif