#include "utils/FileReader.hpp"

#include <fstream>
#include <iostream>
#include <string>

namespace Engine {

std::string FileReader::read(const char *filename) const {
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

}  // namespace Engine