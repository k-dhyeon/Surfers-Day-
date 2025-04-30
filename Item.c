#include "Item.h"
#include "cprocessing.h"
#include "BGM.h"
#include "AssetLib.h"

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

	if (MedalItem.bIsValid)
	{
		if (MedalItem.ItemPos.y > GameData.LaneMin.y)
		{
			RemoveMedal();
		}
		else
		{
			MedalItem.ItemPos.y += GameData.Speed * CP_System_GetDt() * 0.1f;
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
	float CharacterDrawRatio = 0.8f + 0.2f * (CharacterData.CharacterPos.y / (GameData.LaneMax.y - GameData.LaneMin.y));
	float CharacterMinX = CharacterData.CharacterPos.x + (CharacterData.CharaterDrawSize.x * (1 - CharacterDrawRatio) / 2.f);
	float CharacterMaxX = CharacterMinX + CharacterData.CharaterDrawSize.x * CharacterDrawRatio;
	float CharacterMinY = CharacterData.CharacterPos.y - CharacterData.CharaterDrawSize.y + CharacterData.CharacterCollisionSize.y + (CharacterData.CharaterDrawSize.y * (1 - CharacterDrawRatio));
	float CharacterMaxY = CharacterMinY + CharacterData.CharaterDrawSize.y * CharacterDrawRatio;
//	DebugOnly
//	CP_Graphics_DrawRect(GameData.LaneMin.x + CharacterMinX, GameData.LaneMin.y + CharacterMinY, CharacterMaxX- CharacterMinX, CharacterMaxY- CharacterMinY);
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
				if (CharacterData.Energy > 200.f)
				{
					CharacterData.Energy = 200.f;
				}
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

	if (MedalItem.bIsValid)
	{
		float ItemMinX = MedalItem.ItemPos.x - GameData.LaneMin.x;
		float ItemMaxX = ItemMinX + MedalItem.ItemImageSize.x;
		float ItemMinY = MedalItem.ItemPos.y - GameData.LaneMin.y;
		float ItemMaxY = ItemMinY + MedalItem.ItemImageSize.y;
		if (ItemMinX < CharacterMaxX &&
			ItemMaxX > CharacterMinX &&
			ItemMinY < CharacterMaxY &&
			ItemMaxY > CharacterMinY)//check AABB
		{
			RemoveMedal();
			CharacterData.Score += MedalItem.Score * GameData.Speed * 0.05f;
			PlaySFXMedal();
		}
	}
}



void SetBatteryByRandom(int Index)
{
	Batteries[Index].bIsValid = true;
	Batteries[Index].Energy = CP_Random_RangeFloat(10.f,50.f);
	if (Batteries[Index].Energy < 15.f)
	{
		Batteries[Index].BatteryImage = LowBattery;
	}
	else if (Batteries[Index].Energy < 30.f)
	{
		Batteries[Index].BatteryImage = HalfBattery;
	}
	else if (Batteries[Index].Energy < 45.f)
	{
		Batteries[Index].BatteryImage = HighBattery;
	}
	else
	{
		Batteries[Index].BatteryImage = MaxBattery;
	}
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


void SpawnMedal()
{
	if (!MedalItem.bIsValid)
	{
		MedalItem.bIsValid = true;
		float RandomX = CP_Random_RangeFloat(GameData.LaneMax.x / 2.f, GameData.LaneMax.x - MedalItem.ItemImageSize.x);
		MedalItem.ItemPos = CP_Vector_Set(RandomX, GameData.LaneMin.y - BigWaveData.WaveImageSize.y);
	}
}



void RemoveMedal()
{
	if (MedalItem.bIsValid)
	{
		MedalItem.bIsValid = false;
	}
}

void RenderMedal()
{
	if (MedalItem.bIsValid)
	{
		CP_Image_Draw(MedalItem.ItemImage, GameData.LaneMin.x + MedalItem.ItemPos.x, MedalItem.ItemPos.y, MedalItem.ItemImageSize.x, MedalItem.ItemImageSize.y, 255);
	}
}