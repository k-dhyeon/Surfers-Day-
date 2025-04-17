#pragma once
#include "cprocessing_common.h"
#include "stdbool.h"

#define SEA_IMAGE_NUM 1
#define WAVE_IMAGE_NUM 1

typedef enum ECharacterState {
	STANDING = 0,
	RIDEWAVE = 1,
}ECharacterState;

typedef enum EObsticleType {
	TURTLE = 0,
	BOX = 1,
	Ball = 2,
	Dolpin = 3,
	Camera = 4,
	Icecream = 5,
	Starfish = 6,
	Tube = 7,
	Crab = 8,
	Jellyfish = 9,
}EObsticleType;


typedef struct FCharacterData {
	CP_Vector CharacterPos;
	CP_Vector CharaterDrawSize;
	int AnimationFrame;
	CP_Image CharacterImage;
	float AnimationTimer;
	ECharacterState CharacterState;
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

typedef struct FBatteryData {
	bool bIsValid;
	CP_Vector BatteryPos;
	CP_Vector BatteryImageSize;
	CP_Image BatteryImage;
	float Energy;
}FBatteryData;

typedef struct FSeaAnimationData {
	CP_Image SeaImage[SEA_IMAGE_NUM];
	float AnimationTimer;
	int SeaIndex;
}FSeaAnimationData;

typedef struct FBigWaveData {
	bool bIsValid;
	bool bIsRiderable;
	CP_Image WaveImage[WAVE_IMAGE_NUM];
	CP_Vector WaveImageSize;
	float AnimationTimer;
	int WaveIndex;
	float RiderableTime;
	float WaveETA;
}FBigWaveData;

typedef struct FSaveData {
	char Initial[4];
	double Score;
}FSaveData;