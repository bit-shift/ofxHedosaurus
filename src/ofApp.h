#pragma once

#include "midi.h"
#include "sequencer.h"
#include "render_graph.h"

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "SkinSource.h"
#include "VideoSource.h"

class ofApp : public ofBaseApp {
	public:
		ofApp() : ofBaseApp(), midi_in_(mapping_) {}

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

		midi::mapping mapping_;
		midi::in midi_in_;
		
		engine::sequencer sequencer_;

		std::shared_ptr<SkinSource> head_source_;
		std::shared_ptr<SkinSource> neck_source_;
		std::shared_ptr<SkinSource> body_source_;
		std::shared_ptr<SkinSource> fin_source_;
		std::shared_ptr<SkinSource> leg_front_source_;
		std::shared_ptr<SkinSource> leg_back_source_;
		std::shared_ptr<SkinSource> tail_source_;

private:
	void register_midi_trigger();
	void setup_modulations();
};
