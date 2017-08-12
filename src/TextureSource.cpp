#include "TextureSource.h"

#include <constants.h>
#include <midi.h>
#include <algorithms.h>

#include <boost/optional.hpp>

//-----------------------------------------------------------------------------

using namespace engine;

TextureSource::TextureSource(const string source_name, 
							vector<string> image_paths,
							vector<string> video_paths)
	: FboSource()
	, image_paths_(image_paths)
	, video_paths_(video_paths)
{
	name = source_name;
}

//-----------------------------------------------------------------------------

void TextureSource::setup()
{
	allocate(QUAD_WIDTH, QUAD_HEIGHT);

	for (const auto& path : image_paths_)
	{
		const auto node = make_shared<file_node>(path);
		graph_.add_input(node);
		nodes_.push_back(node);

		// modulation mod{node};
		// modulator mod_fn {"alpha", [](ofParameter<size_t>& param) {
		// 	auto value = param.get();
        // 	value = value == 255 ? 0 : 255;
        // 	// param.set(value);
		// }};
		// mod.add_modulator(std::move(mod_fn));
		// modulations_.push_back(std::move(mod));
	}

	for (const auto& path : video_paths_)
	{
		const auto node = make_shared<video_node>(path);
		graph_.add_input(node);
		nodes_.push_back(node);
	}

	parameters_.add(alpha_.set("alpha", 255));
}

//-----------------------------------------------------------------------------

void TextureSource::update()
{
	modulate();
	graph_.update();
}

//-----------------------------------------------------------------------------

void TextureSource::draw()
{
	ofBackground(0); // this matters
	ofSetColor(255, 255, 255, alpha_.get());
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	// reduce visual strength / impact
	// ofSetColor(255, 255, 255, 150);

	graph_.draw();
}

//-----------------------------------------------------------------------------

void TextureSource::set_param(const size_t& node_idx,
			   const string& name, const size_t& value)
{
	if(const auto node = nodes_.at(node_idx))
		node->parameters().get<size_t>(name).set(value * 2);
}

//-----------------------------------------------------------------------------

void TextureSource::modulate()
{
	for (auto& modulation: modulations_)
    	modulation.step();
}