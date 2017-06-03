#include "SkinSource.h"

#include <midi.h>
#include <algorithms.h>

//-----------------------------------------------------------------------------

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
{
	name = "Skin";
	allocate(450, 300);
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	ofImage image;
	ofColor black{ 0, 0, 0, 0 };
    image_.load("assets/skin_tex_01_unsharpen.jpg");
	image2_.load("assets/skin_tex_02_unsharpen.jpg");

	overlay_px_.allocate(image_.getWidth(), image_.getHeight(), 
						OF_IMAGE_COLOR_ALPHA);
	overlay_px_.setColor(black);

	
	// RED
	midi_in_.add_trigger(midi::trigger_t{ 100, [this](const size_t value){ 
		image::set_channel(overlay_px_, 0, value * 2);
	}});

	// GREEN
	midi_in_.add_trigger(midi::trigger_t{ 106, [this](const size_t value){ 
		image::set_channel(overlay_px_, 1, value * 2);
	}});

	// BLUE
	midi_in_.add_trigger(midi::trigger_t{ 103, [this](const size_t value){ 
		image::set_channel(overlay_px_, 2, value * 2);
	}});

	// ALPHA
	midi_in_.add_trigger(midi::trigger_t{ 117, [this](const size_t value){ 
		image::set_channel(overlay_px_, 3, value * 2);
	}});

	// ALPHA
	midi_in_.add_trigger(midi::trigger_t{ 118, [this](const size_t value){ 
		image::set_channel(image_.getPixels(), 3, value * 2);
	}});
}

//-----------------------------------------------------------------------------

void SkinSource::update()
{
	overlay_.setFromPixels(overlay_px_);
}

//-----------------------------------------------------------------------------

void SkinSource::draw()
{
	ofBackground(0); // this matters
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	image_.draw(0, 0);
	overlay_.draw(0, 0);
}
