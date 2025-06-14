#include "ButtonCollection.hpp"
#include <vector>

ButtonCollection::ButtonCollection(const std::string& name) {
    m_Name = name;
}

std::string& ButtonCollection::GetName() {
    return m_Name;
}

std::vector<Button>& ButtonCollection::GetButtons() {
    return m_Buttons;
}

void ButtonCollection::Disable() {
    if (m_Enabled) {
        m_Enabled = false;

        for (auto& button : m_Buttons) {
            button.Hide();
        }
    } 
}

void ButtonCollection::Enable() {
    if (!m_Enabled) {
        m_Enabled = true;

        for (auto& button : m_Buttons) {
            button.Show();
        }
    } 
}

void ButtonCollection::AddButton(const Button& button) {
    Button temp = button;

    temp.id = id;
    id++;

    m_Buttons.push_back(temp);
}