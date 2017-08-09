#pragma once

#include <midi.h>
#include <sequencer.h>
#include <render_graph.h>

#include <FboSource.h>

#include <ofxCvColorImage.h>
#include <ofMain.h>

class TextureSource : public ofx::piMapper::FboSource {

public:
	TextureSource(const string name, vector<string> image_paths);

	void setup();
	void update();
	void draw();

	void set_param(const size_t& node_idx,
				   const string& name, const size_t& value);

	ofParameterGroup& parameters() { return parameters_; }

private:
	void modulate();
	
	vector<string> image_paths_;

	vector<engine::node_ptr> nodes_;
	vector<engine::modulation> modulations_;

	engine::graph graph_;	

	ofParameterGroup parameters_;
    ofParameter<size_t> alpha_;
};