#include "FlowObstacle.h"
#include "GlobalVariables.h"
#include "cprocessing.h"
#include "Math.h"
#include "stdlib.h"
#include "AssetLib.h"

float LastSpawnDeltaTime = 0.f;
float CurrentDelay = 0.f;
float MinDelay = 0.3f;
float MaxDelay = 3.f;
bool bShouldGenerateCurrentDelay = false;

float BounceAmount = 40.f;

void AddObstacle()
{
	int LastIndex = -1;
	for (int i = 0;i < MAX_OBSTACLES;i++)
	{
		if (Obstacles[i].bIsValid == false)
		{
			LastIndex = i;
			break;
		}
	}
	if (LastIndex != -1)
	{
		SetObstacleByRandom(LastIndex);
	}
}

void UpdateObstaclesPosition()
{
	LastSpawnDeltaTime += CP_System_GetDt();
	if (LastSpawnDeltaTime >= CurrentDelay)
	{
		AddObstacle();
		bShouldGenerateCurrentDelay = true;
	}
	if (bShouldGenerateCurrentDelay)
	{
		CurrentDelay = CP_Random_RangeFloat(MinDelay, MaxDelay);
		LastSpawnDeltaTime = 0.f;
		bShouldGenerateCurrentDelay = false;
	}
	for (int i = 0;i < MAX_OBSTACLES;i++)
	{
		if (Obstacles[i].bIsValid)
		{
			if (Obstacles[i].ObstaclePos.x+ Obstacles[i].ObstacleCollisionSize.x<0)
			{
				RemoveObstacle(i);
			}
			else
			{
				Obstacles[i].ObstaclePos.x -= GameData.Speed*CP_System_GetDt();
				
			}
		}
	}
	if (CheckObstaclesCollision())
	{
		CharacterData.bHasRecentlyCollided = true;
		CharacterData.CollisionTimer = 0.f;
		CharacterData.Energy--;
	}
}

bool CheckObstaclesCollision()
{
	if (!CharacterData.bHasRecentlyJumped && !CharacterData.bHasRecentlyCollided)
	{
		float CharacterMinX = CharacterData.CharacterPos.x;
		float CharacterMaxX = CharacterMinX + CharacterData.CharacterCollisionSize.x;
		float CharacterMinY = CharacterData.CharacterPos.y;
		float CharacterMaxY = CharacterMinY + CharacterData.CharacterCollisionSize.y;
		for (int i = 0;i < MAX_OBSTACLES;i++)
		{
			if (Obstacles[i].bIsValid)
			{
				float ObstacleMinX = Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x;
				float ObstacleMaxX = Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x + Obstacles[i].ObstacleCollisionSize.x;
				float ObstacleMinY = Obstacles[i].ObstaclePos.y + Obstacles[i].ObstacleCollisionStartOffset.y;
				float ObstacleMaxY = Obstacles[i].ObstaclePos.y + Obstacles[i].ObstacleCollisionStartOffset.y + Obstacles[i].ObstacleCollisionSize.y;
				if (ObstacleMinX < CharacterMaxX &&
					ObstacleMaxX > CharacterMinX &&
					ObstacleMinY < CharacterMaxY &&
					ObstacleMaxY > CharacterMinY)//check AABB
				{
					BounceCollisionDirection(i);
					return true;
				}
			}
		}
	}
	return false;
}

void BounceCollisionDirection(int Index)
{
	float CharacterCenterX = CharacterData.CharacterPos.x + CharacterData.CharacterCollisionSize.x;
	float CharacterCenterY = CharacterData.CharacterPos.y + CharacterData.CharacterCollisionSize.y;
	float ObstacleCenterX = Obstacles[Index].ObstaclePos.x + Obstacles[Index].ObstacleCollisionSize.x;
	float ObstacleCenterY = Obstacles[Index].ObstaclePos.y + Obstacles[Index].ObstacleCollisionSize.y;
	float DeltaX = CharacterCenterX - ObstacleCenterX;
	float DeltaY = CharacterCenterY - ObstacleCenterY;
	float intersectX = (CharacterData.CharacterCollisionSize.x + Obstacles[Index].ObstacleCollisionSize.x) / 2 - fabsf(DeltaX);
	float intersectY = (CharacterData.CharacterCollisionSize.y + Obstacles[Index].ObstacleCollisionSize.y) / 2 - fabsf(DeltaY);
	if (intersectX < intersectY)
	{
		if (DeltaX > 0)
		{
			if (CharacterData.CharacterPos.x + BounceAmount > GameData.LaneMax.x - CharacterData.CharacterCollisionSize.x)
			{
				CharacterData.CharacterPos.x = GameData.LaneMax.x - CharacterData.CharacterCollisionSize.x;
			}
			else
			{
				CharacterData.CharacterPos.x += BounceAmount;
			}
		}
		else
		{
			if (CharacterData.CharacterPos.x - BounceAmount < GameData.LaneMin.x)
			{
				CharacterData.CharacterPos.x = GameData.LaneMin.x;
			}
			else
			{
				CharacterData.CharacterPos.x -= BounceAmount;
			}
		}
	}
	else 
	{
		if (DeltaY > 0)
		{
			if (CharacterData.CharacterPos.y + BounceAmount > GameData.LaneMax.y - CharacterData.CharacterCollisionSize.y - GameData.LaneMin.y)
			{
				CharacterData.CharacterPos.y = GameData.LaneMax.y - CharacterData.CharacterCollisionSize.y - GameData.LaneMin.y;
			}
			else
			{
				CharacterData.CharacterPos.y += BounceAmount;
			}
		}
		else
		{
			if (CharacterData.CharacterPos.y - BounceAmount < 0)
			{
				CharacterData.CharacterPos.y = 0;
			}
			else
			{
				CharacterData.CharacterPos.y -= BounceAmount;
			}
		}
	}
}

void RemoveObstacle(int RemoveIndex)
{
	if (Obstacles[RemoveIndex].bIsValid)
	{
		Obstacles[RemoveIndex].bIsValid = false;
		CharacterData.Score += Obstacles[RemoveIndex].Score * GameData.Speed;
	}
}

void RenderCharacter_Internal()
{
	//RenderCharacter
	CharacterData.AnimationTimer += CP_System_GetDt();
	if (CharacterData.AnimationTimer > 0.3f)
	{
		if (CharacterData.AnimationFrame == 6)
		{
			CharacterData.AnimationFrame = 0;
			CharacterData.AnimationTimer = 0.f;
		}
		else
		{
			CharacterData.AnimationFrame++;
			CharacterData.AnimationTimer = 0.f;
		}
	}
	CP_Image_DrawSubImage(CharacterData.CharacterImage, GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y - CharacterData.CharaterDrawSize.y + CharacterData.CharacterCollisionSize.y, CharacterData.CharaterDrawSize.x, CharacterData.CharaterDrawSize.y, 100.f * CharacterData.AnimationFrame, 0.f, 100.f * (CharacterData.AnimationFrame+1), 100.f, 255);
//	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//	CP_Graphics_DrawRect(GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y, CharacterData.CharacterCollisionSize.x, CharacterData.CharacterCollisionSize.y);
}

void RenderObjects()
{
	if (CharacterData.bHasRecentlyCollided || CharacterData.bHasRecentlyJumped)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
		for (int i = 0;i < MAX_OBSTACLES; i++)
		{
			if (Obstacles[i].bIsValid)
			{
				CP_Image_Draw(Obstacles[i].ObstacleImage, GameData.LaneMin.x + Obstacles[i].ObstaclePos.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y, Obstacles[i].ObstacleImageSize.x, Obstacles[i].ObstacleImageSize.y, 255);
				//CollisionDebug
				CP_Graphics_DrawRect(GameData.LaneMin.x + Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y + Obstacles[i].ObstacleCollisionStartOffset.y, Obstacles[i].ObstacleCollisionSize.x + Obstacles[i].ObstacleCollisionStartOffset.x, Obstacles[i].ObstacleCollisionSize.y);
			}
		}
		RenderCharacter_Internal();
	}
	else
	{
		bool characterDrawn = false;

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			// 캐릭터가 Obstacle[i]보다 앞에 있고, 아직 안 그렸으면 먼저 캐릭터 그리기
			if (!characterDrawn && CharacterData.CharacterPos.y < Obstacles[i].ObstaclePos.y)
			{
				RenderCharacter_Internal();
				characterDrawn = true;
			}
			if (Obstacles[i].bIsValid)
			{
				// 장애물 그리기
				CP_Image_Draw(Obstacles[i].ObstacleImage, GameData.LaneMin.x + Obstacles[i].ObstaclePos.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y, Obstacles[i].ObstacleImageSize.x, Obstacles[i].ObstacleImageSize.y, 255);
				//CollisionDebug
				CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
				CP_Graphics_DrawRect(GameData.LaneMin.x + Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y+Obstacles[i].ObstacleCollisionStartOffset.y, Obstacles[i].ObstacleCollisionSize.x + Obstacles[i].ObstacleCollisionStartOffset.x, Obstacles[i].ObstacleCollisionSize.y);
			}
		}

		// 만약 캐릭터가 가장 아래쪽일 경우 (아직 안 그려졌다면)
		if (!characterDrawn)
		{
			RenderCharacter_Internal();
		}
	}
}

void SortObstacles()
{
	qsort(Obstacles, MAX_OBSTACLES, sizeof(FObstacleData), CompareByYPos);
}

int CompareByYPos(const void* a, const void* b) {
	FObstacleData* oa = (FObstacleData*)a;
	FObstacleData* ob = (FObstacleData*)b;

	if (oa->ObstaclePos.y < ob->ObstaclePos.y)
		return -1;
	else if (oa->ObstaclePos.y > ob->ObstaclePos.y)
		return 1;
	else
		return 0;
}

void SetObstacleByRandom(int Index)
{
	unsigned int RandomNum = CP_Random_GetInt();
	Obstacles[Index].bIsValid = true;
	switch (RandomNum % OBSTACLE_NUM)
	{
	case 0:
		Obstacles[Index].ObstacleImage = TurtleData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = TurtleData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = TurtleData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = TurtleData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = TurtleData.Score;
		break;
	case 1:
		Obstacles[Index].ObstacleImage = BoxData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = BoxData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = BoxData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = BoxData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = BoxData.Score;
		break;
	default:
		break;
	}
	
	
	float RandomY = CP_Random_RangeFloat(0.f, GameData.LaneMax.y - GameData.LaneMin.y - Obstacles[Index].ObstacleImageSize.y);
	Obstacles[Index].ObstaclePos = CP_Vector_Set(GameData.LaneMax.x, RandomY);
	SortObstacles();
}


