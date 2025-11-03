#include <stdexcept>

#include "dr4/Font.hpp"

#include "common/ErrorHandler.hpp"

void optor::dr4::Font::loadFromFile(const std::string& path)
{
    ERROR_HANDLE([this, &path](){
        if (!font_.loadFromFile(path)) {
            throw std::runtime_error("Can't load font from file");
        }
    });
}