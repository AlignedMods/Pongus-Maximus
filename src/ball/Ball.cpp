#include "Ball.hpp"
#include "Game.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

Ball::Ball() {
    m_Position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    m_Velocity = {7.0f, 7.0f};

    m_Color = Game::Get()->settings.BallColor;
}

void Ball::OnRender() {
    DrawCircle(m_Position.x, m_Position.y, m_Radius, m_Color);
}

Vector2& Ball::GetVelocity() {
    return m_Velocity;
}

void Ball::OnUpdate() {
    for (auto& player : Game::Get()->players) {
        if (CheckCollisionCircleRec(m_Position, m_Radius, player.rectangle)) {
            m_Velocity.x *= -1.0f;
        }
    }
    
    if (m_Position.y + m_Radius > GetScreenHeight() || m_Position.y - m_Radius < 0.0f) {
        m_Velocity.y *= -1.0f;
    }

    if (m_Position.x + m_Radius > GetScreenWidth()) {
        m_Velocity = Vector2Multiply(m_Velocity, {-1.0f, -1.0f});
        Reset();
        Game::Get()->IncrementScore(false);
    } else if (m_Position.x - m_Radius < 0.0f) {
        m_Velocity = Vector2Multiply(m_Velocity, {-1.0f, -1.0f});
        Reset();
        Game::Get()->IncrementScore(true);
    }

    m_Position = Vector2Add(m_Position, m_Velocity);
}

void Ball::Reset() {
    m_Position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
}