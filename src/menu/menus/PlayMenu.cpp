#include "PlayMenu.hpp"
#include <format>
#include "Game.hpp"
#include "raylib.h"
#include "utils/Utils.hpp"

PlayMenu::PlayMenu() {
    // broooo
}

void PlayMenu::OnUpdate() {
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
    } else if (m_SelectedButton >= m_Options.size()) {
        m_SelectedButton = m_Options.size() - 1;
    }

    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
        // Player vs Player button
        if (m_SelectedButton == 0) {
            Game::Get()->StartGameplay(true);
        }

        // Player vs Bot button
        if (m_SelectedButton == 1) {
            Game::Get()->StartGameplay(false);
        }
    }
}

void PlayMenu::OnRender() {
    float y = 180;

    Renderer& renderer = Game::Get()->renderer;

    for (size_t i = 0; i < m_Options.size(); i++) {
        std::string selectedText;
        const char* option = m_Options.at(i);

        if (m_SelectedButton == i) {
            selectedText =
                std::format("> {} <", m_Options.at(m_SelectedButton));
            option = selectedText.c_str();
        }

        float center = CenterText(option, 70);

        Game::Get()->renderer.RenderText(option, center, y, 70, 0xffffffff);

        y += 50;
    }
}
