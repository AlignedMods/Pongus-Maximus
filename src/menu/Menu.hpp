#pragma once

#include <map>
#include <cstdint>

#include "Button.hpp"
#include "menu/ButtonCollection.hpp"

enum class MenuType {
    Main,
    Play,
    Settings,
    Quit
};

class ButtonCollection;
class Button;

class Menu {
public:
    Menu();
    ~Menu() = default;

    void OnUpdate();
    void OnRender();

    void Hide();
    void Show();

    void ChangeCurrentMenu(MenuType menuType);

public:
    uint8_t selectedButton = 1;
    MenuType currentMenu = MenuType::Main;

private:
    std::map<MenuType, ButtonCollection> m_ButtonCollections;

    bool m_IsVisible = true;
};