#include "menu/Button.hpp"
#include "menu/Menu.hpp"
#include "raylib.h"
#include <string>
#include <format>

Button::Button(const std::string& text, Vector2 position, Menu* menu, std::function<void()> callback) {
    m_Callback = callback;

    m_Menu = menu;
    m_Text = text;
    m_ActualText = m_Text;
    m_Position = position;
}

void Button::ChangeText(const std::string& text) {
    m_ActualText = text;
}

void Button::OnRender() {
    if (m_Visible) {
        float textWidth = MeasureText(m_Text.c_str(), 40.0f);

        DrawText(m_Text.c_str(), m_Position.x + GetScreenWidth() / 2.0f - textWidth / 2.0f, m_Position.y, 40.0f, BLACK);
    }
}

void Button::Show() {
    m_Visible = true;
}

void Button::Hide() {
    m_Visible = false;
}

void Button::OnUpdate() {
    if (id == m_Menu->selectedButton && m_Visible) {
        if (IsKeyPressed(KEY_ENTER)) {
            // call the callback function (bascially so i don't have to do all the handling in this function)
            m_Callback();
        }

        if (m_Text.find("<") == std::string::npos) {
            m_Text = std::format("> {} <", m_Text);   
        }
    } else {
        m_Text = m_ActualText;
    }
}