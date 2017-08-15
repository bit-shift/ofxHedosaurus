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
    parameters_.add(x_.set("x", 0));
    parameters_.add(color_idx_.set("color_idx", 0));
        
    alpha_.addListener(this, &node::alpha_changed);
}

auto node::draw() -> void
{
    const int offset = - QUAD_HEIGHT + y_.get();
    ofSetColor(255, 255, 255, alpha_.get());

    texture_.draw(x_.get(), y_.get());
    // frank: 0175 8808861
    // texture2_.draw(-20 + y_.get(), -20 + (y_.get() / 6));
    // texture2_.draw(0, offset);
    // texture2_.draw(0, offset - 153); 
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
    texture_.loadData(image.getPixels());
}

//-----------------------------------------------------------------------------

triangle_node::triangle_node()
    : node()
    , rotations_(0)
{
}

auto triangle_node::update() -> void
{

}

auto triangle_node::draw() -> void
{ 
    // ofPushMatrix();
    
    // ofSetColor(0, 0, 255);
    // ofFill();
    // ofTranslate(QUAD_WIDTH / 2, QUAD_HEIGHT / 2);
    // ofRotateZDeg(rotations_);
    // rotations_++;
    // // ofDrawTriangle(0, 0, QUAD_WIDTH / 2, 0, 0, QUAD_HEIGHT);
    // ofDrawTriangle(QUAD_WIDTH / 2, 0, QUAD_WIDTH, QUAD_HEIGHT, 0, QUAD_HEIGHT);
    
    // ofPopMatrix();

    // ofPushMatrix();
    //     ofTranslate(QUAD_WIDTH / 2, QUAD_HEIGHT / 2, 0);//move pivot to centre
    //     ofRotateZDeg(rotations_);
    //     ofPushMatrix();
    //         // ofTranslate(-QUAD_WIDTH / 2, -QUAD_HEIGHT / 2, 0);//move back by the centre offset
    //         ofDrawTriangle(QUAD_WIDTH / 2, 0, QUAD_WIDTH, QUAD_HEIGHT, 0, QUAD_HEIGHT);
    //     ofPopMatrix();
    // ofPopMatrix();
}

// ofPoint move_square(size_t width, size_t height)
// {
    
// }

//-----------------------------------------------------------------------------

color_node::color_node() 
    : node()
{
    parameters_.add(r_.set("r", 0));
    parameters_.add(g_.set("g", 0));
    parameters_.add(b_.set("b", 0));
}

auto color_node::update() -> void
{
}

auto color_node::draw() -> void
{
    // ofSetColor(r_.get(), g_.get(), b_.get(), alpha_.get());
    ofSetColor(0, 0, 255);
    ofFill();
}

//-----------------------------------------------------------------------------

video_node::video_node(const std::string filename)
    : node()
{
#ifdef TARGET_RASPBERRY_PI

#else
	if (!player_.load(filename))
        ofLogNotice("video_node::setup()") << "Video could not be loaded: " << filename;
	player_.setLoopState(OF_LOOP_NORMAL);
	player_.play();
	player_.setVolume(0.0f);
    player_.setUseTexture(true);
	texture_ = player_.getTexture();
    ofLogNotice("video_node::video_node()") << "Player created";
#endif
}

video_node::~video_node()
{
    player_.stop();
	player_.close();
}

auto video_node::update() -> void
{
    if (player_.isInitialized())
        player_.update();
    else
        ofLogNotice("video_node::update()") << "Player not initialized";
}

auto video_node::draw() -> void
{
    node::draw();
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
        if(node->is_active())
            node->draw();
    }
}

auto graph::add_input(node_ptr node) -> void
{
    nodes_.push_back(node);
}

} // engine
