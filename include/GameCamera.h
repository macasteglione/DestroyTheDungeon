/**
 * @file GameCamera.h
 * @author macasteglione
 * @brief Class for the camera settings
 * @version 0.1
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include "raylib.h"

class GameCamera
{
private:
    Camera camera;

public:
    GameCamera();
    ~GameCamera();
    Camera *GetCamera();
};

#endif // !GAMECAMERA_H