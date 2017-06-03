#pragma once

#include "midi.h"
#include <render_graph.h>

#include "ofMain.h"
#include "FboSource.h"

#include "ofxCvColorImage.h"

class SkinSource : public ofx::piMapper::FboSource {

public:
	SkinSource(midi::in& midi_in);

	void setup();
	void update();
	void draw();

private:
	ofImage image_;
	ofImage image2_;
	ofImage overlay_;
	ofPixels overlay_px_;

	midi::in& midi_in_;

	ofParameter<size_t> saturation_;

	pipeline::node_ptr node0_;
	pipeline::node_ptr node1_;
	pipeline::node_ptr node2_;
	
	pipeline::graph graph_;
};