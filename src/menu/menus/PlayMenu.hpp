#pragma once

#include <array>
#include <cstddef>
#include "menu/Menu.hpp"

class PlayMenu : public Menu {
public:
    PlayMenu();

    void OnUpdate() override;
    void OnRender() override;

private:
    size_t m_SelectedButton = 0;

    std::array<const char*, 2> m_Options = {"Player vs Player", "Player vs AI"};
};
