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
	midi::in& midi_in_;

	pipeline::node_ptr node0_;
	pipeline::node_ptr node1_;
	pipeline::node_ptr node2_;
	pipeline::node_ptr node3_;
	pipeline::node_ptr node4_;
	
	pipeline::graph graph_;
};