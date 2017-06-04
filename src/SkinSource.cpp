#include "SkinSource.h"

#include <constants.h>
#include <midi.h>
#include <algorithms.h>

#include <boost/optional.hpp>

//-----------------------------------------------------------------------------

using namespace engine;

SkinSource::SkinSource(midi::in& midi_in)
	: midi_in_(midi_in)
	, node0_(new file_node("assets/skin_tex_00.png"))
	, node1_(new file_node("assets/skin_tex_01.png"))
	, node2_(new file_node("assets/skin_tex_02.png"))
	, node3_(new file_node("assets/skin_tex_03.png"))
	, node4_(new file_node("assets/skin_tex_04.png"))
	, node5_(new file_node("assets/skin_tex_05.png"))
	, node6_(new file_node("assets/skin_tex_06.png"))
	, node7_(new file_node("assets/skin_tex_07.png"))

{
	name = "Skin";
	allocate(QUAD_WIDTH, QUAD_HEIGHT);

	graph_.add_input(node0_);
	graph_.add_input(node1_);
	graph_.add_input(node2_);
	graph_.add_input(node3_);
	graph_.add_input(node4_);
	graph_.add_input(node5_);
	graph_.add_input(node6_);
	graph_.add_input(node7_);

	modulation_fn fn = [](ofParameter<size_t>& param) {
		auto value = param.get();
        value = value == 255 ? 0 : 255;
        param.set(value);
	};
	modulation mod2{node2_, std::move(fn)};
	
	sequencer_.add_modulation(std::move(mod2));
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	// ALPHA
	midi_in_.add_trigger(midi::trigger{ 9, 0, 117, 
	[this](const size_t value) {
		node0_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 118, 
	[this](const size_t value) { 
		node1_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 14, 
	[this](const size_t value) { 
		node2_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 17, 
	[this](const size_t value){ 
		node3_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 25, 
	[this](const size_t value){ 
		node4_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 30, 
	[this](const size_t value){ 
		node5_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 48, 
	[this](const size_t value){ 
		node6_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	midi_in_.add_trigger(midi::trigger{ 9, 0, 53, 
	[this](const size_t value){ 
		node7_->parameters().get<size_t>("alpha").set(value * 2);
	}});

	// BPM
	midi_in_.add_trigger(midi::trigger{ 9, 0, 58, 
	[this](const size_t value){ 
		sequencer_.parameters().get<size_t>("bpm").set(value * 2);
	}});

	// TRANSPORT
	midi_in_.add_trigger(midi::trigger{ 1, 10, 0, 
	[this](const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(false);
	}});
	midi_in_.add_trigger(midi::trigger{ 1, 11, 0, 
	[this](const size_t value){ 
		sequencer_.parameters().get<size_t>("running").set(true);
	}});
}

//-----------------------------------------------------------------------------

void SkinSource::update()
{
	sequencer_.update();
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
