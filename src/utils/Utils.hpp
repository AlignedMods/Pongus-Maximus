#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Game.hpp"
#include "raylib.h"

inline static void Error(const std::string& message, int8_t errorCode) {
    std::cerr << "\n\033[1;31mERROR: \033[0m" << message << "\n\n";
    exit(errorCode);
}

template <typename T>
inline static void Debug(const T& message) {
#ifdef DEBUG
    std::cout << "\n\033[1;32mDEBUG: \033[0m" << message << "\n\n";
#endif
}

inline static float Round(float num) {
    return std::floor(num + 0.5f);
}

inline static float CenterText(const char* text, float fontSize) {
    Vector2 textSize = MeasureTextEx(Game::Get()->renderer.GetFont(fontSize),
                                     text, fontSize, 3);

    float center = static_cast<float>(GetScreenWidth()) / 2 - textSize.x / 2;

    return center;
}
