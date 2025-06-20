#include "menu/menus/QuitMenu.hpp"
#include <cstddef>
#include <cstdint>
#include <format>
#include "Game.hpp"
#include "Renderer.hpp"
#include "menu/menus/MainMenu.hpp"
#include "raylib.h"
#include "utils/Utils.hpp"

QuitMenu::QuitMenu() {
    Debug("Created Main Menu!");
}

void QuitMenu::OnUpdate() {
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        m_SelectedButton++;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        m_SelectedButton--;
    }

    // unsigned int moment (i know i could easily fix this but it's funnier this
    // way) this is equivalent to doing m_SelectedButton < 0, but this is
    // unsigned so numbers can't be smaller than 0
    if (m_SelectedButton > 18440000000000000) {
        m_SelectedButton = 0;
    } else if (m_SelectedButton >= m_Buttons.size()) {
        m_SelectedButton = m_Buttons.size() - 1;
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        // Yes button
        if (m_SelectedButton == 0) {
            Game::Get()->Quit();
        }

        // No button
        if (m_SelectedButton == 1) {
            Game::Get()->SetCurrentMenu<MainMenu>();
        }
    }

    if (IsKeyPressed(KEY_Y)) {
        Game::Get()->Quit();
    }

    if (IsKeyPressed(KEY_N)) {
        Game::Get()->SetCurrentMenu<MainMenu>();
    }
}

void QuitMenu::OnRender() {
    uint32_t y = 180;

    Renderer& renderer = Game::Get()->renderer;

    const float center = CenterText(text, 60);
    renderer.RenderText(text, center, 130, 60, 0xffffffff);

    for (size_t i = 0; i < m_Buttons.size(); i++) {
        std::string selectedText;
        const char* option = m_Buttons.at(i);

        if (m_SelectedButton == i) {
            selectedText =
                std::format("> {} <", m_Buttons.at(m_SelectedButton));
            option = selectedText.c_str();
        }

        int center = CenterText(option, 40);

        renderer.RenderText(option, center, y, 40, 0xffffffff);
        y += 50;
    }
}
