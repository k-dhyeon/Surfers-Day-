#pragma once

#include "GameStruct.h"


#define MAX_OBSTACLES 20

#define MAX_BATTERIES 3

//Variables
extern FGameData GameData;

extern FCharacterData CharacterData;

extern FObstacleData Obstacles[];

extern FBatteryData Batteries[];

extern FBigWaveData BigWaveData;

void InitGameData();

void InitCharacterData();

void InitObstacles();

void InitItemData();

void InitBigWaveData();