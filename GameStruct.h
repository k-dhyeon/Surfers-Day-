#pragma once
#include "cprocessing_common.h"
#include "stdbool.h"
typedef enum ECharacterState {

}ECharacterState;

typedef struct FCharacterData {
	CP_Vector CharacterPos;
	CP_Image CharacterImage;
	ECharacterState ChracterState;
	bool CheckCollision;
}FCharacterData;

typedef struct FObstacleData {
	CP_Vector ObstaclePos;
	CP_Image ObstacleImage;
}FObstacleData;

typedef struct FGameData {
	float Speed;
	CP_Vector LaneMin;
	CP_Vector LaneMax;
	unsigned int score;
	//TODO : do it later
	//
}FGameData;