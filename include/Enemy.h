/**
 * @file Enemy.h
 * @author macasteglione
 * @brief The class fot the game enemy
 * @version 0.1
 * @date 2026-03-26
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"

class Enemy
{
private:
    static constexpr float SPEED = 3.f;
    static constexpr float STOP_RANGE = 1.2f;   // distancia mínima al jugador
    static constexpr float ATTACK_RANGE = 2.5f; // distancia máxima para matar
    static constexpr float DEATH_DURATION = .4f;

    static const Vector3 SIZE;
    static const Color COLOR;
    static const Color COLOR_DEAD;

    Vector3 position;
    bool alive = true;
    float deathTimer = 0.f; // animación de muerte

public:
    Enemy(Vector3 spawnPos = {5.f, 1.f, 5.f});
    ~Enemy() = default;

    Enemy(const Enemy &) = delete;
    Enemy &operator=(const Enemy &) = delete;

    bool IsHit(Ray ray) const;
    void Update(float delta, Vector3 playerPos);
    void Draw() const;
    bool IsAlive() const { return alive; }
    float DistanceTo(Vector3 pos) const;
    void TryKill(Vector3 playerPos);
};

#endif