#pragma once

#include <ofMain.h>

#include <constants.h>
#include <algorithms.h>


namespace engine {

//-----------------------------------------------------------------------------

class sequencer {
public:
    sequencer()
    {
        parameters_.add(alpha_.set("bpm", 0));
    }

    void update()
    {

    }

    ofParameterGroup& parameters() { return parameters_; }

private:
    ofParameterGroup parameters_;
    ofParameter<size_t> bpm_;
};

} // engine