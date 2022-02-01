#pragma once

#include <string>

namespace Engine {

class FileReader {
   public:
    std::string read(const char* filename) const;
};

}  // namespace Engine