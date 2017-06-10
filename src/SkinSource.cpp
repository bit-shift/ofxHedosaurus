#include "SkinSource.h"

#include <constants.h>
#include <midi.h>
#include <algorithms.h>

#include <boost/optional.hpp>

//-----------------------------------------------------------------------------

using namespace engine;

SkinSource::SkinSource(const std::string source_name,
					   const std::vector<std::string>& filenames)
	: FboSource()
	, node0_(new file_node(filenames.at(0)))
	, node1_(new file_node(filenames.at(1)))
	, node2_(new file_node(filenames.at(2)))
	, node3_(new file_node(filenames.at(3)))
	, node4_(new file_node(filenames.at(4)))
	, node5_(new file_node(filenames.at(5)))
	, node6_(new file_node(filenames.at(6)))
	, node7_(new file_node(filenames.at(7)))

{
	name = source_name;
	allocate(QUAD_WIDTH, QUAD_HEIGHT);

	graph_.add_input(node0_);
	nodes_.push_back(node0_);

	graph_.add_input(node1_);
	nodes_.push_back(node1_);

	graph_.add_input(node2_);
	nodes_.push_back(node2_);

	graph_.add_input(node3_);
	nodes_.push_back(node3_);

	graph_.add_input(node4_);
	nodes_.push_back(node4_);

	graph_.add_input(node5_);
	nodes_.push_back(node5_);

	graph_.add_input(node6_);
	nodes_.push_back(node6_);

	graph_.add_input(node7_);
	nodes_.push_back(node7_);

	modulation mod2{node2_};
	modulator mod_fn2 {"alpha", [](ofParameter<size_t>& param) {
		auto value = param.get();
        value = value == 255 ? 0 : 255;
        param.set(value);
	}};
	mod2.add_modulator(std::move(mod_fn2));
	modulations_.push_back(std::move(mod2));
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
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
	// ofSetColor(255, 255, 255, alpha_.get());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// reduce visual strength / impact
	// ofSetColor(255, 255, 255, 150);

	graph_.draw();
}

//-----------------------------------------------------------------------------

void SkinSource::set_param(const size_t& node_idx,
			   const std::string& name, const size_t& value)
{
	ofLogNotice("SkinSource::set_param()", name);
	nodes_.at(node_idx)->parameters().get<size_t>(name).set(value * 2);
}

//-----------------------------------------------------------------------------

void SkinSource::modulate()
{
	for (auto& modulation: modulations_)
    	modulation.step();
}