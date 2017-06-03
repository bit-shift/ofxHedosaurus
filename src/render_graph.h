#pragma once

#include <ofMain.h>

#include <algorithms.h>

namespace pipeline {

//-----------------------------------------------------------------------------

class node {
public:
    node()
    {
        parameters_.add(alpha_.set("alpha", 0));
        alpha_.addListener(this, &node::alpha_changed);
    }

    void update()
    {        
        if (active_)
            image_.update();
    }

    void draw()
    {
        if (active_)
            image_.draw(0, 0);
    }

    void alpha_changed(size_t& alpha)
    {
        image::set_channel(image_.getPixels(), 3, alpha);
        active_ = alpha == 0 ? false : true;
    }

    ofImage& image() { return image_; }
    ofParameterGroup& parameters() { return parameters_; }

protected:
    bool active_ = true;
    
    ofImage image_;

    ofParameterGroup parameters_;
    ofParameter<size_t> alpha_;
};

//-----------------------------------------------------------------------------

class input_node : public node {
public:
    input_node(node& input) : node(), input_(input) {}

    void update()
    {
        input_.update();
        node::update();
    }

protected:
    node& input_;
};

//-----------------------------------------------------------------------------

class file_node : public node {
public:
    file_node(const std::string filename) : node()
    {
        image_.load(filename);
    }
};

//-----------------------------------------------------------------------------

using generate_fn = std::function<void(ofImage&)>;

class color_node : public node {
public:
    color_node() : node()
    {
        ofColor black{0, 0, 0, 0};
        ofPixels pxs;
        pxs.allocate(450, 300, OF_IMAGE_COLOR_ALPHA);
	    pxs.setColor(black);
        image_.setFromPixels(pxs);

        parameters_.add(r_.set("r", 0));
        parameters_.add(g_.set("g", 0));
        parameters_.add(b_.set("b", 0));

        r_.addListener(this, &color_node::r_changed);
        g_.addListener(this, &color_node::g_changed);
        b_.addListener(this, &color_node::b_changed);
    }

    void r_changed(size_t& r)
    {
        image::set_channel(image_.getPixels(), 0, r);
    }

    void g_changed(size_t& g)
    {
        image::set_channel(image_.getPixels(), 1, g);
    }

    void b_changed(size_t& b)
    {
        image::set_channel(image_.getPixels(), 2, b);
    }

private:
    ofParameter<size_t> r_;
    ofParameter<size_t> g_;
    ofParameter<size_t> b_;
};

//-----------------------------------------------------------------------------

using node_ptr = std::shared_ptr<node>;

class graph {
public:
    graph() {}

    void update()
    {
        for (auto& node: nodes_)
        {
            node->update();
        }
    }

    void draw()
    {
        for (auto& node: nodes_)
        {
            node->draw();
        }
    }

    void add_input(node_ptr& node)
    {
        nodes_.push_back(node);
    }

private:
    vector<node_ptr> nodes_;
};

} // pipeline
