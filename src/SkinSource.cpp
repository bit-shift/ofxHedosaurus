#include "SkinSource.h"

#include <midi.h>
#include <algorithms.h>

//--------------------------------------------------------------

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
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
	
	// Adds callbacks
	midi_in_.add_trigger(midi::trigger_t{ 100, [this](const size_t value){ 
		auto i = 0;
		while (i < overlay_px_.size())
		{
			overlay_px_[i] = std::min(value * 2, size_t{ 255 });
			i += 3;
		}
	}});
	midi_in_.add_trigger(midi::trigger_t{ 106, [this](const size_t value){ 
		auto i = 1;
		while (i < overlay_px_.size())
		{
			overlay_px_[i] = std::min(value * 2, size_t{ 255 });
			i += 3;
		}
	}});
	midi_in_.add_trigger(midi::trigger_t{ 103, [this](const size_t value){ 
		auto i = 2;
		while (i < overlay_px_.size())
		{
			overlay_px_[i] = std::min(value * 2, size_t{ 255 });
			i += 3;
		}
	}});
}

//--------------------------------------------------------------

void SkinSource::draw()
{
	ofBackground(0); // this matters
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	midi::log_message(midi_in_.message());

	overlay_.setFromPixels(overlay_px_);
	
	// image_.draw(0, 0);
	overlay_.draw(0, 0);
}
