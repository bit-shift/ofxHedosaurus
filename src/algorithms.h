#pragma once

#include "ofImage.h"

namespace image {

// ----------------------------------------------------------------------------

inline void set_channel(ofPixels& pixels, const size_t channel, 
                        const size_t color)
{
    auto i = channel;
	while (i < pixels.size())
	{
		pixels[i] = std::min(color, size_t{ 255 });
		i += 4;
	}
}

} // image
