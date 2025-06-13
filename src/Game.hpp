#pragma once

#include "player/Player.hpp"
#include <cstdint>

struct Settings {
    Color PaddleColor;
    Color BallColor;
};

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Loop();

    uint32_t GetWindowHeight() const;
    uint32_t GetWindowWidth() const;

    static Game* Get();

public:
    Player players[2];
    bool isRunning = false;

    Settings settings;

private:
    uint32_t m_WindowWidth = 1280;
    uint32_t m_WindowHeight = 720;

    Color m_Color = { 37, 33, 61, 255 };
};