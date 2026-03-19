/**
 * @file Utils.h
 * @author macasteglione
 * @brief Game utility functions
 * @version 0.1
 * @date 2026-03-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "rcamera.h"

static inline Color MakeRandomColor()
{
    return (Color){(unsigned char)GetRandomValue(20, 255), (unsigned char)GetRandomValue(10, 55), 30, 255};
}

static inline Vector3 MakeRandomColumns(float height)
{
    return (Vector3){(float)GetRandomValue(-15, 15), height / 2.0f, (float)GetRandomValue(-15, 15)};
}

#endif // !UTILS_H