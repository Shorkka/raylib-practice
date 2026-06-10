#include "raylib.h"
#include <iostream>

using namespace std;

// Structure for drawing the circle
struct Pelota
{
    int x;
    int y;
    float radio;
    float speedX;
    float speedY;
};

// Structure for drawing the rectangle
struct Rect
{
    float posX;
    float posY;
    float width;
    float height;
};

// Function prototypes
void circleAnimation(int width, int height, Pelota &myCircle);
void rectangleAnimation(int width, int height, Rect &myRect);

// Function overloading for 'moves'
void moves(Pelota &p, int, int);
void moves(Rect &r, int, int);

int main()
{
    // Window constants
    const short screenWidth = 800;
    const short screenHeight = 450;

    // Struct instances
    Pelota myCircle = {200, 200, 25.0, 5, 5};
    Rect myRectangle = {300, 0, 50, 50};

    // Collision Axe
    float l_axe_x{myRectangle.posX};
    float r_axe_x{myRectangle.posX + myRectangle.height};
    float u_axe_y{myRectangle.posY};
    float b_axe_y{myRectangle.posY - myRectangle.height};
    // Collision Circle
    float l_circle_x{myCircle.x - myCircle.radio};
    float r_circle_x{myCircle.x + myCircle.radio};
    float u_circle_y{myCircle.y - myCircle.radio};
    float b_circle_y{myCircle.y + myCircle.radio};

    // Collision variable
    bool collisionWhitAxe = 
    (b_axe_y >= u_circle_y) && 
    (u_axe_y <= b_circle_y) && 
    (l_axe_x <= r_circle_x) && 
    (r_axe_x >= l_circle_x);
    // Set FPS and create the window
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Update moves
    
    // Update Collision


    // Main game loop
    while (!WindowShouldClose())
    {
        if (collisionWhitAxe)
        {
            DrawText("Game Over...", screenWidth / 2, screenHeight / 2, 22, RED);
        }
        else
        {
            l_axe_x = myRectangle.posX;
            r_axe_x=myRectangle.posX + myRectangle.height;
            u_axe_y=myRectangle.posY;
            b_axe_y=myRectangle.posY - myRectangle.height;
            // Collision Circle
            l_circle_x=myCircle.x - myCircle.radio;
            r_circle_x=myCircle.x + myCircle.radio;
            u_circle_y=myCircle.y - myCircle.radio;
            b_circle_y=myCircle.y + myCircle.radio;
            collisionWhitAxe = 
                (b_axe_y >= u_circle_y) && 
                (u_axe_y <= b_circle_y) && 
                (l_axe_x <= r_circle_x) && 
                (r_axe_x >= l_circle_x);
            // Move the circle and rectangle
            moves(myCircle, screenWidth, screenHeight);
            moves(myRectangle, screenWidth, screenHeight);

            // Clear the screen and start drawing
            BeginDrawing();
            ClearBackground(WHITE);

            circleAnimation(screenWidth, screenHeight, myCircle);
            rectangleAnimation(screenWidth, screenHeight, myRectangle);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void circleAnimation(int width, int height, Pelota &myCircle)
{
    DrawCircle(myCircle.x, myCircle.y, myCircle.radio, BLUE);
}

void rectangleAnimation(int width, int height, Rect &myRect)
{
    DrawRectangle(myRect.posX, myRect.posY, myRect.width, myRect.height, RED);
}

// When a movement key is pressed, update the object's position within the width and height bounds
void moves(Pelota &p, int width, int height)
{
    // Collision Circle
    float l_circle_x{p.x - p.radio};
    float r_circle_x{p.x + p.radio};
    float u_circle_y{p.y - p.radio};
    float b_circle_y{p.y + p.radio};
    if (IsKeyDown(KEY_A) && l_circle_x > 0)
        p.x -= p.speedX;
    if (IsKeyDown(KEY_D) && r_circle_x < width)
        p.x += p.speedX;
    if (IsKeyDown(KEY_W) && u_circle_y > 0)
        p.y -= p.speedY;
    if (IsKeyDown(KEY_S) && b_circle_y < height)
        p.y += p.speedY;
}

void moves(Rect &r, int width, int height)
{
    // Collision Axe
    float l_axe_x{r.posX};
    float r_axe_x{r.posX - r.height};
    float u_axe_y{r.posY};
    float b_axe_y{r.posY + r.height};

    if (IsKeyDown(KEY_LEFT) && l_axe_x > 0)
        r.posX -= 5;
    if (IsKeyDown(KEY_RIGHT) && r_axe_x < width)
        r.posX += 5;
    if (IsKeyDown(KEY_UP) && u_axe_y > 0)
        r.posY -= 5;
    if (IsKeyDown(KEY_DOWN) && b_axe_y < height)
        r.posY += 5;
}