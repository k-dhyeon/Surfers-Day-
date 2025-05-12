#include "RankMenu.h"
#include "GameStruct.h"
#include "stdio.h"
#include "cprocessing.h"
#include "ScoreBoard.h"
#include "MainMenu.h"
#include "AssetLib.h"

#define MAX_ENTRIES 150
#define FILENAME "leaderboard.sav"
FSaveData SaveDatas[150];
int offsetIndex;
float FontSize;
float TopOffset = 135.f;
float LeftOffset = 200.f;
float RankMenuButtonSizeX = 250.f;
float RankMenuButtonSizeY = 100.f;
float PrevButtonPosX;
float PrevButtonPosY;
float NextButtonPosX;
float NextButtonPosY;
float RankMenuReturnToMainButtonPosX;
float RankMenuReturnToMainButtonPosY;

void RankMenuInit()
{
	for (int i = 0;i < 150;i++)
	{
		SaveDatas[i].Initial[0] = '\0';
		SaveDatas[i].Initial[1] = '\0';
		SaveDatas[i].Initial[2] = '\0';
		SaveDatas[i].Initial[3] = '\0';
		SaveDatas[i].Score = 0.f;
	}
	loadData(SaveDatas);
	offsetIndex = 0;
	FontSize = 90.f;
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	PrevButtonPosX = 10.f;
	PrevButtonPosY = CP_System_GetWindowHeight()-RankMenuButtonSizeY - 10.f;
	NextButtonPosX = CP_System_GetWindowWidth() - RankMenuButtonSizeX - 10.f;
	NextButtonPosY = CP_System_GetWindowHeight() - RankMenuButtonSizeY - 10.f;
	RankMenuReturnToMainButtonPosX = CP_System_GetWindowWidth() /2.f - RankMenuButtonSizeX/2.f;
	RankMenuReturnToMainButtonPosY = CP_System_GetWindowHeight() - RankMenuButtonSizeY - 10.f;
	ScoreBoardBackground = CP_Image_Load("./Assets/sc.png");
}

void RankMenuUpdate()
{
	CP_Settings_Fill(CP_Color_Create(70, 70, 70, 255));
	CP_Graphics_DrawRect(0, 0, 1600, 900);
	CP_Image_Draw(ScoreBoardBackground,0,0,1600,900,255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(FontSize);
	for (int i = 0; i < 7; i++)
	{
		if (offsetIndex + i + 1 < 150)
		{
			char RankBuffer[4] = { '\0' };
			sprintf_s(RankBuffer, 4, "%03d", i + offsetIndex + 1);
			CP_Font_DrawText(RankBuffer, LeftOffset + 0.f, FontSize * i + TopOffset);
			char NameBuffer[4] = { '\0' };
			sprintf_s(NameBuffer, 4, "%c%c%c", SaveDatas[offsetIndex + i].Initial[0], SaveDatas[offsetIndex + i].Initial[1], SaveDatas[offsetIndex + i].Initial[2]);
			CP_Font_DrawText(NameBuffer, LeftOffset + 200.f, FontSize * i + TopOffset);
			char ScoreBuffer[128] = { 0 };
			sprintf_s(ScoreBuffer, 128, ": %lf", SaveDatas[offsetIndex + i].Score);
			CP_Font_DrawText(ScoreBuffer, LeftOffset + 450.f, FontSize * i + TopOffset);
		}
	}

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	CP_Image_Draw(UIBoard, PrevButtonPosX, PrevButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY, 255);
	//CP_Graphics_DrawRect(PrevButtonPosX, PrevButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(50.f);
	CP_Font_DrawText("PREV", PrevButtonPosX + 60.f, PrevButtonPosY + 25.f);

	CP_Image_Draw(UIBoard, NextButtonPosX, NextButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY, 255);
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	//CP_Graphics_DrawRect(NextButtonPosX, NextButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(50.f);
	CP_Font_DrawText("NEXT", NextButtonPosX + 60.f, NextButtonPosY + 25.f);

	CP_Image_Draw(UIBoard, RankMenuReturnToMainButtonPosX, RankMenuReturnToMainButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY, 255);
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	//CP_Graphics_DrawRect(RankMenuReturnToMainButtonPosX, RankMenuReturnToMainButtonPosY, RankMenuButtonSizeX, RankMenuButtonSizeY);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(50.f);
	CP_Font_DrawText("MAIN", RankMenuReturnToMainButtonPosX + 60.f, RankMenuReturnToMainButtonPosY + 25.f);

	UpdateRankMenuKeyInput();
}

void RankMenuExit()
{
}

void UpdateRankMenuKeyInput()
{
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
	{
		float MousePosX = CP_Input_GetMouseX();
		float MousePosY = CP_Input_GetMouseY();
		if (MousePosX >= PrevButtonPosX &&
			MousePosX <= PrevButtonPosX + RankMenuButtonSizeX &&
			MousePosY >= PrevButtonPosY &&
			MousePosY <= PrevButtonPosY + RankMenuButtonSizeY)
		{
			if (offsetIndex > 0)
			{
				offsetIndex-=7;
			}
		}
		else if (MousePosX >= NextButtonPosX &&
			MousePosX <= NextButtonPosX + RankMenuButtonSizeX &&
			MousePosY >= NextButtonPosY &&
			MousePosY <= NextButtonPosY + RankMenuButtonSizeY)
		{
			if (offsetIndex < 143)
			{
				offsetIndex += 7;
			}
		}
		else if (MousePosX >= RankMenuReturnToMainButtonPosX &&
			MousePosX <= RankMenuReturnToMainButtonPosX + RankMenuButtonSizeX &&
			MousePosY >= RankMenuReturnToMainButtonPosY &&
			MousePosY <= RankMenuReturnToMainButtonPosY + RankMenuButtonSizeY)
		{
			CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
		}
	}
}