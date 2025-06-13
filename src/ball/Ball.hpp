#pragma once

#include "raylib.h"

class Ball {
public:
    Ball();
    ~Ball() = default;

    void OnRender();
    void OnUpdate();

    void Reset();

private:
    Vector2 m_Position;
    Vector2 m_Velocity;

    float m_Radius = 12.0f;

    Color m_Color;
};