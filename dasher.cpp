#include "dasher.h"

// All objects accelerate towards the ground at 9.8 m/s^2

int main() {
    // Windows dimensions
    const int screenWidth{800};
    const int screenHeight{450};
    const int gravity{1'000}; // Acceleration due to gravity (pixels/s)/s

    // Initialize game window and load scarfy texture
    Texture2D scarfy;
    InitializeGame(scarfy, screenHeight, screenWidth);

    // Scarfy variables
    AnimData scarfyData{
        {0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height}, // Rectangle
        {screenWidth / 2 - (float)scarfy.width / 12, screenHeight - (float)scarfy.height}, // Vector2 position
        0, // frame
        1.0f / 12.0f, // updateTime
        0.0f // runningTime
    };

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebulaData{
        {0.0f, 0.0f, (float)nebula.width / 8, (float)nebula.height / 8}, // Rectangle
        {screenWidth, screenHeight - (float)nebula.height / 8}, // Vector2 position
        0, // frame
        1.0f / 12.0f, // updateTime
        0.0f // runningTime
    };

    AnimData nebula2Data{
        {0.0f, 0.0f, (float)nebula.width / 8, (float)nebula.height / 8}, // Rectangle
        {screenWidth + 300, screenHeight - (float)nebula.height / 8}, // Vector2 position
        0, // frame
        1.0f / 16.0f, // updateTime
        0.0f // runningTime
    };

    // Nebula X velocity in pixels per second
    const int nebulaVelocity{-400};

    // jump velocity in pixels per second
    int jumpVelocity{-600};
    int velocity{0};

    bool isInAir{false};

    // Main game loop
    while (!WindowShouldClose()) {
        const float deltaTime{GetFrameTime()};

        UpdatePlayer(scarfyData, isInAir, velocity, gravity, deltaTime, jumpVelocity, screenHeight);

        UpdatePlayerAnimation(scarfyData, deltaTime, isInAir);

        nebulaData.pos.x += nebulaVelocity * deltaTime;
        nebula2Data.pos.x += nebulaVelocity * deltaTime;

        UpdateNebulaAnimation(nebulaData, deltaTime);
        UpdateNebulaAnimation(nebula2Data, deltaTime);

        DrawGame(scarfy, nebula, scarfyData, nebulaData, nebula2Data);
    }

    CleanupGame(scarfy, nebula);
}

// Function definitions

void InitializeGame(Texture2D &scarfy, const int &screenHeight, const int &screenWidth) {
    InitWindow(screenWidth, screenHeight, "Dapper Dasher");
    scarfy = LoadTexture("textures/scarfy.png");
    SetTargetFPS(60);
}

void UpdatePlayerAnimation(AnimData &data, const float deltaTime, bool isInAir) {
    // Only update animation if the player is not in the air
    if (!isInAir) {
        data.runningTime += deltaTime;
        if (data.runningTime >= data.updateTime) {
            data.runningTime = 0.0f;
            data.rec.x = data.frame * data.rec.width;
            data.frame++;
            if (data.frame > 5) {
                data.frame = 0;
            }
        }
    }
}

void UpdatePlayer(AnimData &data, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity, const int &screenHeight) {
    JumpCheck(data, screenHeight, isInAir, velocity, gravity, deltaTime);

    if (IsKeyPressed(KEY_SPACE) && !isInAir) {
        velocity = jumpVelocity;
    }

    data.pos.y += velocity * deltaTime;
}

void UpdateNebulaAnimation(AnimData &data, const float deltaTime) {
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime) {
        data.runningTime = 0.0f;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > 7) {
            data.frame = 0;
        }
    }
}

void DrawGame(Texture2D scarfy, Texture2D nebula, const AnimData &scarfyData, const AnimData &nebulaData, const AnimData &nebula2Data) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTextureRec(nebula, nebulaData.rec, nebulaData.pos, WHITE);
    DrawTextureRec(nebula, nebula2Data.rec, nebula2Data.pos, RED);
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
}

void CleanupGame(Texture2D scarfy, Texture2D nebula) {
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

void JumpCheck(AnimData &data, const int screenHeight, bool &isInAir, int &velocity, const int gravity, const float deltaTime) {
    if (data.pos.y >= screenHeight - data.rec.height) {
        isInAir = false;
        velocity = 0;
        data.pos.y = screenHeight - data.rec.height;
    } else {
        isInAir = true;
        velocity += gravity * deltaTime;
    }
}
