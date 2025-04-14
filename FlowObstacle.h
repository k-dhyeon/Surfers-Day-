#pragma once

#include<stdbool.h>

extern float LastSpawnDeltaTime;
extern float CurrentDelay;
extern float MinDelay;
extern float MaxDelay;
extern bool bShouldGenerateCurrentDelay;



void AddObstacle();

void UpdateObstaclesPosition();

bool CheckObstaclesCollision();

void BounceCollisionDirection(int Index);

void RemoveObstacle(int RemoveIndex);

void RenderObjects();

void SortObstacles();

int CompareByYPos(const void* a, const void* b);

void SetObstacleByRandom(int Index);