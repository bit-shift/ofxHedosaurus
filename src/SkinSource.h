#pragma once

#include <midi.h>
#include <sequencer.h>
#include <render_graph.h>

#include <FboSource.h>

#include <ofxCvColorImage.h>
#include <ofMain.h>

class SkinSource : public ofx::piMapper::FboSource {

public:
	SkinSource(midi::in& midi_in);

	void setup();
	void update();
	void draw();

private:
	midi::in& midi_in_;

	engine::node_ptr node0_;
	engine::node_ptr node1_;
	engine::node_ptr node2_;
	engine::node_ptr node3_;
	engine::node_ptr node4_;
	engine::node_ptr node5_;
	engine::node_ptr node6_;
	engine::node_ptr node7_;
	
	engine::graph graph_;
	engine::sequencer sequencer_;
};