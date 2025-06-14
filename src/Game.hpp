#pragma once

#include "ball/Ball.hpp"
#include "menu/Menu.hpp"
#include "player/Player.hpp"
#include "raylib.h"
#include <cstdint>
#include <filesystem>

struct Settings {
    Color PaddleColor;
    Color BallColor;

    Texture Background;
};

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Loop();

    void StartGameplay(bool pvp);
    void Quit();

    // left is false, right is true (could've made this an enum but oh well)
    void IncrementScore(bool leftOrRight);

    uint32_t GetWindowHeight() const;
    uint32_t GetWindowWidth() const;

    static Game* Get();

public:
    Player players[2];
    Ball* ball = nullptr;
    bool isRunning = false;

    Settings settings;

private:
    void LoadSettingsFromFile(const std::filesystem::path& path);

private:
    uint32_t m_WindowWidth = 1280;
    uint32_t m_WindowHeight = 720;

    Vector2 m_Score = { 0 };

    bool m_Existing = true;
    bool m_Pvp = true;

    bool m_ShouldSetPvp = false;

    bool m_PvpModeSet = false;

    Menu* m_Menu = nullptr;

    Color m_Color = { 37, 33, 61, 255 };
};