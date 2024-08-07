#pragma once

#include "raylib.h"
void InitializeGame(Texture2D &scarfy, Rectangle &scarfyRect, Vector2 &scarfyPos, const int &screenHeight, const int &screenWidth);
void UpdatePlayer(Vector2 &scarfyPos, Rectangle &scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity);
void DrawGame(Texture2D scarfy, Rectangle scarfyRect, Vector2 scarfyPos);
void CleanupGame(Texture2D scarfy);
void JumpCheck(Vector2 &scarfyPos, const int screenHeight, Rectangle scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime);
