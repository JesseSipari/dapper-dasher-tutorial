#include "raylib.h"
#include "dasher.h"


// All objects accelerate towards the ground at 9.8 m/s^2



int main() {
    // Windows dimensions
    const int screenWidth{800};
    const int screenHeight{450};

    // Initialize the window
    InitWindow(screenWidth, screenHeight, "Dapper Dasher!");

    
    const int gravity{1'000}; // Acceleration due to gravity (pixels/s)/s

    // Load the scarf texture
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;
    scarfyRect.width = scarfy.width/6;
    scarfyRect.height = scarfy.height;
    scarfyRect.x = 0;
    scarfyRect.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = screenWidth/2 - scarfyRect.width/2;
    scarfyPos.y = screenHeight - scarfyRect.height;




    bool isInAir{false};

    // jump velocity in pixels per second
    int jumpVelocity{-600};


    int velocity{0};

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
        const float deltaTime{GetFrameTime()};
        
        // Start drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);


        DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);
        JumpCheck(static_cast<Vector2&>(scarfyPos), screenHeight, scarfyRect, isInAir, velocity, gravity, deltaTime);

        if (IsKeyDown(KEY_SPACE) && !isInAir) {
            velocity += jumpVelocity;
        }

        
        // Update the player Y position
        scarfyPos.y += velocity * deltaTime;

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();

}

void JumpCheck(Vector2 &scarfyPos, const int screenHeight, Rectangle scarfyRect, bool &isInAir, int &velocity, const int gravity, const float deltaTime)
{
    // Check if the rectangle has hit the ground
    if (scarfyPos.y >= screenHeight - scarfyRect.height)
    {
        // Rectangle is on the ground
        isInAir = false;
        velocity = 0;
        scarfyPos.y = screenHeight - scarfyRect.height;
    }
    else
    {
        // Rectangle is in the air
        // Apply gravity to our velocity
        velocity += gravity * deltaTime;
        isInAir = true;
    }
}
