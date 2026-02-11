#pragma once

#ifndef TRANSPORT_STATE_MANAGER_H
#define TRANSPORT_STATE_MANAGER_H

#include <JuceHeader.h>
// #include "Utils/TransportStateListener.h"

// States that the transport can currently be in.
enum TransportState {
    Stopped, Starting, Playing, Stopping, Paused, Looping
};

/*
    TransportStateListener.h

    Small virtual struct that allows for the implementation of behaviors
    that react to state changes via the virtual void onTransportStateChange
    function. This is particularly useful for synchronizing events / actions
    that happen across multiple different files (ie. UI & AudioEngine &
    Display) and should be commonly used in conjunction with the
    TransportStateManager class.
*/

struct TransportStateListener
{
    ~TransportStateListener() = default;
    virtual void onTransportStateChange(TransportState s) = 0;
};

/*
    TransportStateManager
    
    Class that manages transport state changes and calls any objects
    that are within the vector listeners upon a state change. Designed
    to be used in conjunction with the TransportStateListener.
*/
class TransportStateManager
{
public:
    void addListener(TransportStateListener* l) { 
        listeners.add(l); 
    }
    void removeListener(TransportStateListener* l) {
        listeners.remove(l);
    }
    void changeState(TransportState newState) {
        if(state != newState) {
            state = newState;
            listeners.call([&](TransportStateListener& l) {
                l.onTransportStateChange(state);
            });
        }
    }

    TransportState getState() { return state; }

private:
    TransportState state { Stopped };
    juce::ListenerList<TransportStateListener> listeners;
};

#endif