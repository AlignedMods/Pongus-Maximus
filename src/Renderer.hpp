#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include "raylib.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderText(const std::string& text,
                    float x,
                    float y,
                    float fontSize,
                    uint32_t color);

    Font& GetFont(float size);

private:
    uint32_t m_WindowWidth = 1280;
    uint32_t m_WindowHeight = 720;

    std::unordered_map<float, Font> m_Fonts;
};
