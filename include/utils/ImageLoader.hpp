#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"

namespace Engine {

class ImageLoader {
   public:
    ImageLoader();
    unsigned char* load(const char* filename, int* width, int* height,
                        int* channels, int desired_channels) const;
};

}  // namespace Engine