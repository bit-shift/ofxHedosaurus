#pragma once

#include "midi.h"

#include "ofMain.h"
#include "FboSource.h"

#include "ofxCvColorImage.h"

class SkinSource : public ofx::piMapper::FboSource {

public:
	SkinSource();

	void setup();
	void draw();

private:
	ofxCvColorImage image_;
	ofImage overlay_;
	ofPixels overlay_px_;

	midi::in midi_in_;

	ofParameter<size_t> saturation_;
};