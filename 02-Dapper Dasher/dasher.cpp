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
animData updateAnimData(animData, float, int);

int main()
{
    // Consts
    const float windowDimension[2]{512, 380};
    const int sizeOfNebula{600};
    InitWindow(windowDimension[0], windowDimension[1], " Practica 2");

    bool gameEnd{false}; // if this variable is true game end
    bool isInAir{false};
    int gravity{1'000}; // (p/s)/s
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
    // Speed of nebula (pixel for seconds)
    int nebVel{-200};

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
            DrawText("Game Over", windowDimension[0] / 2 - MeasureText("Game Over", 20) / 2, windowDimension[1] / 2 - 10, 20, RED);
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

            for (int i = 0; i < sizeOfNebula; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
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