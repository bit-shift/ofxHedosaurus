#pragma once

#include <ofMain.h>

#include <constants.h>
#include <algorithms.h>


namespace engine {

//-----------------------------------------------------------------------------

class node {
public:
    node();

    auto update() -> void {}
    auto draw() -> void;
    auto alpha_changed(size_t& alpha) -> void;

    auto parameters() -> ofParameterGroup& { return parameters_; }

protected:
    bool active_ = true;
    
    ofTexture texture_;
    ofTexture texture2_;

    ofParameterGroup parameters_;
    ofParameter<size_t> alpha_;
    ofParameter<size_t> color_idx_;
    ofParameter<int> x_;
    ofParameter<int> y_;
};

//-----------------------------------------------------------------------------

class file_node : public node {
public:
    file_node(const std::string filename);
};

//-----------------------------------------------------------------------------

using generate_fn = std::function<void(ofImage&)>;

class color_node : public node {
public:
    color_node();

    auto update() ->void;

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

    auto update() -> void;
    auto draw() -> void;
    auto add_input(node_ptr& node) -> void;

private:
    vector<node_ptr> nodes_;
};

} // engine
