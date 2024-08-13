#pragma once

#include "raylib.h"

struct AnimData {
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

void InitializeGame(Texture2D &scarfy, int windowDimensions[2]);
void UpdatePlayerAnimation(AnimData &data, const float deltaTime, bool isInAir);
void UpdatePlayer(AnimData &data, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity, const int windowDimensions[2]);
void UpdateNebulaAnimation(AnimData &data, const float deltaTime);
void CleanupGame(Texture2D scarfy, Texture2D nebula);
void DrawGame(Texture2D scarfy, Texture2D nebula, const AnimData &scarfyData, const AnimData nebulae[], int nebulaCount);
void JumpCheck(AnimData &data, const int windowDimensions[2], bool &isInAir, int &velocity, const int gravity, const float deltaTime);
