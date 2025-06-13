#pragma once

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

inline static void Error(const std::string& message, int8_t errorCode) {
    std::cerr << "\n\033[1;31ERROR: \033[0m" << message << "\n\n";
    exit(errorCode);
}