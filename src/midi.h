#pragma once

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

struct trigger {
    size_t channel_;
    size_t pitch_;
    size_t control_;
    std::function<void(const size_t value)> fn_;
};

//-----------------------------------------------------------------------------

class in : public ofxMidiListener {
public:

    in()
    {
        in_.listPorts(); // via instance
        //ofxMidiIn::listPorts(); // via static as well
        
        // open port by number (you may need to change this)
        in_.openPort(1);
        //midiIn.openPort("IAC Pure Data In");	// by name
        //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
        
        // don't ignore sysex, timing, & active sense messages,
        // these are ignored by default
        in_.ignoreTypes(false, false, false);
        
        // add ofApp as a listener
        in_.addListener(this);
        
        // print received messages to the console
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
        for(const auto& trigger: trigger_)
        {
            if (trigger.channel_ == msg_.channel &&
                trigger.pitch_ == msg_.pitch &&
                trigger.control_ == msg_.control)
            {
                trigger.fn_(msg_.value);
            }                
        }
    }

    const ofxMidiMessage& message() const
    {
        return msg_;
    }

    void add_trigger(const trigger& trigger)
    {
        trigger_.push_back(trigger);
    }

private:
    ofxMidiIn in_;
    ofxMidiMessage msg_;
    vector<trigger> trigger_;
};

} // midi