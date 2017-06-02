#include "SkinSource.h"

#include <algorithms.h>

//--------------------------------------------------------------

SkinSource::SkinSource()
{
	name = "Skin";
	allocate(450, 300);
}

//--------------------------------------------------------------

void SkinSource::setup()
{
	ofImage image;
    image.load("assets/skin_tex_01_unsharpen.jpg");
	image_.setFromPixels(image.getPixels());
	// invert(image_);

	overlay_px_.allocate(image_.getWidth(), image_.getHeight(), OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------

void SkinSource::draw()
{
	ofBackground(0); // this matters
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	midi::log_message(midi_in_.message());

	overlay_px_.setColor(ofColor::blue);
	overlay_.setFromPixels(overlay_px_);
	
	image_.draw(0, 0);
	// overlay_.draw(0, 0);
}
