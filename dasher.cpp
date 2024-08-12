#include "dasher.h"


// All objects accelerate towards the ground at 9.8 m/s^2



int main() {
    // Windows dimensions
    const int screenWidth{800};
    const int screenHeight{450};    
    const int gravity{1'000}; // Acceleration due to gravity (pixels/s)/s

    // Scarfy variables
    Texture2D scarfy;
    Rectangle scarfyRect;
    Vector2 scarfyPos;


    InitializeGame(scarfy, scarfyRect, scarfyPos, screenHeight, screenWidth);

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRect{0.0f, 0.0f, (float)nebula.width/8, (float)nebula.height/8};
    Vector2 nebulaPos{screenWidth, screenHeight - nebulaRect.height};


    // Nebula X velocity in pixels per second
    int nebulaVelocity{-400};

    // Variables for nebula animation
        int nebulaFrame;
        const float nebulaUpdateTime = 1.0f / 12.0f;
        float nebulaRunningTime = 0.0f;

    // Animation frame
    int frame{0};

    // Time tracking variables for animation
    const float updateTime{1.0f / 12}; // Update the game at 12 frames / second
    float runningTime = 0.0f;

    bool isInAir{false};

    // jump velocity in pixels per second
    int jumpVelocity{-600};
    int velocity{0};
    
   


    // Main game loop
    while (!WindowShouldClose()) {
        const float deltaTime{GetFrameTime()};

        UpdatePlayer(scarfyPos, scarfyRect, isInAir, velocity, gravity, deltaTime, jumpVelocity);

        UpdatePlayerAnimation(runningTime, updateTime, scarfyRect, frame, deltaTime, isInAir);

        DrawGame(scarfy, nebula, scarfyRect, nebulaRect, scarfyPos, nebulaPos);


        // Update the nebula position
        nebulaPos.x += nebulaVelocity * deltaTime;



        // Update the nebula animation frame
        if (nebulaRunningTime >= nebulaUpdateTime) {
            nebulaRunningTime = 0.0f;
            nebulaRect.x = nebulaFrame * nebulaRect.width;
            nebulaFrame++;

            if (nebulaFrame > 7) {
                nebulaFrame = 0;
            }
        } else {
            nebulaRunningTime += deltaTime;
        }
    }
    CleanupGame(scarfy, nebula);
}



// Function definitions

void UpdatePlayerAnimation(float &runningTime, const float updateTime, Rectangle &scarfyRect, int &frame, const float deltaTime, bool isInAir)
{
    // Only update animation if the player is not in the air
    if (!isInAir)
    {
        // Update animation frame
        if (runningTime >= updateTime)
        {
            runningTime = 0.0f;
            scarfyRect.x = frame * scarfyRect.width;
            frame++;

            if (frame > 5)
            {
                frame = 0;
            }
        }
        else
        {
            runningTime += deltaTime;
        }
    }
}


void InitializeGame(Texture2D &scarfy, Rectangle &scarfyRect, Vector2 &scarfyPos, const int &screenHeight, const int &screenWidth) {
    InitWindow(screenWidth, screenHeight, "Dapper Dasher");
    scarfy = LoadTexture("textures/scarfy.png");
    scarfyRect = {0.0f, 0.0f, (float)scarfy.width / 6, (float)scarfy.height};
    scarfyRect.x = 0;
    scarfyRect.y = 0;
    scarfyPos.x = screenWidth / 2 - scarfyRect.width / 2;
    scarfyPos.y = screenHeight - scarfyRect.height;

    SetTargetFPS(60);
}

void UpdatePlayer(Vector2 &scarfyPos, Rectangle &scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime, const int jumpVelocity) {
    JumpCheck(scarfyPos, 450, scarfyRect, isInAir, velocity, gravity, deltaTime);

    if (IsKeyDown(KEY_SPACE) && !isInAir) {
        velocity = jumpVelocity; // Set velocity to jumpVelocity
    }

    // Update the player Y position
    scarfyPos.y += velocity * deltaTime;
}
void DrawGame(Texture2D scarfy, Texture2D nebula, Rectangle scarfyRect, Rectangle nebulaRect, Vector2 scarfyPos, Vector2 nebulaPos) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw the nebula
    DrawTextureRec(nebula, nebulaRect, nebulaPos, WHITE);


    // Draw the player
    DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);
    
    
    EndDrawing();
}

void CleanupGame(Texture2D scarfy, Texture2D nebula) {
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}

void JumpCheck(Vector2 &scarfyPos, const int screenHeight, Rectangle scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime) {
    // Check if the player is on the ground
    if (scarfyPos.y >= screenHeight - scarfyRect.height) {
        // player is on the ground
        isInAir = false;
        velocity = 0;
        scarfyPos.y = screenHeight - scarfyRect.height;
    } else {
        // player is in the air
        isInAir = true;
        velocity += gravity * deltaTime;
    }
}