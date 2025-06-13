#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <cstdint>

enum class PlayerType {
    Player1,
    Player2,
    Bot
};

class Player {
public:
    Player() = default;
    Player(PlayerType type);
    ~Player();

    void OnUpdate();
    void OnRender();

public:
    Rectangle rectangle;

private:
    Vector2 m_Position;
    Vector2 m_Velocity;

    Vector2 m_Size;

    PlayerType m_Type;

    Color m_Color;

    std::unordered_map<std::string, uint16_t> keys;
};