#include "raylib.h"
#include <stdbool.h>
#include <math.h>

int main(void)
{
    bool felloff = false;
    const int screenWidth = 800;
    const int screenHeight = 450;
    int score=0;
    float x = 0.0f, y = 0.0f, z = 3.0f, enemyspeed = 0.3f;
    float ex = 0.0f, ey = 0.0f, ez = -12.0f, musicvolume = 0.5f, gameovervolume = 0.0f;

    InitWindow(screenWidth, screenHeight, "3d box runner game");
    InitAudioDevice(); //initialise audio device, imp step
    
    // Load music file 
    Music music = LoadMusicStream("resources/password-infinity-123276.ogg");
    Music gameover = LoadMusicStream("resources/game-over-8-bit-chiptune-164330.ogg");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.5f);  // floating value shows volume which ranges from [0,1]
    PlayMusicStream(gameover);
    SetMusicVolume(gameover, 0.0f);
 

    // Define the camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 9.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { x, y, z};
    Vector3 enemyPosition = { ex, ey, ez };
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())    // Window will close if esc or cross button is pressed
    {
        UpdateMusicStream(music);
        // Update
        enemyPosition.z += enemyspeed;
        
        if(IsKeyDown(KEY_LEFT)){
            cubePosition.x-=0.2;
        }
        if(IsKeyDown(KEY_RIGHT)){
            cubePosition.x+=0.2;
        }
        if(enemyPosition.z>4 && !felloff){
            enemyPosition.x = (float)GetRandomValue(-6.7,6.7);
            enemyPosition.z = -12.0f;
            score++;
            if(score % 100 == 0 && score!=0) enemyspeed += 0.05; 
        }        
        if(cubePosition.x<-7 || cubePosition.x>6.7){
            felloff = true;
            SetMusicVolume(music, 0.0f);
            SetMusicVolume(gameover, 0.5f);
        }
        
        if(fabs(cubePosition.x - enemyPosition.x) <= 2.0f && fabs(cubePosition.y - enemyPosition.y) <= 2.0f && fabs(cubePosition.z - enemyPosition.z) <= 2.0f){
            enemyPosition.x = ex;
            enemyPosition.y = ey;
            enemyPosition.z = ez;
            cubePosition.x = x;
            cubePosition.y = y;
            cubePosition.z = z;            
            score = 0;
            enemyspeed = 0.3;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            
                if(!felloff){
                BeginMode3D(camera);
                    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED); //length height breadth
                    DrawCube(enemyPosition, 2.0f, 2.0f, 2.0f, WHITE);
                    DrawPlane((Vector3){0.0f,0.0f,0.0f},(Vector2){15,400},BLACK);
                EndMode3D();
                }
                else{
                    DrawText("You fell off!",screenWidth-MeasureText("You fell off!",80)-140,screenHeight/3,80,YELLOW);
                    DrawText(TextFormat("%i",score),screenWidth/2,screenHeight/2 + 20,80,MAROON);
                }    
                if(!felloff) DrawText(TextFormat("%i",score),20,10,80,MAROON);

        EndDrawing();
    }

    UnloadMusicStream(gameover);
    UnloadMusicStream(music);
    CloseWindow();        // Close window
    CloseAudioDevice();

    return 0;
}