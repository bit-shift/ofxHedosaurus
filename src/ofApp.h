#pragma once

#include "midi.h"
#include "sequencer.h"
#include "render_graph.h"

#include "ofMain.h"
#include "Settings.h"
#include "ofxPiMapper.h"
#include "TextureSource.h"
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

		std::shared_ptr<TextureSource> source0_;
		std::shared_ptr<TextureSource> source1_;
		std::shared_ptr<TextureSource> source2_;
		std::shared_ptr<TextureSource> source3_;
		std::shared_ptr<TextureSource> source4_;
		std::shared_ptr<TextureSource> source5_;
		std::shared_ptr<TextureSource> source6_;
		std::shared_ptr<TextureSource> source7_;

private:
	void register_midi_trigger();
	void setup_modulations();

	std::vector<std::shared_ptr<TextureSource>> sources_;
};
