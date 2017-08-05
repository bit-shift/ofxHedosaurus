#include "render_graph.h"

#include <constants.h>
#include <algorithms.h>


namespace engine {

node::node() 
{
    parameters_.add(alpha_.set("alpha", 255));
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
        // texture_.draw(-20 + y_.get(), -20 + (y_.get() / 6));
        texture2_.draw(0, 0);
        // frank: 0175 8808861
        // texture2_.draw(0, offset);
        // texture2_.draw(0, offset - 153);
    }  
}

auto node::alpha_changed(size_t& alpha) -> void
{
    active_ = alpha == 0 ? false : true;
}

} // engine
