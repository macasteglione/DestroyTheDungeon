// Local includes
#include "Player.h"
#include "World.h"
#include "Enemy.h"

int main(void)
{
    const int FPS_MAX = 60;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(0, 0, "Destroy The Dungeon");

    Player player;
    World world;
    Enemy enemy;

    DisableCursor();

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();
        // Update player computes movement internally depending on the player mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advanced player controls, it's recommended to compute player movement manually
        player.Update(delta);

        // Ray desde el centro de la pantalla hacia la escena
        Ray ray = GetScreenToWorldRay(
            (Vector2){GetScreenWidth() / 2.f, GetScreenHeight() / 2.f},
            *player.GetCamera());

        bool isAiming = enemy.IsAlive() && enemy.IsHit(ray);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isAiming)
            enemy.TryKill(player.GetCamera()->position);

        enemy.Update(delta, player.GetCamera()->position);
        bool inRange = enemy.IsAlive() && enemy.DistanceTo(player.GetCamera()->position) <= 2.5f;

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(*player.GetCamera());
            {
                world.DrawWorld();
                enemy.Draw();
            }
            EndMode3D();

            // Crosshair — rojo solo si apunta al enemigo Y está en rango
            int cx = GetScreenWidth() / 2;
            int cy = GetScreenHeight() / 2;
            Color crossColor = (isAiming && inRange) ? RED : WHITE;

            DrawLine(cx - 10, cy, cx + 10, cy, crossColor);
            DrawLine(cx, cy - 10, cx, cy + 10, crossColor);

            if (isAiming && inRange)
                DrawText("[LMB] Attack", cx - 50, cy + 20, 18, RED);
            else if (isAiming && !inRange)
                DrawText("Too far", cx - 30, cy + 20, 18, GRAY);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}