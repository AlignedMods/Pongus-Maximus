#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include "Renderer.hpp"
#include "ball/Ball.hpp"
#include "menu/Menu.hpp"
#include "player/Player.hpp"
#include "raylib.h"

struct Settings {
    Color PaddleColor;
    Color BallColor;

    float FPS;

    Texture Background;

    Music BackgroundMusic;
};

enum class Direction { Left, Right };

class Game {
public:
    Game();
    ~Game();

    void Run();
    void Loop();

    void StartGameplay(bool pvp);
    void Quit();

    // left is false, right is true (could've made this an enum but oh well)
    void IncrementScore(Direction side);

    template <typename T>
    void SetCurrentMenu() {
        m_Menu = std::make_shared<T>();
    }

    uint32_t GetWindowHeight() const;
    uint32_t GetWindowWidth() const;

    static Game* Get();

public:
    Player players[2];
    Ball* ball = nullptr;
    bool isRunning = false;

    float deltaTime = 0.0f;

    Settings settings;

    Renderer renderer;

private:
    void LoadSettingsFromFile(const std::filesystem::path& path);

private:
    uint32_t m_WindowWidth = 1280;
    uint32_t m_WindowHeight = 720;

    double m_PreviousTime;
    double m_CurrentTime;
    double m_DrawUpdateTime;
    double m_WaitTime;

    double m_Seconds = 0.0f;

    Vector2 m_Score = {0};

    bool m_Existing = true;
    bool m_Pvp = true;

    bool m_ShouldSetPvp = false;

    bool m_PvpModeSet = false;

    std::shared_ptr<Menu> m_Menu;

    Color m_Color = {37, 33, 61, 255};
};
