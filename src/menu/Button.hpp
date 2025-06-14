#pragma once

#include "raylib.h"
#include <functional>
#include <string>

#include "Menu.hpp"

class Menu;

class Button {
public:
    Button(const std::string& text, Vector2 position, Menu* menu, std::function<void()> callback);
    Button() = default;
    ~Button() = default;

    void OnUpdate();
    void OnRender();

    void Hide();
    void Show();

    void ChangeText(const std::string& text);

public:
    uint8_t id;

private:
    std::string m_Text;
    std::string m_ActualText;
    Vector2 m_Position;

    bool m_Visible = false;

    std::function<void()> m_Callback;

    Menu* m_Menu = nullptr;
};