#pragma once

#include "FboSource.h"

#include "ofMain.h"
#include "ofxMidi.h"

#include <boost/optional.hpp>

namespace midi {

//-----------------------------------------------------------------------------

inline void log_message(const ofxMidiMessage& message)
{
    ofLogNotice("midi", "Received: " + 
                    ofxMidiMessage::getStatusString(message.status));
	ofLogNotice("midi", "channel: " + to_string(message.channel));
	ofLogNotice("midi", "pitch: " + to_string(message.pitch));
	ofLogNotice("midi", "velocity: " + to_string(message.velocity));	
	ofLogNotice("midi", "control: " + to_string(message.control));
	ofLogNotice("midi", "value: " + to_string(message.value));
	ofLogNotice("midi", "dtime: " + to_string(message.deltatime));
}

//-----------------------------------------------------------------------------
using FboSource = ofx::piMapper::FboSource;

struct trigger {
    size_t channel_;
    size_t control_;
    size_t pitch_;
    std::function<void(const size_t value)> fn_;
};

class mapping {
public:
    void on_event(ofxMidiMessage& event)
    {
        for (const auto& trigger: triggers_)
        {
            if (trigger.channel_ == event.channel &&
                trigger.control_ == event.control &&
                trigger.pitch_ == event.pitch)
            {
                const auto velocity = ofxMidiMessage::getStatusString(event.status) == "Note Off" 
                    ? 0.0
                    : event.velocity;
                trigger.fn_(velocity);            
            }                
        }
    }

    void add_trigger(trigger trigger)
    {
        triggers_.push_back(trigger);
    }

private:
    std::vector<trigger> triggers_;
};

//-----------------------------------------------------------------------------

class in : public ofxMidiListener {
public:

    in(mapping& mapping) : mapping_(mapping)
    {
        // in_.listPorts(); // via instance
        //ofxMidiIn::listPorts(); // via static as well
        
        // open port by number (you may need to change this)
        // in_.openPort(1);
        //midiIn.openPort("IAC Pure Data In");	// by name
        in_.openVirtualPort("ofxHedosaurus Input"); // open a virtual port
        
        // don't ignore sysex, timing, & active sense messages,
        // these are ignored by default
        in_.ignoreTypes(false, false, false);
        
        // add ofApp as a listener
        in_.addListener(this);
        
        // print received messages to thchannele console
        in_.setVerbose(true);
    }

    ~in()
    {
        in_.closePort();
	    in_.removeListener(this);
    }

    void newMidiMessage(ofxMidiMessage& event)
    { 
        msg_ = event;
        mapping_.on_event(event);
    }

    const ofxMidiMessage& message() const
    {
        return msg_;
    }

private:
    ofxMidiIn in_;
    ofxMidiMessage msg_;
    mapping& mapping_;
};

} // midi