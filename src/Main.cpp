// Local includes
#include "Utils.h"
#include "Settings.h"
#include "GameCamera.h"

// C++ binaries
#include "stdlib.h"

#define MAX_COLUMNS 20

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Destroy The Dungeon");

    GameCamera *camera = new GameCamera();

    // Generates some random columns
    float heights[MAX_COLUMNS] = {0};
    Vector3 positions[MAX_COLUMNS] = {0};
    Color colors[MAX_COLUMNS] = {0};

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = MakeRandomColumns(heights[i]);
        colors[i] = MakeRandomColor();
    }

    DisableCursor();
    SetTargetFPS(MAX_FPS);

    while (!WindowShouldClose())
    {
        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advanced camera controls, it's recommended to compute camera movement manually
        UpdateCamera(camera->GetCamera(), CAMERA_FIRST_PERSON);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(*camera->GetCamera());
            {
                DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY); // Draw ground
                DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, BLUE);           // Draw a blue wall
                DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f, LIME);            // Draw a green wall
                DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f, GOLD);            // Draw a yellow wall

                // Draw some cubes around
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                }
            }
            EndMode3D();
        }
        EndDrawing();
    }

    CloseWindow();
    exit(EXIT_SUCCESS);
}