#pragma once
#include "cprocessing_common.h"
#include "stdbool.h"
typedef enum ECharacterState {
<<<<<<< HEAD
	
}ECharacterState;

typedef enum EObsticleType {
	TURTLE = 0,
	BOX = 1,
}EObsticleType;
=======

}ECharacterState;
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b

typedef struct FCharacterData {
	CP_Vector CharacterPos;
	CP_Image CharacterImage;
	ECharacterState ChracterState;
<<<<<<< HEAD
	bool bHasRecentlyJumped;
	float JumpTimer;
	CP_Vector CharacterCollisionSize;
	float Energy;
	bool bHasRecentlyCollided;
	float CollisionTimer;
}FCharacterData;

typedef struct FObstacleData {
	bool bIsValid;
	CP_Vector ObstaclePos;
	CP_Vector ObstacleImageSize;
	CP_Vector ObstacleCollisionSize;
	CP_Vector ObstacleCollisionStartOffset;//from LeftTop
=======
	bool CheckCollision;
}FCharacterData;

typedef struct FObstacleData {
	CP_Vector ObstaclePos;
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b
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