#include "GameCamera.h"

GameCamera::GameCamera()
    : camera{
          .position = {0.f, 2.f, 4.f},
          .target = {0.f, 2.f, 0.f},
          .up = {0.f, 1.f, 0.f},
          .fovy = 60.f,
          .projection = CAMERA_PERSPECTIVE}
{
}

const Camera *GameCamera::GetCamera() const
{
    return &camera;
}

void GameCamera::Update(float delta, int mode)
{
    // Raylib gestiona movimiento XZ y rotación por mouse
    UpdateCamera(&camera, mode);

    bool isMoving = IsKeyDown(KEY_W) || IsKeyDown(KEY_S) ||
                    IsKeyDown(KEY_A) || IsKeyDown(KEY_D);

    ApplyJump(delta);
    ApplyBob(delta, isMoving);
    ApplyTilt(delta);

    // Offset Y total = salto + bob/idle + landing impact
    // Se aplica como delta sobre target para preservar el pitch del mouse
    float totalOffsetY = (playerY - groundY) + bobOffset - landingOffset;
    camera.position.y = groundY + totalOffsetY;
    camera.target.y += totalOffsetY - lastOffsetY;
    lastOffsetY = totalOffsetY;
}

void GameCamera::ApplyJump(float delta)
{
    if (isGrounded && IsKeyPressed(KEY_SPACE))
    {
        velocityY = jumpForce;
        isGrounded = false;
    }

    // Integrar física vertical
    velocityY += gravity * delta;
    playerY += velocityY * delta;

    if (playerY <= groundY)
    {
        // Impulso al resorte proporcional a la velocidad de impacto
        landingVelocity += std::abs(velocityY) * 0.06f;

        playerY = groundY;
        velocityY = 0.f;
        isGrounded = true;
    }

    // Integrar spring del landing: F = -k·x - d·v
    float springForce = -springStiffness * landingOffset - springDamping * landingVelocity;
    landingVelocity += springForce * delta;
    landingOffset += landingVelocity * delta;
}

void GameCamera::ApplyBob(float delta, bool isMoving)
{
    float bobTarget = 0.f;

    if (isMoving && isGrounded)
    {
        // Ciclo senoidal mientras el jugador se mueve
        bobTimer += delta * bobFrequency;
        bobTarget = std::sin(bobTimer) * bobAmplitude;
        idleTimer = 0.f;
    }
    else
    {
        // Respiración idle: sube y baja muy sutilmente
        idleTimer += delta * idleFrequency;
        bobTarget = std::sin(idleTimer) * idleAmplitudeY;
    }

    // Spring arrastra bobOffset hacia bobTarget suavemente
    float bobSpring = -springStiffness * (bobOffset - bobTarget) - springDamping * bobVelocity;
    bobVelocity += bobSpring * delta;
    bobOffset += bobVelocity * delta;
}

void GameCamera::ApplyTilt(float delta)
{
    // Inclinar la cámara al moverse lateralmente (estilo Quake)
    float targetTilt = 0.f;
    if (IsKeyDown(KEY_A))
        targetTilt = tiltMax;
    if (IsKeyDown(KEY_D))
        targetTilt = -tiltMax;

    tiltAngle = Lerp(tiltAngle, targetTilt, delta * tiltSpeed);

    // Rotar el vector UP alrededor del eje forward
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Matrix rot = MatrixRotate(forward, tiltAngle * DEG2RAD);
    camera.up = Vector3Normalize(Vector3Transform({0.f, 1.f, 0.f}, rot));
}