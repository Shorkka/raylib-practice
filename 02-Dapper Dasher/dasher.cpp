#include <iostream>
#include "raylib.h"

int main()
{
    // Consts
    const short windowsWidth{512};
    const short windowsHeight{380};
    
    InitWindow(windowsWidth, windowsHeight, " Practica 2");
    // if this variable is true game end
    bool gameEnd{false};
    bool isInAir{false};
    int gravity{1'000}; // (p/s)/s
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); 
    Rectangle scarfyRec;
    scarfyRec.height = scarfy.height;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowsWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowsHeight - scarfyRec.height;

    // Rectangle dimension
    // pixel for secon
    const int jumpVel{-600};
    // Initial position    

    int velocity{0};
    
    // main loop
    // Set FPS in 60
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        if (gameEnd)
        {
            BeginDrawing();
            ClearBackground(WHITE);
            DrawText("Game Over", windowsWidth / 2 - MeasureText("Game Over", 20) / 2, windowsHeight / 2 - 10, 20, RED);
            EndDrawing();
        }
        else
        {
            // delta time (time since last frame)
            float dT{GetFrameTime()};
            // Start drawing
            BeginDrawing();
            ClearBackground(WHITE);
            
            // Update position
            if((scarfyPos.y  >= windowsHeight - scarfyRec.height)){
                // rectangle is on the ground
                velocity = 0;
                isInAir = false;
            }
            else{
                // rectangle is in the air
                    velocity  += gravity * dT;
                    isInAir = true;
            }
            // Jump check
            if (IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                    velocity += jumpVel;
            } 
            
            // update the position
            scarfyPos.y += velocity * dT;
            
            DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
            
            // stop drawing
            EndDrawing();
        }
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
