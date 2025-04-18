#include "Game.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "KeyInput.h"
#include "FlowObstacle.h"
#include "AssetLib.h"
#include "FlowBackGround.h"
#include "stdio.h"
#include "MainMenu.h"
#include "ScoreBorad.h"
#include "Item.h"
#include "BigWave.h"
#include "BGM.h"
#include "energybar.h"
#include "drone.h"

// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	CP_System_SetWindowSize(1600, 900);
	InitGameData();
	InitCharacterData();
	InitAsset();
	InitItemData();
	InitBigWaveData();
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	PlayInGameBGM();
	dronexy();
	//Test
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextSize(64);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	// initialize variables and CProcessing settings for this gamestate
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 255, 255));
	CP_Settings_Fill(CP_Color_Create(0, 0, 255, 255));
	DrawWater();
//	CP_Graphics_DrawRect(GameData.LaneMin.x, GameData.LaneMin.y, GameData.LaneMax.x-GameData.LaneMin.x, GameData.LaneMax.y - GameData.LaneMin.y);
	UpdateWave();
	RenderObjects();
	UpdateKeyInput();
	UpdateCharacterPosition();
	UpdateObstaclesPosition();
	UpdateItemsPosition();
	RenderBatteries();
	CheckBatteriesCollision();
	
	drone();
	energybar();
	

	if (CharacterData.bHasRecentlyJumped)
	{
		//Debug
		CP_Settings_Fill(CP_Color_Create(128, 128, 128, 128));
		CP_Graphics_DrawRect(GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y, 40.f, 20.f);
		CharacterData.JumpTimer += CP_System_GetDt();
		if (CharacterData.JumpTimer > 1.5f)
		{
			CharacterData.bHasRecentlyJumped = false;
		}
	}
	if (CharacterData.JumpTimer != 0.f)//TODO : nearly 0
	{
		CharacterData.JumpTimer += CP_System_GetDt();
		if (CharacterData.JumpTimer > 5.f)
		{
			CharacterData.JumpTimer = 0.f;
		}
	}
	if (CharacterData.bHasRecentlyCollided)
	{
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 128));
		CP_Graphics_DrawRect(GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y, 40.f, 20.f);
		CharacterData.CollisionTimer += CP_System_GetDt();
		if (CharacterData.CollisionTimer > 3.f)
		{
			CharacterData.bHasRecentlyCollided = false;
			CharacterData.CollisionTimer = 0.f;
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
				int a = 0;
				a++;
			}
		}
	}
	
	CharacterData.Energy -= CP_System_GetDt();

	if (CharacterData.Energy <= 0.f)
	{
		CP_Engine_SetNextGameState(ScoreBoradInit, ScoreBoradUpdate, ScoreBoradExit);
	}

	//TEST
	char buffer[128] = { 0 };
	if (CharacterData.bHasRecentlyJumped)
	{
		sprintf_s(buffer, 128, "Jumped Reset Timer : %f", CharacterData.JumpTimer);
	}
	else
	{
		sprintf_s(buffer, 128, "Not Jumped Reset Timer : %f", CharacterData.JumpTimer);
	}
	CP_Font_DrawText(buffer, 0.f, 0.f);
	printf("%.2f\n", CharacterData.Energy);
	//CP_Font_DrawText((CharacterData.Energy),0.f,0.f);
	// check input, update simulation, render etc.
	CharacterData.Score += CP_System_GetDt()*GameData.Speed*0.1f;
	char ScoreBuffer[128] = { 0 };
	sprintf_s(ScoreBuffer, 128, "Score : %f", CharacterData.Score);
	CP_Font_DrawText(ScoreBuffer, 0.f, GameData.LaneMax.y);

}

// use CP_Engine_SetNextGameState to specify this function as the exit function
// this function will be called once just before leaving the current gamestate
void game_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
	StopInGameBGM();
}