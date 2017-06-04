#pragma once

#include <ofMain.h>

#include <constants.h>
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
    }

    void draw()
    {
        if (active_)
        {
            ofSetColor(255, 255, 255, alpha_.get());
            texture_.draw(0, 0);
        }  
    }

    void alpha_changed(size_t& alpha)
    {
        active_ = alpha == 0 ? false : true;
    }

    ofParameterGroup& parameters() { return parameters_; }

protected:
    bool active_ = true;
    
    ofTexture texture_;

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
        ofImage image;
        image.load(filename);
        texture_.loadData(image.getPixels());
    }
};

//-----------------------------------------------------------------------------

using generate_fn = std::function<void(ofImage&)>;

class color_node : public node {
public:
    color_node() : node()
    {
        ofColor black{0, 0, 0, 0};
        pxs_.allocate(QUAD_WIDTH, QUAD_HEIGHT, OF_IMAGE_COLOR_ALPHA);
	    pxs_.setColor(black);

        parameters_.add(r_.set("r", 0));
        parameters_.add(g_.set("g", 0));
        parameters_.add(b_.set("b", 0));
    }

    void update()
    {
        image::set_channel(pxs_, 0, r_.get());
        image::set_channel(pxs_, 1, g_.get());
        image::set_channel(pxs_, 2, b_.get());

        texture_.loadData(pxs_);

        node::update();
    }

private:
    ofParameter<size_t> r_;
    ofParameter<size_t> g_;
    ofParameter<size_t> b_;

    ofPixels pxs_;
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
