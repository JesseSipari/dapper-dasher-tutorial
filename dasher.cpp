#include "dasher.h"

// All objects accelerate towards the ground at 9.8 m/s^2

int main() {
    // Windows dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512; // screenWidth
    windowDimensions[1] = 380; // screenHeight
    const int gravity{1'000}; // Acceleration due to gravity (pixels/s)/s

    // Initialize game window and load scarfy texture
    Texture2D scarfy;
    InitializeGame(scarfy, windowDimensions);

    // Scarfy variables
    AnimData scarfyData{
        {0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height}, // Rectangle
        {windowDimensions[0] / 2 - (float)scarfy.width / 12, windowDimensions[1] - (float)scarfy.height}, // Vector2 position
        0, // frame
        1.0f / 12.0f, // updateTime
        0.0f // runningTime
    };

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfNebulae{6};
    AnimData nebulae[sizeOfNebulae];

    for(int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].rec.x = 0.0f;
        nebulae[i].rec.y = 0.0f;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height / 8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0f;
        nebulae[i].updateTime = 1.0f / 16.0f;
    }

    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }


    // Nebula X velocity in pixels per second
    const int nebulaVelocity{-400};

    // jump velocity in pixels per second
    int jumpVelocity{-600};
    int velocity{0};

    bool isInAir{false};

    // Main game loop
    while (!WindowShouldClose()) {
        const float deltaTime{GetFrameTime()};

        UpdatePlayer(scarfyData, isInAir, velocity, gravity, deltaTime, jumpVelocity, windowDimensions);

        UpdatePlayerAnimation(scarfyData, deltaTime, isInAir);

        UpdateAllNebulae(nebulae, sizeOfNebulae, nebulaVelocity, deltaTime);

        DrawGame(scarfy, nebula, scarfyData, nebulae, sizeOfNebulae);
    }

    CleanupGame(scarfy, nebula);
}

// Function definitions

void InitializeGame(Texture2D &scarfy, int windowDimensions[2]) {
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");
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

void UpdatePlayer(AnimData &data, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity, const int windowDimensions[2]) {
    JumpCheck(data, windowDimensions, isInAir, velocity, gravity, deltaTime);

    if (IsKeyPressed(KEY_SPACE) && !isInAir) {
        velocity = jumpVelocity;
    }

    data.pos.y += velocity * deltaTime;
}

void UpdateNebulaAnimation(AnimData &data, const float deltaTime, const int sizeOfNebulae) {

    for(int i = 0; i < sizeOfNebulae; i++) {
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

}

void UpdateAllNebulae(AnimData nebulae[], const int sizeOfNebulae, const int nebulaVelocity, const float deltaTime) {
    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].pos.x += nebulaVelocity * deltaTime;
        UpdateNebulaAnimation(nebulae[i], deltaTime, sizeOfNebulae);
    }
}

void DrawGame(Texture2D scarfy, Texture2D nebula, const AnimData &scarfyData, const AnimData nebulae[], int nebulaCount) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < nebulaCount; i++) {
        DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, (i % 2 == 0) ? WHITE : RED);
    }

    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

    EndDrawing();
}

void CleanupGame(Texture2D scarfy, Texture2D nebula) {
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

void JumpCheck(AnimData &data, const int windowDimensions[2], bool &isInAir, int &velocity, const int gravity, const float deltaTime) {
    if (data.pos.y >= windowDimensions[1] - data.rec.height) {
        isInAir = false;
        velocity = 0;
        data.pos.y = windowDimensions[1] - data.rec.height;
    } else {
        isInAir = true;
        velocity += gravity * deltaTime;
    }
}
