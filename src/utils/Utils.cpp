#include "utils/Utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"

#include <fstream>
#include <iostream>

namespace Engine {

unsigned char* load_image(const char* filename, int* width, int* height, int* channels, int desired_channels) {
    stbi_set_flip_vertically_on_load(1);
    return stbi_load(filename, width, height, channels, desired_channels);
}

std::string read_file(const char* filename) {
    std::ifstream file(filename);

    std::string contents;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            contents.append(line).append("\n");
        }
    }

    return contents;
}

}