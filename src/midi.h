#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

namespace midi {

inline void log_message(const ofxMidiMessage& message)
{
    ofLogNotice("midi", "Received: " + ofxMidiMessage::getStatusString(message.status));
	ofLogNotice("midi", "channel: " + to_string(message.channel));
	ofLogNotice("midi", "pitch: " + to_string(message.pitch));
	ofLogNotice("midi", "velocity: " + to_string(message.velocity));	
	ofLogNotice("midi", "control: " + to_string(message.control));
	ofLogNotice("midi", "value: " + to_string(message.value));
	ofLogNotice("midi", "dtime: " + to_string(message.deltatime));
}

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

    void newMidiMessage(ofxMidiMessage& event) 
    { 
        msg_ = event;
    }

    const ofxMidiMessage& message()
    {
        return msg_;
    }

private:
    ofxMidiIn in_;
    ofxMidiMessage msg_;
};

} // midi