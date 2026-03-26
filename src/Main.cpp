// Local includes
#include "GameCamera.h"
#include "World.h"

int main(void)
{
    const int FPS_MAX = 60;
    
    InitWindow(0, 0, "Destroy The Dungeon");

    GameCamera camera;
    World world;

    DisableCursor();
    SetTargetFPS(FPS_MAX);

    while (!WindowShouldClose())
    {
        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advanced camera controls, it's recommended to compute camera movement manually
        camera.Update(GetFrameTime());

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(*camera.GetCamera());
            {
                world.DrawWorld();
            }
            EndMode3D();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}