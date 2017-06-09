#pragma once

#include <constants.h>
#include <render_graph.h>

#include "FboSource.h"

#include <ofMain.h>

namespace engine {

using FboSource = ofx::piMapper::FboSource;

// ----------------------------------------------------------------------------

namespace util {

inline size_t bpm_to_interval_ms(const size_t bpm)
{
	auto bpms = bpm / 60.f / 1000.f;
    return std::ceil( 1.f / bpms );
}

} // util

//-----------------------------------------------------------------------------

using modulation_fn = std::function<void(ofParameter<size_t>&)>;

struct modulator {
    modulator(const std::string name, modulation_fn fn) : name_(name), fn_(fn) {}

    std::string name_;
    modulation_fn fn_;
};

//-----------------------------------------------------------------------------

class modulation {
public:
    modulation(node_ptr node) : node_(node) {}

    void step()
    {
        for (auto& modulator: modulators_)
        {
            modulator.fn_(node_->parameters().get<size_t>(modulator.name_));
        }
    }

    void add_modulator(modulator modulator)
    {
        modulators_.push_back(modulator);
    }

private:
    node_ptr node_;
    std::vector<modulator> modulators_;
};

//-----------------------------------------------------------------------------

class sequencer {
public:
    sequencer()
    {
        parameters_.add(bpm_.set("bpm", 60));
        parameters_.add(running_.set("running", false));
    }

    void update()
    {
        auto time = ofGetElapsedTimeMillis();
        auto interval = util::bpm_to_interval_ms(bpm_.get());

        time_delta_ += time - prev_time_;
        
        if (time_delta_ > interval)
        {
            step();
            time_delta_ = 0;
        }

        prev_time_ = time;
    }

    void step()
    {
        if (running_.get())
        {
            for (auto source: sources_)
                source->modulate();
        }
    }

    void add_source(std::shared_ptr<FboSource> source)
    {
        sources_.push_back(source);
    }

    ofParameterGroup& parameters() { return parameters_; }

private:
    size_t prev_time_ = 0;
    size_t time_delta_ = 0;

    ofParameterGroup parameters_;
    ofParameter<size_t> bpm_;
    ofParameter<bool> running_;

    std::vector<std::shared_ptr<FboSource>> sources_;
};

} // engine