#include "Game.hpp"
#include "ball/Ball.hpp"
#include "menu/Menu.hpp"
#include "menu/menus/MainMenu.hpp"
#include "nlohmann/json.hpp"
#include "player/Player.hpp"
#include "utils/Utils.hpp"

#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include "raylib.h"

// ᶠʳᵉᵃᵏʸ code

static Game* s_Instance = nullptr;

Game::Game() {
    if (!s_Instance) {
        s_Instance = this;
    } else {
        Error("There is more than one instance of game!", -1);
    }
}

Game::~Game() {
    delete ball;

    CloseAudioDevice();
    CloseWindow();
}

void Game::Loop() {
    ball = new Ball();

    m_Menu = std::make_shared<MainMenu>();

    m_CurrentTime = 0.0;
    m_PreviousTime = GetTime();
    m_DrawUpdateTime = 0.0;
    m_WaitTime = 0.0;

    PlayMusicStream(settings.BackgroundMusic);

    while (!WindowShouldClose() && m_Existing) {
        UpdateMusicStream(settings.BackgroundMusic);

        PollInputEvents();

        if (IsKeyPressed(KEY_ESCAPE)) {
            isRunning = false;
            SetCurrentMenu<MainMenu>();
        }

        if (m_Pvp && !m_PvpModeSet && m_ShouldSetPvp) {
            std::cout << "Making pvp";
            players[0] = Player(PlayerType::Player1);
            players[1] = Player(PlayerType::Player2);

            m_PvpModeSet = true;
        } else if (!m_Pvp && !m_PvpModeSet && m_ShouldSetPvp) {
            std::cout << "Making pvb";

            players[0] = Player(PlayerType::Player1);
            players[1] = Player(PlayerType::Bot);

            m_PvpModeSet = true;
        }

        if (!isRunning) {
            m_Menu->OnUpdate();
        } else {
            for (auto& player : players) {
                player.OnUpdate();
            }

            ball->OnUpdate();
        }

        BeginDrawing();

        ClearBackground(GetColor(0x000000ff));

        DrawTextureEx(settings.Background, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);

        for (auto& player : players) {
            player.OnRender();
        }

        ball->OnRender();

        std::string score1 = std::format("{}", m_Score.x);
        std::string score2 = std::format("{}", m_Score.y);

        int s1Size = MeasureText(score1.c_str(), 50);
        int s2Size = MeasureText(score2.c_str(), 50);

        DrawText(score1.c_str(), GetScreenWidth() / 4 - s1Size / 2, 0, 50,
                 BLACK);
        DrawText(score2.c_str(), GetScreenWidth() / 4 * 3 - s2Size / 2, 0, 50,
                 BLACK);

        if (!isRunning) {
            m_Menu->OnRender();
        }

        float frames = 1.0f / deltaTime;

        DrawText(TextFormat("FPS: %.1f", Round(frames)), 0, 0, 20, WHITE);

        EndDrawing();

        SwapScreenBuffer();

        m_CurrentTime = GetTime();
        m_DrawUpdateTime = m_CurrentTime - m_PreviousTime;

        if (settings.FPS > 0) {
            m_WaitTime = (1.0f / settings.FPS) - m_DrawUpdateTime;

            if (m_WaitTime > 0.0f) {
                WaitTime(m_WaitTime);
                m_CurrentTime = GetTime();
                deltaTime = static_cast<float>(m_CurrentTime - m_PreviousTime);
            } else {
                deltaTime = m_DrawUpdateTime;
            }

            m_PreviousTime = m_CurrentTime;
        }
    }

    UnloadMusicStream(settings.BackgroundMusic);
}

void Game::IncrementScore(Direction side) {
    if (side == Direction::Left) {
        m_Score.x += 1;
    } else {
        m_Score.y += 1;
    }
}

void Game::LoadSettingsFromFile(const std::filesystem::path& filePath) {
    // Parsing the json file
    std::ifstream file(filePath);
    nlohmann::json jsonFile = nlohmann::json::parse(file);

    std::stringstream str;

    std::string s1 = jsonFile.at("PaddleColor");
    s1.append("ff");
    str << s1;
    uint32_t paddleColor;
    str >> std::hex >> paddleColor;

    str.clear();
    s1.clear();

    s1 = jsonFile.at("BallColor");
    s1.append("ff");  // this is here so the transparency isn't 0
    str << s1;
    uint32_t ballColor;
    str >> std::hex >> ballColor;

    str.clear();
    s1.clear();

    std::string backgroundMusic = jsonFile.at("BackgroundMusic");

    settings.FPS = jsonFile.at("fps");
    settings.PaddleColor = GetColor(paddleColor);
    settings.BallColor = GetColor(ballColor);

    settings.BackgroundMusic = LoadMusicStream(backgroundMusic.c_str());
}

void Game::Quit() {
    m_Existing = false;
}

void Game::Run() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(m_WindowWidth, m_WindowHeight, "Pongus Maximus");

    InitAudioDevice();

    SetExitKey(KEY_F8);

    LoadSettingsFromFile("Assets/settings.json");

    settings.Background = LoadTexture("Assets/textures/backdrop.png");

    SetCurrentMenu<MainMenu>();

    Loop();
}

uint32_t Game::GetWindowHeight() const {
    return m_WindowHeight;
}

uint32_t Game::GetWindowWidth() const {
    return m_WindowWidth;
}

void Game::StartGameplay(bool pvp) {
    isRunning = true;
    m_Pvp = pvp;
    m_ShouldSetPvp = true;
}

Game* Game::Get() {
    return s_Instance;
}

uint32_t Foo(uint32_t bar) {
    return 7 * bar;
}
