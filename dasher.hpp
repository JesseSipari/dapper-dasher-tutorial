#ifndef DASHER_HPP
#define DASHER_HPP

#include "raylib.h"

// Struct to hold animation data
struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

// Function declarations

void InitializeGame(Texture2D &scarfy, int windowDimensions[2]);

void UpdatePlayerAnimation(AnimData &data, const float deltaTime, const int windowDimensions[2]);

void UpdatePlayer(AnimData &data, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity, const int windowDimensions[2]);

void UpdateNebulaAnimation(AnimData &data, const float deltaTime, const int sizeOfNebulae);

void UpdateAllNebulae(AnimData nebulae[], const int sizeOfNebulae, const int nebulaVelocity, const float deltaTime);

void DrawGame(Texture2D scarfy, Texture2D nebula, const AnimData &scarfyData, const AnimData nebulae[], int nebulaCount);

void CleanupGame(Texture2D scarfy, Texture2D nebula);

bool isOnGround(const AnimData data, const int windowDimensions[2]);

#endif // DASHER_HPP
