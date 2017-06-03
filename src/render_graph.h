#pragma once

#include <ofMain.h>

namespace pipeline {

//-----------------------------------------------------------------------------

class node {
public:
    node() {}

    ofImage& image() 
    { 
        return image_; 
    }

    void add_input(node& node)
    {
        nodes_.push_back(node);
    }

    void update()
    {
        for (auto& node: nodes_)
            node.update();
        image_.update();
    }

protected:
    ofImage image_;
    vector<node> nodes_;
};

//-----------------------------------------------------------------------------

class file_node : public node {
public:
    file_node(const std::string filename) : node()
    {
        image_.load(filename);
    }

    void update()
    {
        node::update();
    }
};

//-----------------------------------------------------------------------------

class gen_node : public node {
public:
    gen_node() : node()
    {
        
    }

    void update()
    {
        node::update();
    }
};

//-----------------------------------------------------------------------------

class mixer_node : public node {
public:
    mixer_node() : node() {}

    void update()
    {
        for (auto& node: nodes_)
        {
            // do the actual mixing via the alpha channel
            std::ignore = node.image();
        }
        node::update();
    }
};

//-----------------------------------------------------------------------------

class render_graph {
public:
    render_graph(node& root)
    : root_(root) {}

    void update()
    {
        root_.update();
    }

    void draw()
    {
        root_.image().draw(0, 0);
    }

private:
    node& root_;
};

} // pipeline
