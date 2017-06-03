#include "SkinSource.h"

#include <midi.h>
#include <algorithms.h>

//-----------------------------------------------------------------------------

using namespace pipeline;

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
	, node0_(new file_node("assets/skin_tex_01_unsharpen.png"))
	, node1_(new file_node("assets/skin_tex_02_unsharpen.png"))
	, node2_(new color_node())
{
	name = "Skin";
	allocate(450, 300);

	graph_.add_input(node0_);
	graph_.add_input(node1_);
	graph_.add_input(node2_);
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	// ALPHA
	midi_in_.add_trigger(midi::trigger_t{ 117, [this](const size_t value){ 
		node0_->set_alpha(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 118, [this](const size_t value){ 
		node1_->set_alpha(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 14, [this](const size_t value){ 
		node2_->set_alpha(value * 2);
	}});
}

//-----------------------------------------------------------------------------

void SkinSource::update()
{
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
}
