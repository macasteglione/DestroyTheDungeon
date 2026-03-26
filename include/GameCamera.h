/**
 * @file GameCamera.h
 * @author macasteglione
 * @brief First-person camera with jump, head bob, idle sway and tilt
 * @version 0.2
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 */
#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include "raylib.h"
#include "raymath.h"
#include <cmath>

class GameCamera
{
private:
    Camera camera;

    // Jump
    float playerY = 2.f;   // altura lógica del jugador
    float velocityY = 0.f; // velocidad vertical
    float groundY = 2.f;   // altura del piso
    float gravity = -20.f;
    float jumpForce = 7.f;
    bool isGrounded = true;

    // Landing spring
    float landingOffset = 0.f;     // desplazamiento Y del resorte
    float landingVelocity = 0.f;   // velocidad del resorte
    float springStiffness = 180.f; // rigidez — velocidad de recuperación
    float springDamping = 14.f;    // amortiguación — suprime el rebote

    // Head bob (movimiento)
    float bobTimer = 0.f;
    float bobAmplitude = 0.02f; // altura máxima del ciclo
    float bobFrequency = 10.f;  // velocidad del ciclo
    float bobOffset = 0.f;      // offset Y actual
    float bobVelocity = 0.f;    // velocidad del spring del bob

    // Idle sway (respiración en reposo)
    float idleTimer = 0.f;
    float idleAmplitudeY = 0.006f; // amplitud vertical (sutil)
    float idleFrequency = 1.2f;    // frecuencia de respiración

    // Tilt
    float tiltAngle = 0.f; // ángulo actual en grados
    float tiltMax = 1.f;   // inclinación máxima
    float tiltSpeed = 8.f; // velocidad de interpolación

    // Shared
    float lastOffsetY = 0.f; // offset Y del frame anterior (para calcular delta)

    void ApplyJump(float delta);
    void ApplyBob(float delta, bool isMoving);
    void ApplyTilt(float delta);

public:
    GameCamera();
    ~GameCamera() = default;

    GameCamera(const GameCamera &) = delete;
    GameCamera &operator=(const GameCamera &) = delete;

    const Camera *GetCamera() const;
    void Update(float delta, int mode = CAMERA_FIRST_PERSON);
};

#endif // !GAMECAMERA_H