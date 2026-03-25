#include "World.h"

World::World() : heights{}, positions{}, colors{}
{
    floorTexture = LoadTexture("assets/Grass/Grass_01/Grass_01_basecolor.png");
    SetTextureWrap(floorTexture, TEXTURE_WRAP_REPEAT);

    Mesh planeMesh = GenTiledPlaneMesh(40.f, 40.f, 20, 20);
    model = LoadModelFromMesh(planeMesh);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = floorTexture;

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12);
        positions[i] = MakeRandomColumns(heights[i]);
        colors[i] = MakeRandomColor();
    }
}

World::~World()
{
    UnloadTexture(floorTexture);
    UnloadModel(model);
}

float World::GetHeights(int i) const
{
    assert(i >= 0 && i < MAX_COLUMNS);
    return heights[i];
}

Vector3 World::GetPositions(int i) const
{
    assert(i >= 0 && i < MAX_COLUMNS);
    return positions[i];
}

Color World::GetColors(int i) const
{
    assert(i >= 0 && i < MAX_COLUMNS);
    return colors[i];
}

void World::DrawWorld()
{
    DrawModel(model, (Vector3){0.f, 0.f, 0.f}, 1.f, WHITE);
}

Color World::MakeRandomColor()
{
    return (Color){(unsigned char)GetRandomValue(20, 255), (unsigned char)GetRandomValue(10, 55), 30, 255};
}

Vector3 World::MakeRandomColumns(float height)
{
    return (Vector3){(float)GetRandomValue(-15, 15), height / 2.0f, (float)GetRandomValue(-15, 15)};
}

Mesh World::GenTiledPlaneMesh(float width, float length, int tilesX, int tilesZ)
{
    Mesh mesh = GenMeshPlane(width, length, tilesX, tilesZ);

    int vertsX = tilesX + 1;
    int vertsZ = tilesZ + 1;

    for (int z = 0; z < vertsZ; z++)
    {
        for (int x = 0; x < vertsX; x++)
        {
            int idx = z * vertsX + x;
            mesh.texcoords[idx * 2 + 0] = (float)x;
            mesh.texcoords[idx * 2 + 1] = (float)z;
        }
    }

    UpdateMeshBuffer(mesh, 1, mesh.texcoords, mesh.vertexCount * 2 * sizeof(float), 0);
    return mesh;
}