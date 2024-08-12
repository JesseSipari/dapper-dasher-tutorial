#pragma once

#include "raylib.h"
void InitializeGame(Texture2D &scarfy, Rectangle &scarfyRect, Vector2 &scarfyPos, const int &screenHeight, const int &screenWidth);
void UpdatePlayerAnimation(float &runningTime, const float updateTime, Rectangle &scarfyRect, int &frame, const float deltaTime, bool isInAir);
void UpdatePlayer(Vector2 &scarfyPos, Rectangle &scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity);
void CleanupGame(Texture2D scarfy, Texture2D nebula);
void DrawGame(Texture2D scarfy, Texture2D nebula, Rectangle scarfyRect, Rectangle nebulaRect, Vector2 scarfyPos, Vector2 nebulaPos, Rectangle nebula2rect, Vector2 nebula2pos);
void JumpCheck(Vector2 &scarfyPos, const int screenHeight, Rectangle scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime);
