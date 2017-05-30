#pragma once

#include "ofMain.h"
#include "FboSource.h"

class SkinSource : public ofx::piMapper::FboSource {
	public:
		SkinSource();

		void setup();
		void draw();

		ofShader _shader;
    	ofPlanePrimitive _plane;
		ofImage _img;
};