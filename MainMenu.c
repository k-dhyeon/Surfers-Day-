#include "MainMenu.h"
#include "cprocessing.h"
#include "stdio.h"
#include "Game.h"

float WindowCenterX;
float WindowCenterY;
float ButtonSizeX = 200.f;
float ButtonSizeY = 100.f;
float StartButtonPosX;
float StartButtonPosY;
float QuitButtonPosX;
float QuitButtonPosY;

void MainMenuInit(void)
{
	CP_System_SetWindowSize(1600, 900);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	WindowCenterX = (float)CP_System_GetWindowWidth()/2.f;
	WindowCenterY = (float)CP_System_GetWindowHeight()/2.f;
	StartButtonPosX = WindowCenterX - (ButtonSizeX / 2.f);
	StartButtonPosY = WindowCenterY - (ButtonSizeY)-5.f;
	QuitButtonPosX = WindowCenterX - (ButtonSizeX / 2.f);
	QuitButtonPosY = WindowCenterY + (ButtonSizeY)+5.f;
}

void MainMenuUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Graphics_DrawRect(StartButtonPosX, StartButtonPosY, ButtonSizeX, ButtonSizeY);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	char buffer[12] = { 0 };
	sprintf_s(buffer, 12, "Game Start");
	CP_Font_DrawText(buffer, WindowCenterX, WindowCenterY - (ButtonSizeY / 2.f));

	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Graphics_DrawRect(QuitButtonPosX, QuitButtonPosY, ButtonSizeX, ButtonSizeY);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	char buffer2[5] = { 0 };
	sprintf_s(buffer2, 5, "Quit");
	CP_Font_DrawText(buffer2, WindowCenterX - (ButtonSizeX / 2.f) + (ButtonSizeX/2.f), WindowCenterY + (ButtonSizeY * 1.5f));
	UpdateMainMenuKeyInput();
}

void MainMenuExit(void)
{

}

void UpdateMainMenuKeyInput(void)
{
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))//Move Left
	{
		float MousePosX = CP_Input_GetMouseX();
		float MousePosY = CP_Input_GetMouseY();
		if (MousePosX >= StartButtonPosX &&
			MousePosX <= StartButtonPosX + ButtonSizeX &&
			MousePosY >= StartButtonPosY &&
			MousePosY <= StartButtonPosY + ButtonSizeY)
		{
			CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		}
		else if (MousePosX >= QuitButtonPosX &&
			MousePosX <= QuitButtonPosX + ButtonSizeX &&
			MousePosY >= QuitButtonPosY &&
			MousePosY <= QuitButtonPosY + ButtonSizeY)
		{
			CP_Engine_Terminate();
		}
	}
}