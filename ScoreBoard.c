#include "MainMenu.h"
#include "cprocessing.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "GlobalVariables.h"
#include "ScoreBoard.h"
#include "BGM.h"
#include "AssetLib.h"

#define MAX_ENTRIES 150
#define FILENAME "leaderboard.sav"

float RestartPosX ;
float RestartPosY ;
float GoToMainPosX;
float GoToMainPosY ;
float SocreBoardBtnSizeX;
float SocreBoardBtnSizeY;

int SaveDataNum = 150;
FSaveData SaveDatas[150];
int CurrentPlayerIndex = -1;

int PlayerInitialIndex;
char PlayerInitial[4];

void ScoreBoradInit(void)
{
	CP_System_SetWindowSize(1600, 900);
	SocreBoardBtnSizeX = 250.f;
	SocreBoardBtnSizeY = 100.f;
	RestartPosX = WindowCenterX - SocreBoardBtnSizeX * 1.5f;
	RestartPosY = WindowCenterY;
	GoToMainPosX = WindowCenterX + SocreBoardBtnSizeX / 2.f;
	GoToMainPosY = WindowCenterY;


	for (int i = 0;i < 150;i++)
	{
		SaveDatas[i].Initial[0] = '\0';
		SaveDatas[i].Initial[1] = '\0';
		SaveDatas[i].Initial[2] = '\0';
		SaveDatas[i].Initial[3] = '\0';
		SaveDatas[i].Score = 0.f;
	}
	PlayerInitialIndex = 0;
	for (int i = 0;i < 4;i++)
	{
		PlayerInitial[i] = '\0';
	}
	loadData(SaveDatas);
	CurrentPlayerIndex = FindScoreRank();
	SaveDatas[149].Score = CharacterData.Score;
	PlaySFXGameOver();
}

void ScoreBoradUpdate(void)
{
	CP_Settings_Fill(CP_Color_Create(70, 70, 70, 30));
	CP_Graphics_DrawRect(0,0,1600, 900);	

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);

	char ScoreBuffer[128] = { 0 };
	sprintf_s(ScoreBuffer, 128, "Score : %.2f", CharacterData.Score);
	CP_Settings_Fill(CP_Color_Create(255, 255, 128, 255));
	CP_Settings_TextSize(80.f);
	CP_Font_DrawText(ScoreBuffer, WindowCenterX, WindowCenterY - 100.f);

	if (CurrentPlayerIndex != -1)
	{
		char RankBuffer[128] = { 0 };
		sprintf_s(RankBuffer, 128, "Your Rank : %d", CurrentPlayerIndex+1);
		CP_Settings_TextSize(80.f);
		CP_Font_DrawText(RankBuffer, WindowCenterX, WindowCenterY - 180.f);
	}
	else
	{
		CP_Settings_TextSize(80.f);
		CP_Font_DrawText("Out of Rank", WindowCenterX, WindowCenterY - 180.f);
	}
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_TOP);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	for (int i = 0; i < 3; i++)
	{
		float offset = 150.f;
		char TempStr[2] = { PlayerInitial[i], '\0' };
		if (PlayerInitialIndex == i)
		{
			CP_Settings_Fill(CP_Color_Create(255, 255, 128, 255));
		}
		else
		{
			CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
		}
		CP_Graphics_DrawRect(WindowCenterX - 200.f + offset*i, WindowCenterY - 300.f, 100.f, 100.f);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText(TempStr, WindowCenterX - 200.f + 24.f + offset * i, WindowCenterY - 300.f + 18.f);
	}

	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Settings_TextSize(50.f);
	CP_Image_Draw(StartBoard, RestartPosX, RestartPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY, 255);
	//CP_Font_DrawText("Start", RestartPosX + 50.f, RestartPosY + 25.f);
	
	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	//CP_Graphics_DrawRect(RestartPosX, RestartPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY);

	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(MainBoard, GoToMainPosX, GoToMainPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY, 255);
	//CP_Font_DrawText("Main", GoToMainPosX + 70.f, GoToMainPosY + 25.f);

	//CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	//CP_Graphics_DrawRect(GoToMainPosX, GoToMainPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY);
	UpdateScoreBoardKeyInput();
	
	GetPlayerKeyBoardInput();
	
}

void ScoreBoradExit(void)
{
	SaveDatas[149].Initial[0] = PlayerInitial[0];
	SaveDatas[149].Initial[1] = PlayerInitial[1];
	SaveDatas[149].Initial[2] = PlayerInitial[2];
	qsort(SaveDatas, 150, sizeof(FSaveData), compareScores);
	saveData(SaveDatas);
}
	
	
void UpdateScoreBoardKeyInput(void)
{
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		float MousePosX = CP_Input_GetMouseX();
		float MousePosY = CP_Input_GetMouseY();
		if (MousePosX >= RestartPosX &&
			MousePosX <= RestartPosX + SocreBoardBtnSizeX &&
			MousePosY >= RestartPosY &&
			MousePosY <= RestartPosY + SocreBoardBtnSizeY)
		{
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}

		else if (MousePosX >= GoToMainPosX &&
			MousePosX <= GoToMainPosX + SocreBoardBtnSizeX &&
			MousePosY >= GoToMainPosY &&
			MousePosY <= GoToMainPosY + SocreBoardBtnSizeY)
		{
			CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
		}
		
	}
	if (CP_Input_KeyDown(KEY_ENTER))
	{
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	}
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}
}



// 내림차순 정렬용 비교 함수
int compareScores(const void* a, const void* b) {
	FSaveData* fa = (FSaveData*)a;
	FSaveData* fb = (FSaveData*)b;
	if (fb->Score > fa->Score) return 1;
	else if (fb->Score < fa->Score) return -1;
	else return 0;
}

// 데이터 저장
void saveData(FSaveData data[]) {
	FILE* fp = fopen(FILENAME, "wb");
	if (!fp) {
		perror("파일 저장 실패");
		return;
	}
	fwrite(data, sizeof(FSaveData), SaveDataNum, fp);
	fclose(fp);
}

// 데이터 불러오기
void loadData(FSaveData data[]) {
	FILE* fp = fopen(FILENAME, "rb");
	if (!fp) {
		perror("파일 불러오기 실패");
		return;
	}
	fread(data, sizeof(FSaveData), SaveDataNum, fp);
	fclose(fp);
}

int FindScoreRank()
{
	for (int i = 0; i < SaveDataNum; i++)
	{
		if (SaveDatas[i].Score < CharacterData.Score)
		{
			return i;
		}
	}
	return -1;
}

void GetPlayerKeyBoardInput()
{
	if (CP_Input_KeyTriggered(KEY_A))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'A';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_B))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'B';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_C))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'C';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_D))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'D';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_E))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'E';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_F))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'F';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_G))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'G';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_H))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'H';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_I))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'I';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_J))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'J';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_K))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'K';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_L))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'L';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_M))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'M';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_N))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'N';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_O))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'O';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_P))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'P';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_Q))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'Q';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_R))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'R';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_S))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'S';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_T))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'T';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_U))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'U';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_V))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'V';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_W))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'W';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_X))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'X';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_Y))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'Y';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_Z))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = 'Z';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_SPACE))
	{
		if (PlayerInitialIndex < 3)
		{
			PlayerInitial[PlayerInitialIndex] = ' ';
			if (PlayerInitialIndex < 2)
			{
				PlayerInitialIndex++;
			}
		}
	}
	else if (CP_Input_KeyTriggered(KEY_BACKSPACE))
	{
		if (PlayerInitialIndex > 0)
		{
			if (PlayerInitial[PlayerInitialIndex] == '\0')
			{
				PlayerInitialIndex--;
				PlayerInitial[PlayerInitialIndex] = '\0';
				
			}
			else
			{
				PlayerInitial[PlayerInitialIndex] = '\0';
				PlayerInitialIndex--;
			}
		}
		else if(PlayerInitialIndex == 0)
		{
			PlayerInitial[PlayerInitialIndex] = '\0';
		}
	}
}