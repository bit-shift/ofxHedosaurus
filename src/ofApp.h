#pragma once

#include "midi.h"

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "SkinSource.h"
#include "VideoSource.h"

class ofApp : public ofBaseApp {
	public:
		void setup();
		void update();
		void draw();
		void exit();
	
		void keyPressed(int key);
		void keyReleased(int key);
	
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseDragged(int x, int y, int button);

		ofxPiMapper piMapper;
		
		midi::in midi_in_;

		SkinSource * _skinSource;
};
