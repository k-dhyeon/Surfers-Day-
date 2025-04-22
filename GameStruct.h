#pragma once
#include "cprocessing_common.h"
#include "stdbool.h"

#define SEA_IMAGE_NUM 1
#define COMBO_COMMAND_LENGTH 5

typedef enum ECharacterState {
	STANDING = 0,		//Image num 2
	JUMPUP = 1,			//Image num 2
	JUMPDOWN = 2,		//Image num 2
	COLLISION = 3,		//Image num 2
	STARTWAVE = 4,		//Image num 2
	WAVING = 5,			//Image num 2
	ENDWAVE = 6,		//Image num 2
	COMBO1 = 7,			//Image num 2
	COMBO2 = 8,			//Image num 2
}ECharacterState;

typedef enum ECharacterComboState {
	
}ECharacterComboState;

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
	int AnimationMaxFrame;
	CP_Image CharacterImage;
	float AnimationTimer;
	ECharacterState CharacterState;
	float JumpTimer;
	CP_Vector CharacterCollisionOffset;
	CP_Vector CharacterCollisionSize;
	float Energy;
	float CollisionTimer;
	double Score;
	//Combo
	int ComboIndex;
	char ComboCommand[COMBO_COMMAND_LENGTH];
	ECharacterComboState ComboState;
	CP_Vector HandOffset;
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
	CP_Image WaveImage;
	CP_Vector WaveImageSize;
	float AnimationTimer;
	int WaveIndex;
	int WaveMaxIndex;
	int WaveRiderableStartIndex;
	int WaveRiderableEndIndex;
	float RiderableTime;
	float WaveETA;
}FBigWaveData;

typedef struct FSaveData {
	char Initial[4];
	double Score;
}FSaveData;