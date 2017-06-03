#include "SkinSource.h"

#include <midi.h>
#include <algorithms.h>

//-----------------------------------------------------------------------------

using namespace pipeline;

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
	, image_node_("assets/skin_tex_01_unsharpen.png")
	, graph_(mixer_node_)
{
	name = "Skin";
	allocate(450, 300);
	
	mixer_node_.add_input(image_node_);
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	ofImage image;
	ofColor black{ 0, 0, 0, 0 };
    image_.load("assets/skin_tex_01_unsharpen.png");
	image2_.load("assets/skin_tex_02_unsharpen.jpg");

	overlay_px_.allocate(image_.getWidth(), image_.getHeight(), 
						OF_IMAGE_COLOR_ALPHA);
	overlay_px_.setColor(black);

	// // Overlay
	// // RED
	// midi_in_.add_trigger(midi::trigger_t{ 100, [this](const size_t value){ 
	// 	image::set_channel(overlay_px_, 0, value * 2);
	// }});

	// // GREEN
	// midi_in_.add_trigger(midi::trigger_t{ 106, [this](const size_t value){ 
	// 	image::set_channel(overlay_px_, 1, value * 2);
	// }});

	// // BLUE
	// midi_in_.add_trigger(midi::trigger_t{ 103, [this](const size_t value){ 
	// 	image::set_channel(overlay_px_, 2, value * 2);
	// }});

	// // ALPHA
	// midi_in_.add_trigger(midi::trigger_t{ 117, [this](const size_t value){ 
	// 	image::set_channel(overlay_px_, 3, value * 2);
	// }});

	// // ALPHA
	// midi_in_.add_trigger(midi::trigger_t{ 118, [this](const size_t value){ 
	// 	image::set_channel(image_.getPixels(), 3, value * 2);
	// }});
}

//-----------------------------------------------------------------------------

void SkinSource::update()
{
	overlay_.setFromPixels(overlay_px_);
	image_.update();

	graph_.update();
}

//-----------------------------------------------------------------------------

void SkinSource::draw()
{
	ofBackground(0); // this matters
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// reduce visual strength / impact
	// ofSetColor(255, 255, 255, 150);
	graph_.draw();

	// overlay_.draw(0, 0);
	// image_.draw(0, 0);
}
