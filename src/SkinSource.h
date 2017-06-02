#pragma once

#include "midi.h"

#include "ofMain.h"
#include "FboSource.h"

#include "ofxCvColorImage.h"

class SkinSource : public ofx::piMapper::FboSource {

public:
	SkinSource(midi::in& midi_in);

	void setup();
	void draw();
	void update();

private:
	ofImage image_;
	ofImage image2_;

	ofPixels fbo_px_;

	ofImage overlay_;
	ofPixels overlay_px_;
	ofMesh mesh_;

	midi::in& midi_in_;

	ofParameter<size_t> saturation_;

	const size_t height_ = 1024;
	const size_t width_ = 1024;
	const size_t meshSize_ = 6;

	int W = 200;
	int H = 100;
	
};