#include "SkinSource.h"

#include <constants.h>
#include <midi.h>
#include <algorithms.h>

//-----------------------------------------------------------------------------

using namespace pipeline;

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
	, node0_(new file_node("assets/skin_tex_02.png"))
	, node1_(new file_node("assets/skin_tex_03.png"))
	, node2_(new file_node("assets/skin_tex_04.png"))
	, node3_(new file_node("assets/skin_tex_05.png"))
	, node4_(new file_node("assets/skin_tex_06.png"))
{
	name = "Skin";
	allocate(QUAD_WIDTH, QUAD_HEIGHT);

	graph_.add_input(node0_);
	graph_.add_input(node1_);
	graph_.add_input(node2_);
	graph_.add_input(node3_);
	graph_.add_input(node4_);
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	// ALPHA Master mixing
	midi_in_.add_trigger(midi::trigger_t{ 117, [this](const size_t value){ 
		node0_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 118, [this](const size_t value){ 
		node1_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 14, [this](const size_t value){ 
		node2_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 17, [this](const size_t value){ 
		node3_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger_t{ 25, [this](const size_t value){ 
		node4_->parameters().get<size_t>("alpha").set(value * 2);
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
