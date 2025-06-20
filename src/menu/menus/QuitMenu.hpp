#pragma once

#include "menu/Menu.hpp"
#include <array>
#include <cstddef>

class QuitMenu : public Menu {
public:
    QuitMenu();

    void OnUpdate() override;
    void OnRender() override;
private:
    size_t m_SelectedButton = 0;
    std::array<const char*, 2> m_Buttons = {"Yes", "No"};

    const char* text = "Are you sure you wish to quit? (Y/N)";
};