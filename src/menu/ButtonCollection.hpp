#pragma once

#include "menu/Button.hpp"
#include <cstdint>
#include <vector>
#include <string>

class Button;

class ButtonCollection {
public:
    ButtonCollection(const std::string& name);
    ButtonCollection() = default;

    void Enable();
    void Disable();

    void AddButton(const Button& button);
    std::vector<Button>& GetButtons();

    std::string& GetName();

private:
    std::string m_Name;
    std::vector<Button> m_Buttons;

    uint8_t id = 1;

    bool m_Enabled = false;
};