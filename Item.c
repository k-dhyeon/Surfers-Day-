#include "Item.h"
#include "cprocessing.h"
#include "BGM.h"

float LastSpawnBatteryDeltaTime = 0.f;
float CurrentBatterySpawnDelay = 0.f;
float MinBatterySpawnDelay = 15.f;
float MaxBatterySpawnDelay = 20.f;

float LastSpawnedSpeedItemDeltaTime = 0.f;
float CurrentSpeedItemSpawnDelay = 0.f;
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

	LastSpawnedSpeedItemDeltaTime += CP_System_GetDt();
	if (LastSpawnedSpeedItemDeltaTime >= CurrentSpeedItemSpawnDelay)
	{
		SpawnSpeedItem();
		CurrentSpeedItemSpawnDelay = CP_Random_RangeFloat(MinBatterySpawnDelay*2.f, MaxBatterySpawnDelay*2.f);
		LastSpawnedSpeedItemDeltaTime = 0.f;
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
	
	if (AddSpeedItem.bIsValid)
	{
		if (AddSpeedItem.ItemPos.y + AddSpeedItem.ItemImageSize.y < 0)
		{
			RemoveAddSpeedItem();
		}
		else
		{
			AddSpeedItem.ItemPos.y -= GameData.Speed * CP_System_GetDt() * 0.1f;
		}
	}

	if (ReduceSpeedItem.bIsValid)
	{
		if (ReduceSpeedItem.ItemPos.y + ReduceSpeedItem.ItemImageSize.y < 0)
		{
			RemoveReduceSpeedItem();
		}
		else
		{
			ReduceSpeedItem.ItemPos.y -= GameData.Speed * CP_System_GetDt() * 0.1f;
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

void CheckItemsCollision()
{
	float CharacterMinX = CharacterData.CharacterPos.x;
	float CharacterMaxX = CharacterMinX + CharacterData.CharacterCollisionSize.x + CharacterData.CharacterCollisionOffset.x;
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
				PlaySFXBatteryRecharge();
			}
		}
	}

	if (AddSpeedItem.bIsValid)
	{
		float ItemMinX = AddSpeedItem.ItemPos.x;
		float ItemMaxX = AddSpeedItem.ItemPos.x + AddSpeedItem.ItemImageSize.x;
		float ItemMinY = AddSpeedItem.ItemPos.y;
		float ItemMaxY = AddSpeedItem.ItemPos.y + AddSpeedItem.ItemImageSize.y;
		if (ItemMinX < CharacterMaxX &&
			ItemMaxX > CharacterMinX &&
			ItemMinY < CharacterMaxY &&
			ItemMaxY > CharacterMinY)//check AABB
		{
			RemoveAddSpeedItem();
			if (GameData.Speed * AddSpeedItem.GameSpeedMultiplier < 3000.f)
			{
				GameData.Speed *= AddSpeedItem.GameSpeedMultiplier;
			}
			else
			{
				GameData.Speed = 3000.f;
			}
			PlaySFXBatteryRecharge();
		}
	}
	if (ReduceSpeedItem.bIsValid)
	{
		float ItemMinX = ReduceSpeedItem.ItemPos.x;
		float ItemMaxX = ReduceSpeedItem.ItemPos.x + ReduceSpeedItem.ItemImageSize.x;
		float ItemMinY = ReduceSpeedItem.ItemPos.y;
		float ItemMaxY = ReduceSpeedItem.ItemPos.y + ReduceSpeedItem.ItemImageSize.y;
		if (ItemMinX < CharacterMaxX &&
			ItemMaxX > CharacterMinX &&
			ItemMinY < CharacterMaxY &&
			ItemMaxY > CharacterMinY)//check AABB
		{
			RemoveReduceSpeedItem();
			if (GameData.Speed * AddSpeedItem.GameSpeedMultiplier < 200.f)
			{
				GameData.Speed *= ReduceSpeedItem.GameSpeedMultiplier;
			}
			else
			{
				GameData.Speed = 200.f;
			}
			PlaySFXBatteryRecharge();
		}
	}
}



void SetBatteryByRandom(int Index)
{
	Batteries[Index].bIsValid = true;
	float RandomX = CP_Random_RangeFloat(GameData.LaneMin.x, (GameData.LaneMax.x)/2.f - Batteries[Index].BatteryImageSize.x);
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

void SpawnSpeedItem()
{
	if (!AddSpeedItem.bIsValid && !ReduceSpeedItem.bIsValid)
	{
		bool bIsAddSpeedItem = CP_Random_GetBool();
		if (bIsAddSpeedItem)
		{
			AddSpeedItem.bIsValid = true;
			float RandomX = CP_Random_RangeFloat(GameData.LaneMax.x / 2.f, GameData.LaneMax.x - AddSpeedItem.ItemImageSize.x);
			AddSpeedItem.ItemPos = CP_Vector_Set(RandomX, GameData.LaneMax.y - GameData.LaneMin.y);
		}
		else
		{
			ReduceSpeedItem.bIsValid = true;
			float RandomX = CP_Random_RangeFloat(GameData.LaneMax.x / 2.f, GameData.LaneMax.x - ReduceSpeedItem.ItemImageSize.x);
			ReduceSpeedItem.ItemPos = CP_Vector_Set(RandomX, GameData.LaneMax.y - GameData.LaneMin.y);
		}
	}
	
}

void RemoveAddSpeedItem()
{
	if (AddSpeedItem.bIsValid)
	{
		AddSpeedItem.bIsValid = false;
	}
}

void RemoveReduceSpeedItem()
{
	if (ReduceSpeedItem.bIsValid)
	{
		ReduceSpeedItem.bIsValid = false;
	}
}

void RenderSpeedItems()
{
	if (AddSpeedItem.bIsValid)
	{
		CP_Image_Draw(AddSpeedItem.ItemImage, GameData.LaneMin.x + AddSpeedItem.ItemPos.x, GameData.LaneMin.y + AddSpeedItem.ItemPos.y, AddSpeedItem.ItemImageSize.x, AddSpeedItem.ItemImageSize.y, 255);
	}
	if (ReduceSpeedItem.bIsValid)
	{
		CP_Image_Draw(ReduceSpeedItem.ItemImage, GameData.LaneMin.x + ReduceSpeedItem.ItemPos.x, GameData.LaneMin.y + ReduceSpeedItem.ItemPos.y, ReduceSpeedItem.ItemImageSize.x, ReduceSpeedItem.ItemImageSize.y, 255);
	}
}