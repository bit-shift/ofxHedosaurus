#pragma once

#include <midi.h>
#include <sequencer.h>
#include <render_graph.h>

#include <FboSource.h>

#include <ofxCvColorImage.h>
#include <ofMain.h>

class SkinSource : public ofx::piMapper::FboSource {

public:
	SkinSource();

	void setup();
	void update();
	void draw();

	void set_param(const size_t& node_idx, 
				   const std::string& name, const size_t& value);
	void modulate();

private:
	engine::node_ptr node0_;
	engine::node_ptr node1_;
	engine::node_ptr node2_;
	engine::node_ptr node3_;
	engine::node_ptr node4_;
	engine::node_ptr node5_;
	engine::node_ptr node6_;
	engine::node_ptr node7_;

	std::vector<engine::node_ptr> nodes_;

	engine::graph graph_;
	std::vector<engine::modulation> modulations_;
};