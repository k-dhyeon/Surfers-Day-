#pragma once
#include "GlobalVariables.h"
#include "cprocessing.h"



//Variables
FGameData GameData;
FCharacterData CharacterData;
FObstacleData Obstacles[MAX_OBSTACLES];

void InitGameData()
{
	GameData.Speed = 200.f;
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
	CharacterData.CharacterCollisionSize = CP_Vector_Set(100.f,30.f);//TODO : Use Image and Set Collision Size
	CharacterData.bHasRecentlyJumped = false;
	CharacterData.JumpTimer = 0.f;
	CharacterData.Energy = 200.f;
	CharacterData.bHasRecentlyCollided = false;
	CharacterData.CollisionTimer = 0.f;
	CharacterData.Score = 0;
	CharacterData.CharacterImage = CP_Image_Load("./Assets/Swim.png");
	CharacterData.AnimationTimer = 0.f;
	CharacterData.AnimationFrame = 0;
	CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
}

void InitObstacles()
{
	for (int i = 0; i < MAX_OBSTACLES; i++)
	{
		Obstacles[i].bIsValid = false;
	}
}
