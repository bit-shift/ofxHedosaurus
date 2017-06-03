#pragma once

#include <ofMain.h>

namespace pipeline {

//-----------------------------------------------------------------------------

class node {
public:
    node() {}

    virtual void process();

    ofImage& image() { return image_; }
    void update()
    {
        image_.update();
    }

protected:
    ofImage image_;
};

//-----------------------------------------------------------------------------

class file_node : public node {
public:
    file_node(const std::string filename) : node()
    {
        image_.load(filename);
    }

    void process()
    {

    }
};

//-----------------------------------------------------------------------------

class gen_node : public node {
public:
    gen_node() : node()
    {
        
    }

    void process()
    {

    }
};

//-----------------------------------------------------------------------------

class mixer_node {
public:
    mixer_node() {}

    void add_input(node& node)
    {
        in_nodes.push_back(node);
    }

    void draw()
    {
        for (auto& node: in_nodes)
        {
            // do the actual mixing via the alpha channel
            std::ignore = node.image();
            node.image().draw(0, 0);
        }
    }
private:
    vector<node> in_nodes;
};

//-----------------------------------------------------------------------------

class render_graph {
public:
    render_graph() {}

    void update() 
    {
        for (auto& node: nodes_)
            node.update();
    }

    void draw() 
    {
        mixer_.draw();
    }

private:
    vector<node> nodes_;
    mixer_node mixer_;
};

} // pipeline