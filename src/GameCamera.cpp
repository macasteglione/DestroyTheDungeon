#include "GameCamera.h"

// Define the camera to look into our 3d world (position, target, up vector)
GameCamera::GameCamera() : camera{
                               .position = {0.f, 2.0f, 4.0f},   // Camera position
                               .target = {0.f, 2.f, 0.f},       // Camera looking at point
                               .up = {0.f, 1.f, 0.f},           // Camera up vector (rotation towards target)
                               .fovy = 60.f,                    // Camera field-of-view Y
                               .projection = CAMERA_PERSPECTIVE // Camera projection type

                           }
{
}

const Camera *GameCamera::GetCamera() const
{
    return &camera;
}

void GameCamera::Update(int mode)
{
    UpdateCamera(&camera, mode);
}