/*
    -> make window
    -> make ball
    -> make middle line
    -> make paddles
    -> give ball movement 
    -> make ball bounce off of edges of window 
    -> give paddles movement 
    -> check if paddle has collided with ball 
    -> automate one of the paddles 
    -> add score

*/

#include "raylib.h"
#include <stdbool.h>
#include <time.h>
#define screenWidth 800
#define screenHeight 450

int ball_x = screenWidth/2, ball_y = screenHeight/2;
int speed_x = 10,speed_y = 10;
float radius = 15;
int paddlespeed = 10;
int pscore = 0, cscore = 0;

struct paddlemove{
    int paddle_x, paddle_y;
};

struct paddlemove player;
struct paddlemove comp;

void movepaddleup(int *y){
    *y -= paddlespeed;
    if(*y<=0) *y=0;
}
void movepaddledown(int *y){
    *y += paddlespeed;
    if(*y + 100>=screenHeight) *y=screenHeight-100;
}

void comppaddlemove(int *y){
    if(*y-5>ball_y){ movepaddleup(y);} //check if center of paddle is greater than ball center then, move up
    if(*y-5<=ball_y){ movepaddledown(y);} //check if center of paddle is lesser than ball center then, move down
}

void ballmovement(){
    ball_x += speed_x;
    ball_y += speed_y;
    if(ball_x-radius<=0) cscore++;
    if(ball_x+radius>=screenWidth) pscore++;
    if(ball_y + radius>=screenHeight || ball_y - radius <=0){
        speed_y *=-1;
    }
    if(ball_x + radius>=screenWidth || ball_x - radius <=0){
        speed_x *=-1;
    }
}

int main(void)
{
    player.paddle_x = 10;
    player.paddle_y = screenHeight/2-20;

    comp.paddle_x = screenWidth-17;
    comp.paddle_y = screenHeight/2-20;

    InitWindow(screenWidth, screenHeight, "Raylib first try-Pong");

    SetTargetFPS(70);
    double startTime = GetTime();
    while (GetTime() - startTime < 2) {
        BeginDrawing();
            DrawText("Get ready...", screenWidth / 2 - 100, screenHeight / 2 - 50, 30, RAYWHITE);
            ClearBackground(BLACK);
        EndDrawing();
    }
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
            ballmovement(); //give ball movement
            if(IsKeyDown((KEY_UP))){
                movepaddleup(&player.paddle_y);
            }
            if(IsKeyDown((KEY_DOWN))){
                movepaddledown(&player.paddle_y);
            }
            comppaddlemove(&comp.paddle_y);
            
            
            
            ClearBackground(BLACK); //so ball doesn't leave trace
            
            
            
            
            if(CheckCollisionCircleRec((Vector2){ball_x,ball_y},radius, (Rectangle){player.paddle_x,player.paddle_y,7,100})==true){
                speed_x *= -1;
            }
            if(CheckCollisionCircleRec((Vector2){ball_x,ball_y},radius, (Rectangle){comp.paddle_x,comp.paddle_y,7,100})==true){
                speed_x *= -1;
            }
            
        // Draw
        BeginDrawing();
            DrawRectangle(player.paddle_x,player.paddle_y,7,100,RAYWHITE); //draw left paddle
            DrawRectangle(comp.paddle_x,comp.paddle_y,7,100,RAYWHITE); //draw right paddle
            DrawCircle(ball_x,ball_y,radius,RAYWHITE); //draw ball
            DrawLine(screenWidth/2,0,screenWidth/2,screenHeight,GOLD); //draw middle line
            DrawText(TextFormat("%i",pscore),screenWidth/4,10,80,RAYWHITE);
            DrawText(TextFormat("%i",cscore),3*screenWidth/4,10,80,RAYWHITE);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}