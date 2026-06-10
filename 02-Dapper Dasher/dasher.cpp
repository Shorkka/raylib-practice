#include <iostream>
#include "raylib.h"

int main(){
    // Consts
    const short windowsWidth{500}; 
    const short windowsHeight{250}; 
    
    // if this variable is true game end
    bool gameEnd = false;

    // Set FPS in 60 
    SetTargetFPS(60);
    // main loop
    InitWindow(windowsWidth, windowsHeight, " Practica 2");
    while(!WindowShouldClose()){
        if(gameEnd){
            BeginDrawing();
                
            EndDrawing();
        }else{
                BeginDrawing();
                ClearBackground(WHITE);
                
            EndDrawing();
        }
    }
    CloseWindow();
}
