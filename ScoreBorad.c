#include "MainMenu.h"
#include "cprocessing.h"
#include "stdio.h"
#include "Game.h"
#include "GlobalVariables.h"
#include "ScoreBorad.h"


float RestartPosX ;
float RestartPosY ;
float GoToMainPosX;
float GoToMainPosY ;
float SocreBoardBtnSizeX;
float SocreBoardBtnSizeY;



void ScoreBoradInit(void)
{
	CP_System_SetWindowSize(1600, 900);
	RestartPosX = WindowCenterX - 260.f;
	RestartPosY = WindowCenterY;
	GoToMainPosX = WindowCenterX + 110.f;
	GoToMainPosY = WindowCenterY;
	SocreBoardBtnSizeX = 250.f;
	SocreBoardBtnSizeY = 100.f;

}

void ScoreBoradUpdate(void)
{
	CP_Settings_Fill(CP_Color_Create(70, 70, 70, 30));
	CP_Graphics_DrawRect(0,0,1600, 900);	
	
	char ScoreBuffer[128] = { 0 };
	sprintf_s(ScoreBuffer, 128, "Score : %f", CharacterData.Score);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(80.f);
	CP_Font_DrawText(ScoreBuffer, WindowCenterX - 220.f, WindowCenterY - 150.f);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(50.f);
	char buffer[12] = { 0 };
	sprintf_s(buffer, 12, "ReStart");
	CP_Font_DrawText(buffer, RestartPosX + 50.f, RestartPosY + 25.f);
	
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	CP_Graphics_DrawRect(RestartPosX, RestartPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY);


	char buffer2[20] = { 0 };
	sprintf_s(buffer2, 20, "GoToMain");
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText(buffer2, GoToMainPosX + 30.f, GoToMainPosY + 25.f);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 30));
	CP_Graphics_DrawRect(GoToMainPosX, GoToMainPosY, SocreBoardBtnSizeX, SocreBoardBtnSizeY);
	UpdateScoreBoardKeyInput();
}

void ScoreBoradExit(void)
{
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
}