#include "BigWave.h"
#include "cprocessing.h"
#include "stdio.h"
#include "Item.h"
#include "AssetLib.h"

float LastWavingGameSpeed = 0.f;
float AnimationNextTime = 2.f;

float WhaleGoUITimer;

void BeginWave()
{
	BigWaveData.bIsValid = true;
	BigWaveData.AnimationTimer = 0.f;
	BigWaveData.WaveIndex = 0;
	BigWaveData.WaveMaxIndex = 8;
	WhaleData.bIsValid = CP_Random_GetBool();
	WhaleData.ObstaclePos = CP_Vector_Set(GameData.LaneMax.x,GameData.LaneMin.y);
	WhaleData.ImageAnimationIndex = 0;
	WhaleData.ImageAnimationTimer = 0.f;
	WhaleGoUITimer = 0.f;
}

void UpdateWave()
{
	if (BigWaveData.bIsValid)
	{
		float ImageSizeX = (float)CP_Image_GetWidth(BigWaveData.WaveImage);
		float ImageSizeY = (float)CP_Image_GetHeight(BigWaveData.WaveImage);
		BigWaveData.AnimationTimer += CP_System_GetDt();

		if (CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
		{
			CharacterData.Score += CP_System_GetDt() * GameData.Speed*0.2f;
		}
		if (BigWaveData.WaveIndex > BigWaveData.WaveRiderableStartIndex && BigWaveData.WaveIndex < BigWaveData.WaveRiderableEndIndex)
		{
			if (CharacterData.CharacterState == WAVING) 
			{
				SetCharacterState(HEIGHESTWAVE);
			}
		}
		else
		{
			if (CharacterData.CharacterState == HEIGHESTWAVE)
			{
				SetCharacterState(WAVING);
			}
		}
		float DrawOffsetY = BigWaveData.WaveIndex < BigWaveData.WaveMaxIndex / 2 ? BigWaveData.WaveImageSize.y/4.f * (AnimationNextTime - BigWaveData.AnimationTimer) / AnimationNextTime : BigWaveData.WaveImageSize.y / 4.f * (BigWaveData.AnimationTimer)/ AnimationNextTime;
		if (!BigWaveData.bIsRiderable)
		{
			CP_Image_DrawSubImage(BigWaveData.WaveImage, 0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y + DrawOffsetY, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y, ImageSizeX / BigWaveData.WaveMaxIndex * BigWaveData.WaveIndex, 0, ImageSizeX / BigWaveData.WaveMaxIndex * (BigWaveData.WaveIndex + 1), ImageSizeY, 255);
			
			
			if (BigWaveData.AnimationTimer > AnimationNextTime)
			{
				BigWaveData.WaveIndex++;
				BigWaveData.AnimationTimer = 0.f;
			}
			if (BigWaveData.WaveIndex >= BigWaveData.WaveRiderableStartIndex && BigWaveData.WaveIndex <= BigWaveData.WaveRiderableEndIndex)
			{
				BigWaveData.bIsRiderable = true;
			}
			if (BigWaveData.WaveIndex > BigWaveData.WaveMaxIndex)
			{
				RemoveWave();
				if (CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
				{
					SetCharacterState(ENDWAVE);
					GameData.Speed = LastWavingGameSpeed;
				}

			}
			//DEBUG
			//CP_Settings_Fill(CP_Color_Create(200,200,200,255));
			//CP_Graphics_DrawRect(0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y);
		}
		else
		{
			CP_Image_DrawSubImage(BigWaveData.WaveImage, 0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y + DrawOffsetY, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y, ImageSizeX / BigWaveData.WaveMaxIndex * BigWaveData.WaveIndex, 0, ImageSizeX / BigWaveData.WaveMaxIndex * (BigWaveData.WaveIndex + 1), ImageSizeY, 255);

			if (!MedalItem.bIsValid)
			{
				SpawnMedal();
			}

			if (BigWaveData.AnimationTimer > AnimationNextTime)
			{
				BigWaveData.WaveIndex++;
				BigWaveData.AnimationTimer = 0.f;
				if (BigWaveData.WaveIndex > BigWaveData.WaveRiderableEndIndex)
				{
					BigWaveData.bIsRiderable = false;
					if (CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
					{
						SetCharacterState(ENDWAVE);
						GameData.Speed = LastWavingGameSpeed;
					}
				}
			}
			
		}
	}
	else
	{
		BigWaveData.WaveETA -= CP_System_GetDt();
		if (BigWaveData.WaveETA < 0.f)
		{
			BeginWave();
		}
	}

	
	CheckRideWave();

}

void RemoveWave()
{
	BigWaveData.bIsValid = false;
	BigWaveData.bIsRiderable = false;
	BigWaveData.WaveETA = CP_Random_RangeFloat(10.f, 20.f);
	WhaleData.bIsValid = false;
}

void CheckRideWave()
{
	if (BigWaveData.bIsValid)
	{
		if (CharacterData.CharacterPos.y <= 0.f)
		{
			if (CharacterData.CharacterState == STANDING && BigWaveData.bIsRiderable)
			{
				SetCharacterState(STARTWAVE);
				LastWavingGameSpeed = GameData.Speed;
				GameData.Speed *= 2.f;
			}
		}
		else
		{
			if (CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
			{
				SetCharacterState(ENDWAVE);
				GameData.Speed = LastWavingGameSpeed;
			}
		}
	}
	else
	{
		if (CharacterData.CharacterState == WAVING || CharacterData.CharacterState == HEIGHESTWAVE)
		{
			SetCharacterState(ENDWAVE);
			GameData.Speed = LastWavingGameSpeed;
		}
	}
}

void RenderWhale()
{
	if (WhaleData.bIsValid)
	{
		WhaleGoUITimer += CP_System_GetDt();
		if (WhaleGoUITimer < 4.f)
		{
			CP_Image_Draw(WhaleArrowImage, 10.f, GameData.LaneMin.y - 200.f, 200.f, 100.f, 255);
			CP_Image_Draw(WhaleGoImage, 130.f, GameData.LaneMin.y - 230.f, 200.f, 100.f, 255);
		}
		CP_Image_DrawSubImage(WhaleData.ObstacleImage, WhaleData.ObstaclePos.x, WhaleData.ObstaclePos.y-200.f, WhaleData.ObstacleImageSize.x/3.f * 2.5f, WhaleData.ObstacleImageSize.y * 2.5f,
			WhaleData.ObstacleImageSize.x/3 * WhaleData.ImageAnimationIndex,
			0,
			(WhaleData.ObstacleImageSize.x/3) * (WhaleData.ImageAnimationIndex + 1),
			WhaleData.ObstacleImageSize.y,
			255);
		WhaleData.ObstaclePos.x -= 300.f * CP_System_GetDt();
		WhaleData.ImageAnimationTimer += CP_System_GetDt();
		if (WhaleData.ImageAnimationTimer >1.f)
		{
			WhaleData.ImageAnimationTimer = 0;
			if (WhaleData.ImageAnimationIndex == 2)
			{
				WhaleData.ImageAnimationIndex = 0;
			}
			else
			{
				WhaleData.ImageAnimationIndex++;
			}
		}
		if (bDebugMode)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 100));
			CP_Graphics_DrawRect(GameData.LaneMin.x + WhaleData.ObstaclePos.x + WhaleData.ObstacleCollisionStartOffset.x, WhaleData.ObstaclePos.y + WhaleData.ObstacleCollisionStartOffset.y, WhaleData.ObstacleCollisionSize.x + WhaleData.ObstacleCollisionStartOffset.x, WhaleData.ObstacleCollisionSize.y);
		}
	}
}