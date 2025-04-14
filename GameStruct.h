#pragma once
#include "cprocessing_common.h"
#include "stdbool.h"
typedef enum ECharacterState {

	
}ECharacterState;

typedef enum EObsticleType {
	TURTLE = 0,
	BOX = 1,
}EObsticleType;


typedef struct FCharacterData {
	CP_Vector CharacterPos;
	CP_Vector CharaterDrawSize;
	int AnimationFrame;
	CP_Image CharacterImage;
	float AnimationTimer;
	ECharacterState ChracterState;

	bool bHasRecentlyJumped;
	float JumpTimer;
	CP_Vector CharacterCollisionSize;
	float Energy;
	bool bHasRecentlyCollided;
	float CollisionTimer;
	double Score;
}FCharacterData;

typedef struct FObstacleData {
	bool bIsValid;
	CP_Vector ObstaclePos;
	CP_Vector ObstacleImageSize;
	CP_Vector ObstacleCollisionSize;
	CP_Vector ObstacleCollisionStartOffset;//from LeftTop

	CP_Image ObstacleImage;
	float Score;
}FObstacleData;

typedef struct FGameData {
	float Speed;
	float SpeedTimer;
	CP_Vector LaneMin;
	CP_Vector LaneMax;
	//TODO : do it later
	//
}FGameData;