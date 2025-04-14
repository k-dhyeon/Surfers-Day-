#pragma once

#include "GameStruct.h"


#define MAX_OBSTACLES 20

//Variables
extern FGameData GameData;

extern FCharacterData CharacterData;

extern FObstacleData Obstacles[];

void InitGameData();

void InitCharacterData();

void InitObstacles();
