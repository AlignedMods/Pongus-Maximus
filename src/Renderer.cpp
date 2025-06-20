#include "Renderer.hpp"
#include <cstdint>
#include "raylib.h"

Renderer::Renderer() {
    // constructor code (coming soon)
}

Renderer::~Renderer() {
    // idk
}

Font& Renderer::GetFont(float size) {
    if (!m_Fonts.contains(size)) {
        // Wanted font size is not yet loaded

        m_Fonts[size] =
            LoadFontEx("Assets/fonts/CreatoDisplay/CreatoDisplay-Medium.ttf",
                       size, nullptr, 0);
    }

    return m_Fonts.at(size);
}
void Renderer::RenderText(const std::string& text,
                          float x,
                          float y,
                          float fontSize,
                          uint32_t color) {
    Font* font = nullptr;

    if (!m_Fonts.contains(fontSize)) {
        // Wanted font size is not yet loaded

        m_Fonts[fontSize] =
            LoadFontEx("Assets/fonts/CreatoDisplay/CreatoDisplay-Medium.ttf",
                       fontSize, nullptr, 0);
    }

    font = &m_Fonts.at(fontSize);

    DrawTextEx(*font, text.c_str(), {x, y}, fontSize, 3, GetColor(color));
}
