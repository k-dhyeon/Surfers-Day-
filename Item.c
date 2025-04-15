#include "Item.h"
#include "cprocessing.h"


float LastSpawnBatteryDeltaTime = 0.f;
float CurrentBatterySpawnDelay = 0.f;
float MinBatterySpawnDelay = 15.f;
float MaxBatterySpawnDelay = 20.f;

void SpawnBattery()
{
	int LastIndex = -1;
	for (int i = 0;i < MAX_BATTERIES;i++)
	{
		if (Batteries[i].bIsValid == false)
		{
			LastIndex = i;
			break;
		}
	}
	if (LastIndex != -1)
	{
		SetBatteryByRandom(LastIndex);
	}
}

void UpdateItemsPosition()
{
	LastSpawnBatteryDeltaTime += CP_System_GetDt();
	if (LastSpawnBatteryDeltaTime >= CurrentBatterySpawnDelay)
	{
		SpawnBattery();
		CurrentBatterySpawnDelay = CP_Random_RangeFloat(MinBatterySpawnDelay, MaxBatterySpawnDelay);
		LastSpawnBatteryDeltaTime = 0.f;
	}
	
	for (int i = 0;i < MAX_BATTERIES;i++)
	{
		if (Batteries[i].bIsValid)
		{
			if (Batteries[i].BatteryPos.y + Batteries[i].BatteryImageSize.y < 0)
			{
				RemoveBattery(i);
			}
			else
			{
				Batteries[i].BatteryPos.y -= GameData.Speed * CP_System_GetDt()* 0.1f;
			}
		}
	}
	
}

void RemoveBattery(int RemoveIndex)
{
	if (Batteries[RemoveIndex].bIsValid)
	{
		Batteries[RemoveIndex].bIsValid = false;
	}
}

void CheckBatteriesCollision()
{
	float CharacterMinX = CharacterData.CharacterPos.x;
	float CharacterMaxX = CharacterMinX + CharacterData.CharacterCollisionSize.x;
	float CharacterMinY = CharacterData.CharacterPos.y;
	float CharacterMaxY = CharacterMinY + CharacterData.CharacterCollisionSize.y;
	for (int i = 0;i < MAX_BATTERIES;i++)
	{
		if (Batteries[i].bIsValid)
		{
			float BatteryMinX = Batteries[i].BatteryPos.x;
			float BatteryMaxX = Batteries[i].BatteryPos.x + Batteries[i].BatteryImageSize.x;
			float BatteryMinY = Batteries[i].BatteryPos.y;
			float BatteryMaxY = Batteries[i].BatteryPos.y + Batteries[i].BatteryImageSize.y;
			if (BatteryMinX < CharacterMaxX &&
				BatteryMaxX > CharacterMinX &&
				BatteryMinY < CharacterMaxY &&
				BatteryMaxY > CharacterMinY)//check AABB
			{
				RemoveBattery(i);
				CharacterData.Score += Batteries[i].Energy;
				CharacterData.Energy += Batteries[i].Energy;
			}
		}
	}
}



void SetBatteryByRandom(int Index)
{
	Batteries[Index].bIsValid = true;
	float RandomX = CP_Random_RangeFloat(GameData.LaneMin.x, GameData.LaneMax.x - Batteries[Index].BatteryImageSize.x);
	Batteries[Index].BatteryPos = CP_Vector_Set(RandomX, GameData.LaneMax.y - GameData.LaneMin.y);
}

void RenderBatteries()
{
	for (int i = 0;i < MAX_BATTERIES;i++)
	{
		if (Batteries[i].bIsValid)
		{
			CP_Image_Draw(Batteries[i].BatteryImage, GameData.LaneMin.x + Batteries[i].BatteryPos.x, GameData.LaneMin.y + Batteries[i].BatteryPos.y, Batteries[i].BatteryImageSize.x, Batteries[i].BatteryImageSize.y, 255);
		}
	}
}