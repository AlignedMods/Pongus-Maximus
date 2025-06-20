#pragma once

#include "menu/Menu.hpp"
#include <array>
#include <cstddef>

class MainMenu : public Menu {
public:
    MainMenu();

    void OnUpdate() override;
    void OnRender() override;
private:
    size_t m_SelectedButton = 0;
    std::array<const char*, 3> m_Buttons = {"Play", "Settings", "Quit"};
};