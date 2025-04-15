#include "BigWave.h"
#include "cprocessing.h"
#include "stdio.h"
void BeginWave()
{
	BigWaveData.bIsValid = true;
	BigWaveData.AnimationTimer = 0.f;
	BigWaveData.WaveIndex = 0;
	BigWaveData.RiderableTime = CP_Random_RangeFloat(10.f,20.f);
}

void UpdateWave()
{
	if (BigWaveData.bIsValid)
	{
		float ImageSizeX = (float)CP_Image_GetWidth(BigWaveData.WaveImage[0]);
		float ImageSizeY = (float)CP_Image_GetHeight(BigWaveData.WaveImage[0]);
		BigWaveData.AnimationTimer += CP_System_GetDt();
		if (!BigWaveData.bIsRiderable)
		{
			CP_Image_DrawSubImage(BigWaveData.WaveImage[0], 0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y, ImageSizeX / 6 * BigWaveData.WaveIndex, 0, ImageSizeX / 6 * (BigWaveData.WaveIndex + 1), ImageSizeY, 255);
			
			
			if (BigWaveData.AnimationTimer > 5.f)
			{
				BigWaveData.WaveIndex++;
				BigWaveData.AnimationTimer = 0.f;
			}
			if (BigWaveData.WaveIndex > 1 && BigWaveData.WaveIndex < 4)
			{
				BigWaveData.bIsRiderable = true;
			}
			if (BigWaveData.WaveIndex > 5)
			{
				RemoveWave();
				CharacterData.CharacterState = STANDING;

			}
			//DEBUG
			//CP_Settings_Fill(CP_Color_Create(200,200,200,255));
			//CP_Graphics_DrawRect(0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y);
		}
		else
		{
			CP_Image_DrawSubImage(BigWaveData.WaveImage[0], 0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y, ImageSizeX / 6 * BigWaveData.WaveIndex, 0, ImageSizeX / 6 * (BigWaveData.WaveIndex + 1), ImageSizeY, 255);
			
			if (BigWaveData.AnimationTimer > 5.f)
			{
				BigWaveData.WaveIndex++;
				BigWaveData.AnimationTimer = 0.f;
			}
			
		}
		CheckRideWave();
	}
	else
	{
		BigWaveData.WaveETA -= CP_System_GetDt();
		if (BigWaveData.WaveETA < 0.f)
		{
			BeginWave();
		}
	}
}

void RemoveWave()
{
	BigWaveData.bIsValid = false;
	BigWaveData.bIsRiderable = false;
	BigWaveData.WaveETA = CP_Random_RangeFloat(20.f, 40.f);
}

void CheckRideWave()
{
	if (BigWaveData.bIsValid)
	{
		if (CharacterData.CharacterPos.y <= 0.f)
		{
			CharacterData.CharacterState = RIDEWAVE;
		}
	}
}
