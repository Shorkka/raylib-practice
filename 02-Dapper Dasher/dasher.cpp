#include <iostream>
#include "raylib.h"

struct animData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(animData, int);
animData updateAnimData(animData, float, short);

int main()
{
    // Consts
    const float windowDimension[2]{512, 380};
    const int sizeOfNebula{50};
    InitWindow(windowDimension[0], windowDimension[1], " Practica 2");

    bool isInAir{false};
    int gravity{1'000}; // (p/s)/s

    // background
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");

    // scarfy vairables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    animData scarfyData{
        {0.0, 0.0, scarfy.width / 6, scarfy.height},                                                     // Rectangle rec
        {windowDimension[0] / 2 - scarfyData.rec.width / 2, windowDimension[1] - scarfyData.rec.height}, // Vector2 pos
        0,                                                                                               // Int frame
        1.0 / 12.0,                                                                                      // float updateTime
        0.0                                                                                              // float runningTime
    };
    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    animData nebulae[sizeOfNebula]{};

    for (int i = 0; i < sizeOfNebula; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width / 8;
        nebulae[i].rec.height = nebula.height / 8;
        nebulae[i].pos.y = windowDimension[1] - nebula.height / 8;
        nebulae[i].frame = 0.0;
        nebulae[i].updateTime = 1.0 / 16.0;
        nebulae[i].runningTime = 0;
        nebulae[i].pos.x = windowDimension[0] + i * 300;
    }
    
    float finishLine{nebulae[sizeOfNebula -1].pos.x};
    
    // Speed of nebula (pixel for seconds)
    int nebVel{-200};

    // Jump speed of scarfy
    const int jumpVel{-600};

    // Initial position
    int velocity{0};

    float bgX{};
    float mgX{};
    float fgX{};
    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        float dT{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dT;
        mgX -= 40 * dT;
        fgX -= 80 * dT;

        if(bgX <= -background.width*2){
            bgX = 0;
        }
        if(mgX <= -midground.width*2){
            mgX = 0;
        }

        if(fgX <= -foreground.width*2){
            fgX = 0;
        }


        Vector2 bg1Pos{bgX, 0.0};
        Vector2 mg1Pos{mgX, 0.0};
        Vector2 fg1Pos{fgX, 0.0};
        
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
        // Draw the background
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);


        // Update position
        if (isOnGround(scarfyData, windowDimension[1]))
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // scarfy is in the air
            velocity += gravity * dT;
            isInAir = true;
        }
        // Jump checkW                 X
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i].pos.x += nebVel * dT;
        }

        // finish Line update
        finishLine += nebVel * dT;


        for(animData nebula : nebulae){
            
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad, 
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec, scarfyRec)){
                collision = true;
            }
        }

        
        // update scarfy position
        scarfyData.pos.y += velocity * dT;

        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        // Neubla frame Update
        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }
        // Draw nebula
        if(collision){
            // lose the game
            DrawText("Game Over", windowDimension[0] / 2 - MeasureText("Game Over", 40) / 2, windowDimension[1] / 2, 40, RED);
        }else if(scarfyData.pos.x >= finishLine){
            DrawText("You win!!!", windowDimension[0] / 2 - MeasureText("You win!!!", 40) / 2, windowDimension[1] / 2, 40, WHITE);
        }
        else{
        

            for (int i = 0; i < sizeOfNebula; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }   
            // Draw scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
            
        }
        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}

bool isOnGround(animData data, int windowsHeight)
{
    return data.pos.y >= windowsHeight - data.rec.height;
}

animData updateAnimData(animData data, float dT, short maxFrame)
{
    // update running time
    data.runningTime += dT;
    if (data.runningTime >= data.updateTime)
    {
        // update animation frame
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}
