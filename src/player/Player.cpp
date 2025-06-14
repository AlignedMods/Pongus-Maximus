#include "Player.hpp"
#include "raylib.h"
#include "raymath.h"

#include "Game.hpp"
#include <algorithm>
#include <iostream>

Player::Player(PlayerType type) {
    m_Size = {20.0f, 80.0f};

    m_Type = type;

    m_Color = Game::Get()->settings.PaddleColor;

    switch (m_Type) {
        case PlayerType::Player1: {
            keys["up"] = KEY_W;
            keys["down"] = KEY_S;

            m_Position = { 10.0f, Game::Get()->GetWindowHeight() / 2.0f - m_Size.y / 2.0f};
            break;
        }

        case PlayerType::Player2: {
            keys["up"] = KEY_UP;
            keys["down"] = KEY_DOWN;

            m_Position = { Game::Get()->GetWindowWidth() - 10.0f - m_Size.x, Game::Get()->GetWindowHeight() / 2.0f - m_Size.y / 2.0f};
            break;
        }

        case PlayerType::Bot: {
            keys["up"] = KEY_NULL;
            keys["down"] = KEY_NULL;

            m_Position = { Game::Get()->GetWindowWidth() - 10.0f - m_Size.x, Game::Get()->GetWindowHeight() / 2.0f - m_Size.y / 2.0f};
            break;
        }
    }

    rectangle = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};
    
    m_Velocity = Vector2Zero();
}

Player::~Player() {

}

void Player::OnUpdate() {
    //std::cout << (int)m_Type << '\n';

    if (m_Type == PlayerType::Player1 || m_Type == PlayerType::Player2) {
        if (IsKeyDown(keys.at("down"))) {
            m_Velocity.y = std::min(m_Velocity.y + 1.0f, 5.0f);
        } else if (IsKeyDown(keys.at("up"))) {
            m_Velocity.y = std::max(m_Velocity.y - 1.0f, -5.0f);
        } else {
            if (m_Velocity.y > 0.0f) {
                m_Velocity.y -= 0.5f;
            } else if (m_Velocity.y < 0.0f) {
                m_Velocity.y += 0.5f;
            }
        }
    } else if (m_Type == PlayerType::Bot) {
        if (Game::Get()->ball->m_Position.y > m_Position.y) {
            m_Velocity.y = std::min(m_Velocity.y + 1.0f, 5.0f);
        } else if (Game::Get()->ball->m_Position.y < m_Position.y) {
            m_Velocity.y = std::max(m_Velocity.y - 1.0f, -5.0f);
        } else {
            if (m_Velocity.y > 0.0f) {
                m_Velocity.y -= 0.5f;
            } else if (m_Velocity.y < 0.0f) {
                m_Velocity.y += 0.5f;
            }
        }
    }

    if (m_Position.y < 0.0f && m_Velocity.y < 0.0f) {
        
    } else if (m_Position.y + m_Size.y > GetScreenHeight() && m_Velocity.y > 0.0f) {

    } else {
        m_Position = Vector2Add(m_Position, m_Velocity);
    }

    rectangle = {m_Position.x, m_Position.y, m_Size.x, m_Size.y};
}

void Player::OnRender() {
    DrawRectangleRounded(rectangle, 2.0f, 50, m_Color);
}