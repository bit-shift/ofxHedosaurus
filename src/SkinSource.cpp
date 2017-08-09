#include "SkinSource.h"

#include <constants.h>
#include <midi.h>
#include <algorithms.h>

#include <boost/optional.hpp>

//-----------------------------------------------------------------------------

using namespace engine;

SkinSource::SkinSource(const string source_name, vector<string> image_paths)
	: FboSource()
	, image_paths_(image_paths)
{
	name = source_name;
}

//-----------------------------------------------------------------------------

void SkinSource::setup()
{
	allocate(QUAD_WIDTH, QUAD_HEIGHT);

	for (const auto& path : image_paths_)
	{
		const auto node = make_shared<file_node>(path);
		graph_.add_input(node);
		nodes_.push_back(node);
	}

	parameters_.add(alpha_.set("alpha", 255));
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
	ofSetColor(255, 255, 255, alpha_.get());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// reduce visual strength / impact
	// ofSetColor(255, 255, 255, 150);

	graph_.draw();
}

//-----------------------------------------------------------------------------

void SkinSource::set_param(const size_t& node_idx,
			   const string& name, const size_t& value)
{
	if(const auto node = nodes_.at(node_idx))
		node->parameters().get<size_t>(name).set(value * 2);
}

//-----------------------------------------------------------------------------

void SkinSource::modulate()
{
	for (auto& modulation: modulations_)
    	modulation.step();
}