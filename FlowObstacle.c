#include "FlowObstacle.h"
#include "GlobalVariables.h"
#include "cprocessing.h"
#include "Math.h"
#include "stdlib.h"
#include "AssetLib.h"
#include "BGM.h"
#include "CameraShake.h"

float LastSpawnDeltaTime = 0.f;
float CurrentDelay = 0.f;
float MinDelay = 0.3f;
float MaxDelay = 3.f;


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
		float RelativeMaxDelayByGameSpeed = 0.f;
		if (GameData.Speed > 1000)
		{
			RelativeMaxDelayByGameSpeed = MaxDelay / 5.f;
		}
		else
		{
			RelativeMaxDelayByGameSpeed = MaxDelay*0.8f;
		}
		//RelativeMaxDelayByGameSpeed = MinDelay;
		CurrentDelay = CP_Random_RangeFloat(MinDelay, RelativeMaxDelayByGameSpeed);
		LastSpawnDeltaTime = 0.f;
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
		SetCharacterState(COLLISION);
		PlaySFXCollision();
		CharacterData.CollisionTimer = 0.f;
		GameData.Speed = InitGameSpeed + (GameData.Speed - InitGameSpeed) / 2.f;
		StartShake(0.25f, 1.0f, 3.f);
	}
}

bool CheckObstaclesCollision()
{
	if (CharacterData.CharacterState == STANDING && !CharacterData.bEndWaveInvincible)
	{
		float CharacterMinX = CharacterData.CharacterPos.x + CharacterData.CharacterCollisionOffset.x;
		float CharacterMaxX = CharacterMinX + CharacterData.CharacterCollisionSize.x;
		float CharacterMinY = CharacterData.CharacterPos.y + CharacterData.CharacterCollisionOffset.y;
		float CharacterMaxY = CharacterMinY + CharacterData.CharacterCollisionSize.y;
		if (bDebugMode)
		{
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
			CP_Graphics_DrawRect(GameData.LaneMin.x + CharacterMinX, GameData.LaneMin.y + CharacterMinY, CharacterMaxX - CharacterMinX, CharacterMaxY - CharacterMinY);
		}
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
					CharacterData.Energy -= Obstacles[i].Score;
					if (CharacterData.Energy < 0.f)
					{
						CharacterData.Energy = 0.f;
					}
					return true;
				}
			}
		}
	}
	return false;
}

void BounceCollisionDirection(int Index)
{
	float CharacterCenterX = CharacterData.CharacterPos.x + CharacterData.CharacterCollisionSize.x + CharacterData.CharacterCollisionOffset.x;
	float CharacterCenterY = CharacterData.CharacterPos.y + CharacterData.CharacterCollisionSize.y;
	float ObstacleCenterX = Obstacles[Index].ObstaclePos.x + Obstacles[Index].ObstacleCollisionSize.x;
	float ObstacleCenterY = Obstacles[Index].ObstaclePos.y + Obstacles[Index].ObstacleCollisionSize.y;
	float DeltaX = CharacterCenterX - ObstacleCenterX;
	float DeltaY = CharacterCenterY - ObstacleCenterY;
	float intersectX = (CharacterData.CharacterCollisionSize.x + CharacterData.CharacterCollisionOffset.x + Obstacles[Index].ObstacleCollisionSize.x) / 2 - fabsf(DeltaX);
	float intersectY = (CharacterData.CharacterCollisionSize.y + Obstacles[Index].ObstacleCollisionSize.y) / 2 - fabsf(DeltaY);
	if (intersectX < intersectY)
	{
		if (DeltaX > 0)
		{
			if (CharacterData.CharacterPos.x + BounceAmount > GameData.LaneMax.x - CharacterData.CharacterCollisionSize.x - CharacterData.CharacterCollisionOffset.x)
			{
				CharacterData.CharacterPos.x = GameData.LaneMax.x - CharacterData.CharacterCollisionSize.x - CharacterData.CharacterCollisionOffset.x;
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
		CharacterData.Score += Obstacles[RemoveIndex].Score * GameData.Speed*0.001f;
	}
}

void RenderCharacter_Internal()
{
	//RenderCharacter
	CharacterData.AnimationTimer += CP_System_GetDt();
	if (CharacterData.AnimationTimer > 0.3f)
	{
		if (CharacterData.AnimationFrame == CharacterData.AnimationMaxFrame)
		{
			if (CharacterData.CharacterState == JUMPUP)
			{
				SetCharacterState(JUMPDOWN);
			}
			else if (CharacterData.CharacterState == COMBO1)
			{
				SetCharacterState(JUMPDOWN);
			}
			else if (CharacterData.CharacterState == COMBO2)
			{
				SetCharacterState(JUMPDOWN);
			}
			else if (CharacterData.CharacterState == JUMPDOWN)
			{
				SetCharacterState(STANDING);
			}
			else if (CharacterData.CharacterState == STARTWAVE)
			{
				SetCharacterState(WAVING);
			}
			else if (CharacterData.CharacterState == ENDWAVE)
			{
				SetCharacterState(STANDING);
				CharacterData.bEndWaveInvincible = true;
			}
			else
			{
				CharacterData.AnimationFrame = 0;
				CharacterData.AnimationTimer = 0.f;
			}
		}
		else
		{
			CharacterData.AnimationFrame++;
			CharacterData.AnimationTimer = 0.f;
		}
	}
	float CharacterDrawRatio = 0.8f + 0.2f * (CharacterData.CharacterPos.y / (GameData.LaneMax.y - GameData.LaneMin.y));
	if(CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
	{
		CharacterDrawRatio = 0.7f;
	}
	CP_Image_DrawSubImage(CharacterData.CharacterImage,
		GameData.LaneMin.x + CharacterData.CharacterPos.x + (CharacterData.CharaterDrawSize.x * (1 - CharacterDrawRatio) /2.f),
		GameData.LaneMin.y + CharacterData.CharacterPos.y - CharacterData.CharaterDrawSize.y + CharacterData.CharacterCollisionSize.y + (CharacterData.CharaterDrawSize.y * (1 - CharacterDrawRatio)),
		CharacterData.CharaterDrawSize.x * CharacterDrawRatio,
		CharacterData.CharaterDrawSize.y * CharacterDrawRatio,
		100.f * CharacterData.AnimationFrame + 1,
		100.f * CharacterData.CharacterState + 1,
		100.f * (CharacterData.AnimationFrame+1) - 1,
		100.f * (CharacterData.CharacterState + 1) - 1,
		255);
}

void RenderObjects()
{
	if (CharacterData.CharacterState == COLLISION || CharacterData.CharacterState == JUMPUP || CharacterData.CharacterState == JUMPDOWN)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 100));
		for (int i = 0;i < MAX_OBSTACLES; i++)
		{
			if (Obstacles[i].bIsValid)
			{
				CP_Image_Draw(Obstacles[i].ObstacleImage, GameData.LaneMin.x + Obstacles[i].ObstaclePos.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y, Obstacles[i].ObstacleImageSize.x, Obstacles[i].ObstacleImageSize.y, 255);
				//CollisionDebug
				if (bDebugMode)
				{
					CP_Graphics_DrawRect(GameData.LaneMin.x + Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y + Obstacles[i].ObstacleCollisionStartOffset.y, Obstacles[i].ObstacleCollisionSize.x + Obstacles[i].ObstacleCollisionStartOffset.x, Obstacles[i].ObstacleCollisionSize.y);
				}
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
				CP_Image_Draw(Obstacles[i].ObstacleImage, floorf(GameData.LaneMin.x + Obstacles[i].ObstaclePos.x), GameData.LaneMin.y + Obstacles[i].ObstaclePos.y, Obstacles[i].ObstacleImageSize.x, Obstacles[i].ObstacleImageSize.y, 255);
				//CollisionDebug
				if (bDebugMode)
				{
					CP_Settings_Fill(CP_Color_Create(255, 255, 0,100));
					CP_Graphics_DrawRect(GameData.LaneMin.x + Obstacles[i].ObstaclePos.x + Obstacles[i].ObstacleCollisionStartOffset.x, GameData.LaneMin.y + Obstacles[i].ObstaclePos.y + Obstacles[i].ObstacleCollisionStartOffset.y, Obstacles[i].ObstacleCollisionSize.x + Obstacles[i].ObstacleCollisionStartOffset.x, Obstacles[i].ObstacleCollisionSize.y);
				}
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
	case 2:
		Obstacles[Index].ObstacleImage = BallData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = BallData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = BallData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = BallData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = BallData.Score;
		break;
	case 3:
		Obstacles[Index].ObstacleImage = DolpinData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = DolpinData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = DolpinData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = DolpinData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = DolpinData.Score;
		break;
	case 4:
		Obstacles[Index].ObstacleImage = CameraData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = CameraData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = CameraData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = CameraData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = CameraData.Score;
		break;
	case 5:
		Obstacles[Index].ObstacleImage = IcecreamData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = IcecreamData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = IcecreamData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = IcecreamData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = IcecreamData.Score;
		break;
	case 6:
		Obstacles[Index].ObstacleImage = StarFishData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = StarFishData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = StarFishData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = StarFishData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = StarFishData.Score;
		break;
	case 7:
		Obstacles[Index].ObstacleImage = TubeData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = TubeData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = TubeData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = TubeData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = TubeData.Score;
		break;
	case 8:
		Obstacles[Index].ObstacleImage = CrabData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = CrabData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = CrabData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = CrabData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = CrabData.Score;
		break;
	case 9:
		Obstacles[Index].ObstacleImage = JellyfishData.ObstacleImage;
		Obstacles[Index].ObstacleImageSize = JellyfishData.ObstacleImageSize;
		Obstacles[Index].ObstacleCollisionSize = JellyfishData.ObstacleCollisionSize;
		Obstacles[Index].ObstacleCollisionStartOffset = JellyfishData.ObstacleCollisionStartOffset;
		Obstacles[Index].Score = JellyfishData.Score;
		break;
	default:
		break;
	}
	if (CP_Random_RangeInt(0,4) < 1)//20%
	{
		float CharacterPosCenterY = CharacterData.CharacterPos.y + CharacterData.CharacterCollisionSize.y/2.f;
		CharacterPosCenterY -= Obstacles[Index].ObstacleCollisionSize.y/2.f;
		CharacterPosCenterY -= Obstacles[Index].ObstacleCollisionStartOffset.y;
		Obstacles[Index].ObstaclePos = CP_Vector_Set(GameData.LaneMax.x, CharacterPosCenterY);
	}
	else
	{
		float RandomY = CP_Random_RangeFloat(-Obstacles[Index].ObstacleCollisionStartOffset.y, GameData.LaneMax.y - GameData.LaneMin.y - Obstacles[Index].ObstacleCollisionSize.y - Obstacles[Index].ObstacleCollisionStartOffset.y);
		Obstacles[Index].ObstaclePos = CP_Vector_Set(GameData.LaneMax.x, RandomY);
	}
	SortObstacles();
}

