#include "GameCamera.h"

// Define the camera to look into our 3d world (position, target, up vector)
GameCamera::GameCamera()
{
    camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // Camera position
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};   // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                           // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;        // Camera projection type
}

GameCamera::~GameCamera() {}

Camera *GameCamera::GetCamera()
{
    return &camera;
}