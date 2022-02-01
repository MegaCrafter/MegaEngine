#include "utils/ImageLoader.hpp"

namespace Engine {

ImageLoader::ImageLoader() { stbi_set_flip_vertically_on_load(1); }

unsigned char* ImageLoader::load(const char* filename, int* width, int* height,
                                 int* channels, int desired_channels) const {
    return stbi_load(filename, width, height, channels, desired_channels);
}

}  // namespace Engine