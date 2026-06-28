#include <iostream>
#include "raylib.h"

struct animData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Consts
    const short windowsWidth{512};
    const short windowsHeight{380};
    
    InitWindow(windowsWidth, windowsHeight, " Practica 2");

    bool gameEnd{false}; // if this variable is true game end
    bool isInAir{false}; 
    int gravity{1'000}; // (p/s)/s
    int count = 0;
    // scarfy vairables
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); 
    animData scarfyData{
        {0.0, 0.0, scarfy.width/6 , scarfy.height}, // Rectangle rec
        {windowsWidth/2 - scarfyData.rec.width/2, windowsHeight - scarfyData.rec.height}, // Vector2 pos
        0, // Int frame
        1.0/12.0, // float updateTime
        0.0 // float runningTime
    };
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    animData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowsWidth, windowsHeight - nebData.rec.height}, // Vector pos
        0, // int frame
        1.0/12.0, // float updateTime
        0.0 // float runningTime
    };
    // Second neubla
    animData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowsWidth + 300, windowsHeight - neb2Data.rec.height}, // Vector pos
        0, // int frame
        1.0/16.0, // float updateTime
        0.0 // float runningTime
    };

    // Speed of nebula (pixel for seconds)
    int nebVel{-600};
    int neb2Vel{-600};

    // Jump speed of scarfy
    const int jumpVel{-600};
    
    // Initial position    
    int velocity{0};
    
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
            if((scarfyData.pos.y  >= windowsHeight - scarfyData.rec.height)){
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
            nebData.pos.x += nebVel * dT; 
            neb2Data.pos.x+= neb2Vel * dT;

            // update scarfy position
            scarfyData.pos.y += velocity * dT;

            if(!isInAir){
                // update running time
                scarfyData.runningTime+= dT;
                if(scarfyData.runningTime >= scarfyData.updateTime){
                    // update animation frame
                    scarfyData.runningTime = 0.0;
                    scarfyData.rec.x= scarfyData.frame*scarfyData.rec.width;
                    scarfyData.frame++;
                    if(scarfyData.frame > 5){
                        scarfyData.frame  = 0;
                    }
                }
            }
            // Neubla frame Update
            nebData.runningTime += dT;
                if(nebData.runningTime >= nebData.updateTime){
                    nebData.runningTime = 0.0;
                    nebData.rec.x = nebData.frame*nebData.rec.width;
                    nebData.frame++;
                    if(nebData.frame > 7){
                        nebData.frame = 0;
                    
                }
            }
            neb2Data.runningTime += dT;
                if(neb2Data.runningTime >= neb2Data.updateTime){
                    nebData.runningTime = 0.0;
                    neb2Data.rec.x = neb2Data.frame*neb2Data.rec.width;
                    neb2Data.frame++;
                    if(neb2Data.frame > 7){
                        neb2Data.frame = 0;
                    
                }
            }
            // Draw nebula
            DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
            DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);
            // Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
            // stop drawing
            EndDrawing();
        }
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}