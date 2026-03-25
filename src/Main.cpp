// Local includes
#include "Settings.h"
#include "GameCamera.h"
#include "World.h"

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Destroy The Dungeon");

    GameCamera camera;
    World world;

    DisableCursor();
    SetTargetFPS(MAX_FPS);

    while (!WindowShouldClose())
    {
        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advanced camera controls, it's recommended to compute camera movement manually
        camera.Update();

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