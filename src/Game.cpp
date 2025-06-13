#include "Game.hpp"
#include "ball/Ball.hpp"
#include "player/Player.hpp"
#include "utils/Utils.hpp"
#include "nlohmann/json.hpp"

#include "raylib.h"
#include <cstdint>
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
    CloseWindow();
}

void Game::Loop() {
    Texture background = LoadTexture("Assets/backdrop.png");

    std::ifstream file("Assets/settings.json");
    nlohmann::json jsonFile = nlohmann::json::parse(file);

    std::stringstream str;

    std::string s1 = jsonFile.at("PaddleColor");
    s1.append("ff");
    str << s1;
    uint32_t paddleColor;
    str >> std::hex >> paddleColor;

    str.clear();
    std::string s2 = jsonFile.at("BallColor");
    s2.append("ff"); // this is here so the transparency isn't 0
    str << s2;
    uint32_t ballColor;
    str >> std::hex >> ballColor;

    settings.PaddleColor = GetColor(paddleColor);
    settings.BallColor = GetColor(ballColor);

    players[0] = Player(PlayerType::Player1);
    players[1] = Player(PlayerType::Player2);

    Ball b;

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_SPACE)) {
            isRunning = true;
        }

        if (isRunning) {
            for (auto& player : players) {
                player.OnUpdate();
            }

            b.OnUpdate();
        }

        BeginDrawing();

        ClearBackground(GetColor(0x000000ff));

        DrawTextureEx(background, {0.0f, 0.0f}, 0.0f, 1.0f, WHITE);

        for (auto& player : players) {
            player.OnRender();
        }

        b.OnRender();

        EndDrawing();
    }
}

void Game::Run() {
    InitWindow(m_WindowWidth, m_WindowHeight, "Pongus Maximus");

    SetExitKey(KEY_F8);

    SetTargetFPS(60);

    Loop();
}

uint32_t Game::GetWindowHeight() const {
    return m_WindowHeight;
}

uint32_t Game::GetWindowWidth() const {
    return m_WindowWidth;
}

Game* Game::Get() {
    return s_Instance;
}