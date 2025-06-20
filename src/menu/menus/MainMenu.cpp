#include "MainMenu.hpp"
#include <cstddef>
#include <format>
#include "Game.hpp"
#include "QuitMenu.hpp"
#include "Renderer.hpp"
#include "menu/menus/PlayMenu.hpp"
#include "raylib.h"
#include "utils/Utils.hpp"

MainMenu::MainMenu() {
    Debug("Created Main Menu!");
}

void MainMenu::OnUpdate() {
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
        // Play button
        if (m_SelectedButton == 0) {
            Game::Get()->SetCurrentMenu<PlayMenu>();
        }

        // Settings button
        if (m_SelectedButton == 1) {
        }

        // Quit button
        if (m_SelectedButton == 2) {
            Game::Get()->SetCurrentMenu<QuitMenu>();
        }
    }
}

void MainMenu::OnRender() {
    float y = 180;

    Renderer& renderer = Game::Get()->renderer;

    for (size_t i = 0; i < m_Buttons.size(); i++) {
        std::string selectedText;
        const char* option = m_Buttons.at(i);

        if (m_SelectedButton == i) {
            selectedText =
                std::format("> {} <", m_Buttons.at(m_SelectedButton));
            option = selectedText.c_str();
        }

        float center = CenterText(option, 70);

        Game::Get()->renderer.RenderText(option, center, y, 70, 0xffffffff);

        y += 50;
    }
}
