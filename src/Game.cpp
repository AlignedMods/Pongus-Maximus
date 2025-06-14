#include "Game.hpp"
#include "ball/Ball.hpp"
#include "menu/Menu.hpp"
#include "player/Player.hpp"
#include "utils/Utils.hpp"
#include "nlohmann/json.hpp"

#include "raylib.h"
#include <cstdint>
#include <format>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <sstream>

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
    delete m_Menu;

    CloseWindow();
}

void Game::Loop() {
    ball = new Ball();
    m_Menu = new Menu();

    while (!WindowShouldClose() && m_Existing) {
        std::cout << m_PvpModeSet << '\n';

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

        DrawText(score1.c_str(), GetScreenWidth() / 4 - s1Size / 2, 0, 50, BLACK);
        DrawText(score2.c_str(), GetScreenWidth() / 4 * 3 - s2Size / 2, 0, 50, BLACK);

        if (!isRunning) {
            m_Menu->OnRender();
        }

        EndDrawing();
    }
}

void Game::IncrementScore(bool leftOrRight) {
    if (leftOrRight == false) {
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
    s1.append("ff"); // this is here so the transparency isn't 0
    str << s1;
    uint32_t ballColor;
    str >> std::hex >> ballColor;

    settings.PaddleColor = GetColor(paddleColor);
    settings.BallColor = GetColor(ballColor);
}

void Game::Quit() {
    m_Existing = false;
}

void Game::Run() {
    InitWindow(m_WindowWidth, m_WindowHeight, "Pongus Maximus");

    SetExitKey(KEY_F8);

    SetTargetFPS(60);

    LoadSettingsFromFile("Assets/settings.json");

    settings.Background = LoadTexture("Assets/backdrop.png");

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