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

    // scarfy vairables
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); 
    Rectangle scarfyRec;
    scarfyRec.height = scarfy.height;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowsWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowsHeight - scarfyRec.height;

    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowsWidth, windowsHeight - nebRec.height};
    
    // Speed of nebula (pixel for seconds)
    int nebVel{-600};

    // Nebula animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime;
    // pixel for secon
    const int jumpVel{-600};
    
    // Initial position    
    int velocity{0};
    
    int frame{}; // animation frame

    // amount of time before we update the animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime{};
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
                // scarfy is in the air
                    velocity  += gravity * dT;
                    isInAir = true;
            }
            // Jump checkW                 X
            if (IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                    velocity += jumpVel;
            } 
            
            // update nebula position
            nebPos.x += nebVel * dT; 

            // update scarfy position
            scarfyPos.y += velocity * dT;
            if(!isInAir){
                // update running time
                runningTime+= dT;
                if(runningTime >= updateTime){
                    // update animation frame
                    scarfyRec.x= frame*scarfyRec.width;
                    frame++;
                    if(frame > 5){
                        frame = 0;
                    }
                    runningTime = 0.0;
                }
            }
            // Neubla frame Update
            nebRunningTime += dT;
            if(!isInAir){
                if(nebRunningTime >= nebUpdateTime){
                    nebRunningTime = 0.0;
                    nebRec.x = nebFrame*nebRec.width;
                    nebFrame++;
                    if(nebFrame > 8){
                        nebFrame = 0;
                    }
                    nebRunningTime = 0.0;
                }

            }
            // Draw nebula
            DrawTextureRec(nebula, nebRec, nebPos, WHITE);

            // Draw scarfy
            DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
            // stop drawing
            EndDrawing();
        }
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
