#include "render_graph.h"

#include <constants.h>
#include <algorithms.h>


namespace engine {

using node_ptr = std::shared_ptr<node>;
using generate_fn = std::function<void(ofImage&)>;

//-----------------------------------------------------------------------------

node::node() 
{
    parameters_.add(alpha_.set("alpha", 0));
    parameters_.add(y_.set("y", 0));
    parameters_.add(color_idx_.set("color_idx", 0));
        
    alpha_.addListener(this, &node::alpha_changed);
}

auto node::draw() -> void
{
    if (active_)
    {
        const int offset = - QUAD_HEIGHT + y_.get();
        ofSetColor(255, 255, 255, alpha_.get());

        texture_.draw(0, 0);

        // frank: 0175 8808861
        // texture2_.draw(-20 + y_.get(), -20 + (y_.get() / 6));
        // texture2_.draw(0, offset);
        // texture2_.draw(0, offset - 153);
    }  
}

auto node::alpha_changed(size_t& alpha) -> void
{
    active_ = alpha == 0 ? false : true;
}

//-----------------------------------------------------------------------------

file_node::file_node(const std::string filename) 
    : node()
{
    ofImage image;
    image.load(filename);
    image.rotate90(2);
    texture_.loadData(image.getPixels());
}

//-----------------------------------------------------------------------------

color_node::color_node() 
    : node()
{
    ofColor black{0, 0, 0, 0};
    pxs_.allocate(QUAD_WIDTH, QUAD_HEIGHT, OF_IMAGE_COLOR_ALPHA);
	pxs_.setColor(black);

    parameters_.add(r_.set("r", 0));
    parameters_.add(g_.set("g", 0));
    parameters_.add(b_.set("b", 0));
}

auto color_node::update() -> void
{
    image::set_channel(pxs_, 0, r_.get());
    image::set_channel(pxs_, 1, g_.get());
    image::set_channel(pxs_, 2, b_.get());

    texture_.loadData(pxs_);

    node::update();
}

//-----------------------------------------------------------------------------

video_node::video_node(const std::string filename) 
    : node()
{
#ifdef TARGET_RASPBERRY_PI

#else
	if (!player_.load(filename))
        ofLogNotice("video_node::video_node()") << "Video could not be loaded";
	player_.setLoopState(OF_LOOP_NORMAL);
	player_.play();
	player_.setVolume(0.0f);
	texture_ = player_.getTexture();
#endif
}

video_node::~video_node()
{
    player_.stop();
	player_.close();
}

auto video_node::update() -> void
{
    player_.update();

    node::update();
}

//-----------------------------------------------------------------------------

auto graph::update() -> void
{
    for (auto& node: nodes_)
    {
        node->update();
    }
}

auto graph::draw() -> void
{
    for (auto& node: nodes_)
    {
        node->draw();
    }
}

auto graph::add_input(node_ptr node) -> void
{
    nodes_.push_back(node);
}

} // engine
