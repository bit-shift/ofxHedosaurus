#pragma once

#include <ofMain.h>

#include <algorithms.h>

namespace pipeline {

//-----------------------------------------------------------------------------

class node {
public:
    node() {}

    ofImage& image()
    { 
        return image_; 
    }

    void update()
    {        
        image_.update();
    }

    void draw()
    {
        image_.draw(0, 0);
    }

    void set_alpha(const size_t alpha)
    {
        image::set_channel(image_.getPixels(), 3, alpha);
    }

protected:
    ofImage image_;
    size_t alpha_ = 255;
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
    ofImage image_;
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
        ofColor black{ 125, 67, 15, 255 };
        ofPixels pxs;
        pxs.allocate(450, 300, OF_IMAGE_COLOR_ALPHA);
	    pxs.setColor(black);
        image_.setFromPixels(pxs);
    }

    void set_r(const size_t value)
    {
        image::set_channel(image_.getPixels(), 0, value);
    }

    void set_g(const size_t value)
    {
        image::set_channel(image_.getPixels(), 1, value);
    }

    void set_b(const size_t value)
    {
        image::set_channel(image_.getPixels(), 2, value);
    }
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
