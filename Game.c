#include "Game.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "KeyInput.h"
#include "FlowObstacle.h"
#include "AssetLib.h"
#include "FlowBackGround.h"
#include "stdio.h"
#include "MainMenu.h"
#include "ScoreBoard.h"
#include "Item.h"
#include "BigWave.h"
#include "BGM.h"
#include "energybar.h"
#include "drone.h"
#include "CameraShake.h"

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	CP_System_SetWindowSize(1600, 900);
	InitShake();
	InitGameData();
	InitCharacterData();

	InitAsset();
	InitItemData();
	InitBigWaveData();
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	PlayInGameBGM();
	InitKeyInput();
	//Test
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextSize(64);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_System_SetFrameRate(120);
	// initialize variables and CProcessing settings for this gamestate
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	UpdateShake();
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 255, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	DrawSkyBackGround();
	DrawFarBackGround();
	DrawBackGroundSeaGull();
	UpdateWave();
	DrawWater();
	//	CP_Graphics_DrawRect(GameData.LaneMin.x, GameData.LaneMin.y, GameData.LaneMax.x-GameData.LaneMin.x, GameData.LaneMax.y - GameData.LaneMin.y);


	UpdateKeyInput();
	UpdateCharacterPosition();
	UpdateObstaclesPosition();
	UpdateItemsPosition();
	CheckItemsCollision();
	RenderObjects();
	RenderBatteries();
	RenderSpeedItems();
	DrawNearBackGround();
	

	if (BigWaveData.WaveIndex >= BigWaveData.WaveRiderableStartIndex + 1 && BigWaveData.WaveIndex <= BigWaveData.WaveRiderableEndIndex - 1)
	{
		float AnimationNextTime = 2.f;
		float DrawOffsetY = BigWaveData.WaveIndex < BigWaveData.WaveMaxIndex / 2 ? BigWaveData.WaveImageSize.y / 4.f * (AnimationNextTime - BigWaveData.AnimationTimer) / AnimationNextTime : BigWaveData.WaveImageSize.y / 4.f * (BigWaveData.AnimationTimer) / AnimationNextTime;

		CP_Image_Draw(WaveTop, 0.f, GameData.LaneMin.y - BigWaveData.WaveImageSize.y + DrawOffsetY, BigWaveData.WaveImageSize.x, BigWaveData.WaveImageSize.y, 150);
	}
	RenderWhale();
	RenderMedal();
	drone();
	energybar();



	if (CharacterData.CharacterState == JUMPDOWN)
	{
		CharacterData.JumpTimer += CP_System_GetDt();
	}
	if (CharacterData.JumpTimer != 0.f)//TODO : nearly 0
	{
		CharacterData.JumpTimer += CP_System_GetDt();
		if (CharacterData.JumpTimer > 5.f)
		{
			CharacterData.JumpTimer = 0.f;
		}
	}
	if (CharacterData.CharacterState == COLLISION)
	{
		CharacterData.CollisionTimer += CP_System_GetDt();
		if (CharacterData.CollisionTimer > 1.5f)
		{
			SetCharacterState(STANDING);
			CharacterData.CollisionTimer = 0.f;
		}
	}
	if (CharacterData.bEndWaveInvincible)
	{
		CharacterData.EndWaveInvincibleTimer += CP_System_GetDt();
		if (CharacterData.EndWaveInvincibleTimer > 0.5f)
		{
			CharacterData.bEndWaveInvincible = false;
			CharacterData.EndWaveInvincibleTimer = 0.f;
		}
	}
	
	if (GameData.Speed < 3000.f)// update game speed
	{
		GameData.SpeedTimer += CP_System_GetDt();
		if (GameData.SpeedTimer > 2.5f)
		{
			GameData.SpeedTimer = 0.f;
			if (GameData.Speed <= 1100.f)
			{
				GameData.Speed *= 1.1f;
			}
			else if(GameData.Speed <= 1600.f)
			{
				GameData.Speed += 50.f;
			}
			else
			{
				//TESTONLY
			}
		}
	}
	
	CharacterData.Energy -= CP_System_GetDt();

	if (CharacterData.Energy <= 0.f)
	{
		CP_Engine_SetNextGameState(ScoreBoradInit, ScoreBoradUpdate, ScoreBoradExit);
	}

	//TEST

	if (CP_System_GetDt() > 0.016 * 2)
	{
		printf("delayed");
	}
}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	StopInGameBGM();
}