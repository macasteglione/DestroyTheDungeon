#include "Enemy.h"

const Vector3 Enemy::SIZE = {1.f, 2.5f, 1.f};
const Color Enemy::COLOR = {150, 200, 200, 255};
const Color Enemy::COLOR_DEAD = {200, 60, 60, 180};

Enemy::Enemy(Vector3 spawnPos) : position(spawnPos) {}

float Enemy::DistanceTo(Vector3 pos) const
{
    // Solo distancia XZ — ignorar altura
    Vector3 flat = {pos.x, position.y, pos.z};
    return Vector3Distance(position, flat);
}

void Enemy::TryKill(Vector3 playerPos)
{
    if (!alive)
        return;

    if (DistanceTo(playerPos) <= ATTACK_RANGE)
    {
        alive = false;
        deathTimer = DEATH_DURATION;
    }
}

bool Enemy::IsHit(Ray ray) const
{
    if (!alive)
        return false;

    // Bounding box basada en posición y tamaño
    BoundingBox box = {
        .min = {position.x - SIZE.x / 2.f,
                position.y - SIZE.y / 2.f,
                position.z - SIZE.z / 2.f},
        .max = {position.x + SIZE.x / 2.f,
                position.y + SIZE.y / 2.f,
                position.z + SIZE.z / 2.f}};

    return GetRayCollisionBox(ray, box).hit;
}

void Enemy::Update(float delta, Vector3 playerPos)
{
    if (!alive)
    {
        // Countdown de animación de muerte
        deathTimer -= delta;
        return;
    }

    // Ignorar diferencia de altura — perseguir solo en XZ
    Vector3 target = {playerPos.x, position.y, playerPos.z};
    Vector3 dir = Vector3Subtract(target, position);
    float dist = Vector3Length(dir);

    // Solo moverse si está lejos del jugador
    if (dist > STOP_RANGE)
    {
        Vector3 normalized = Vector3Scale(dir, 1.f / dist); // normalizar a mano
        position = Vector3Add(position, Vector3Scale(normalized, SPEED * delta));
    }
}

void Enemy::Draw() const
{
    // No dibujar si la animación de muerte terminó
    if (!alive && deathTimer <= 0.f)
        return;

    Color color = alive ? COLOR : COLOR_DEAD;

    // Animación de muerte: achatar el cubo hacia el suelo
    float scaleY = alive ? 1.f : Clamp(deathTimer / DEATH_DURATION, 0.f, 1.f);
    Vector3 size = {SIZE.x, SIZE.y * scaleY, SIZE.z};
    Vector3 pos = {position.x, position.y * scaleY, position.z};

    DrawCubeV(position, SIZE, COLOR);
    DrawCubeWiresV(position, SIZE, BLACK);
}