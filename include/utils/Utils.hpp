#pragma once

#include <string>

namespace Engine {

unsigned char* load_image(const char* filename, int* width, int* height, int* channels, int desired_channels);

std::string read_file(const char* filename);

}