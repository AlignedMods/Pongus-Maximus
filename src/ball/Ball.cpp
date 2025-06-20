#include "Ball.hpp"
#include "Game.hpp"
#include "raylib.h"
#include "raymath.h"

Ball::Ball() {
    m_Position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    m_Velocity = {-420.0f, 420.0f};

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

    if (m_Position.y + m_Radius > GetScreenHeight() ||
        m_Position.y - m_Radius < 0.0f) {
        m_Velocity.y *= -1.0f;
    }

    if (m_Position.x + m_Radius > GetScreenWidth()) {
        m_Velocity = Vector2Multiply(m_Velocity, {-1.0f, -1.0f});
        Reset();
        Game::Get()->IncrementScore(Direction::Left);
    } else if (m_Position.x - m_Radius < 0.0f) {
        m_Velocity = Vector2Multiply(m_Velocity, {-1.0f, -1.0f});
        Reset();
        Game::Get()->IncrementScore(Direction::Right);
    }

    m_Position = Vector2Add(
        m_Position, Vector2Multiply(m_Velocity, {Game::Get()->deltaTime,
                                                 Game::Get()->deltaTime}));
}

void Ball::Reset() {
    m_Position = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
}
