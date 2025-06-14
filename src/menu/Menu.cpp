#include "Menu.hpp"
#include "Game.hpp"
#include "menu/ButtonCollection.hpp"
#include "raylib.h"
#include <iostream>

Menu::Menu() {
    m_ButtonCollections[MenuType::Main] = ButtonCollection("Main");
    m_ButtonCollections[MenuType::Play] = ButtonCollection("Play");
    m_ButtonCollections[MenuType::Settings] = ButtonCollection("Settings");
    m_ButtonCollections[MenuType::Quit] = ButtonCollection("Quit");

    m_ButtonCollections.at(MenuType::Main).AddButton(Button("Play", {0.0f, 0.0f}, this, [this]{
        ChangeCurrentMenu(MenuType::Play);
    }));

    m_ButtonCollections.at(MenuType::Main).AddButton(Button("Quit", {0.0f, 60.0f}, this, [this]{
        currentMenu = MenuType::Quit;
    }));

    m_ButtonCollections.at(MenuType::Play).AddButton(Button("Player vs Player", {0.0f, 300.0f}, this, []{
        Game::Get()->StartGameplay(true);
    }));

    m_ButtonCollections.at(MenuType::Play).AddButton(Button("Player vs Bot", {0.0f, 350.0f}, this, []{
        Game::Get()->StartGameplay(false);
    }));

    m_ButtonCollections.at(MenuType::Main).Enable();
}

void Menu::Hide() {
    m_IsVisible = false;
}

void Menu::Show() {
    m_IsVisible = true;
}

void Menu::OnRender() {
    if (!m_IsVisible) {
        return;
    }

    for (auto& button : m_ButtonCollections.at(currentMenu).GetButtons()) {
        button.OnRender();
    }
}

void Menu::ChangeCurrentMenu(MenuType menuType) {
    m_ButtonCollections.at(currentMenu).Disable();
    currentMenu = menuType;
    m_ButtonCollections.at(currentMenu).Enable();

    selectedButton = 1;
}

void Menu::OnUpdate() {
    //m_ButtonCollections.at(currentMenu).Enable();

    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        selectedButton++;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        selectedButton--;
    }

    if (selectedButton > m_ButtonCollections.at(currentMenu).GetButtons().size()) {
        selectedButton = m_ButtonCollections.at(currentMenu).GetButtons().size();
    } else if (selectedButton < 1) {
        selectedButton = 1;
    }

    for (auto& button : m_ButtonCollections.at(currentMenu).GetButtons()) {
        button.OnUpdate();
    }
}