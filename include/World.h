/**
 * @file World.h
 * @author macasteglione
 * @brief Class for the game world settings
 * @version 0.1
 * @date 2026-03-25
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include <assert.h>

class World
{
private:
    static constexpr int MAX_COLUMNS = 20;

    Texture2D floorTexture;
    Model model;

    float heights[MAX_COLUMNS];
    Vector3 positions[MAX_COLUMNS];
    Color colors[MAX_COLUMNS];

    static inline Color MakeRandomColor();
    static inline Vector3 MakeRandomColumns(float height);
    static Mesh GenTiledPlaneMesh(float width, float length, int tilesX, int tilesZ);

public:
    World();
    ~World();

    float GetHeights(int i) const;
    Vector3 GetPositions(int i) const;
    Color GetColors(int i) const;

    void DrawWorld();
};

#endif // !WORLD_H