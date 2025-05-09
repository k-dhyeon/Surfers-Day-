#pragma once
#include "GlobalVariables.h"
#include "cprocessing.h"
#include "AssetLib.h"


//Variables
FGameData GameData;
FCharacterData CharacterData;
FObstacleData Obstacles[MAX_OBSTACLES];
FBatteryData Batteries[MAX_BATTERIES];
FSpeedItemData AddSpeedItem;
FSpeedItemData ReduceSpeedItem;
FMedalItemData MedalItem;
FBigWaveData BigWaveData;

float InitGameSpeed = 200.f;

//Debug only, Set false when release
bool bDebugMode = false;



void InitGameData()
{
	GameData.Speed = InitGameSpeed;
	float WindowHeight = (float)CP_System_GetWindowHeight();
	GameData.LaneMax = CP_Vector_Set((float)CP_System_GetWindowWidth(), WindowHeight * 0.85f);
	GameData.LaneMin = CP_Vector_Set(0.f, WindowHeight/2.f);
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		Obstacles[i].bIsValid = false;
	}
	GameData.SpeedTimer = 0.f;
}

void InitCharacterData()
{
	CharacterData.CharacterPos = CP_Vector_Set((GameData.LaneMax.x-GameData.LaneMin.x)/5.f,(GameData.LaneMax.y-GameData.LaneMin.y)/2.f);
	CharacterData.CharacterCollisionSize = CP_Vector_Set(90.f,40.f);//TODO : Use Image and Set Collision Size
	CharacterData.CharacterCollisionOffset = CP_Vector_Set(55.f, -10.f);
	CharacterData.JumpTimer = 0.f;
	CharacterData.Energy = 200.f;
	CharacterData.CollisionTimer = 0.f;
	CharacterData.Score = 0;
	CharacterData.CharacterImage = CP_Image_Load("./Assets/Character.png");
	CharacterData.AnimationTimer = 0.f;
	CharacterData.AnimationFrame = 0;
	CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
	CharacterData.ComboIndex = 0;
	CharacterData.HandOffset = CP_Vector_Set(200.f,-100.f);
	SetCharacterState(STANDING);
	for (int i = 0; i < COMBO_COMMAND_LENGTH;i++)
	{
		CharacterData.ComboCommand[i] = '\0';
	}
	CharacterData.bEndWaveInvincible = false;
	CharacterData.EndWaveInvincibleTimer = 0.f;
}

void InitObstacles()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		Obstacles[i].bIsValid = false;
	}
}

void InitItemData()
{
	for (int i = 0; i < MAX_BATTERIES; i++)
	{
		Batteries[i].BatteryImage = BatteryData.BatteryImage;
		Batteries[i].Energy = BatteryData.Energy;
		Batteries[i].BatteryImageSize = BatteryData.BatteryImageSize;
		Batteries[i].bIsValid = false;
	}
	AddSpeedItem.bIsValid = false;
	AddSpeedItem.GameSpeedMultiplier = 1.3f;
	AddSpeedItem.ItemImage = CP_Image_Load("./Assets/FastItem.png");
	AddSpeedItem.ItemImageSize = CP_Vector_Set(50.f, 50.f);
	AddSpeedItem.ItemPos = CP_Vector_Set(CP_Random_RangeFloat(GameData.LaneMax.x/2.f, GameData.LaneMax.x), GameData.LaneMax.y - GameData.LaneMin.y);
	ReduceSpeedItem.bIsValid = false;
	ReduceSpeedItem.GameSpeedMultiplier = 0.9f;
	ReduceSpeedItem.ItemImage = CP_Image_Load("./Assets/SlowItem.png");
	ReduceSpeedItem.ItemImageSize = CP_Vector_Set(50.f,50.f);
	ReduceSpeedItem.ItemPos = CP_Vector_Set(CP_Random_RangeFloat(GameData.LaneMax.x / 2.f, GameData.LaneMax.x), GameData.LaneMax.y - GameData.LaneMin.y);
	MedalItem.bIsValid = false;
	MedalItem.ItemImage = CP_Image_Load("./Assets/Trophy.png");
	MedalItem.ItemImageSize = CP_Vector_Set(50.f, 50.f);
	MedalItem.Score = 100.f;
}

void InitBigWaveData()
{
	BigWaveData.AnimationTimer = 0.f;
	BigWaveData.WaveIndex = 0;
	BigWaveData.bIsRiderable = false;
	BigWaveData.bIsValid = false;
	BigWaveData.WaveImageSize = CP_Vector_Set((float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight() / 5.f);
	BigWaveData.WaveETA = CP_Random_RangeFloat(0.f,0.f);//(10.f,15.f);
	BigWaveData.WaveImage = CP_Image_Load("./Assets/Wave.png");
	BigWaveData.WaveRiderableStartIndex = 2;
	BigWaveData.WaveRiderableEndIndex = 5;
}

void SetCharacterState(ECharacterState NewState)
{
	CharacterData.AnimationFrame = 0;
	CharacterData.AnimationTimer = 0.f;
	CharacterData.CharacterState = NewState;
	switch(NewState)
	{
		case STANDING :
			CharacterData.AnimationMaxFrame = 1;
			break;
		case JUMPUP :
			CharacterData.AnimationMaxFrame = 2;
			break;
		case JUMPDOWN :
			CharacterData.AnimationMaxFrame = 2;
			break;
		case COLLISION : 
			CharacterData.AnimationMaxFrame = 2;
			break;
		case STARTWAVE :
			CharacterData.AnimationMaxFrame = 2;
			break;
		case WAVING : 
			CharacterData.AnimationMaxFrame = 1;
			break;
		case ENDWAVE : 
			CharacterData.AnimationMaxFrame = 1;
			break;
		case COMBO1 : 
			CharacterData.AnimationMaxFrame = 2;
			break;
		case COMBO2 : 
			CharacterData.AnimationMaxFrame = 2;
			break;
		case HEIGHESTWAVE:
			CharacterData.AnimationMaxFrame = 2;
			break;
		default:
			CharacterData.AnimationMaxFrame = 0;
			break;
	}
}
