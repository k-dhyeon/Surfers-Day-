#include "MainMenu.h"
#include "cprocessing.h"
#include "stdio.h"
#include "Game.h"
#include "BGM.h"
#include "RankMenu.h"
#include "HowToPlay.h"
#include "AssetLib.h"
float WindowCenterX;
float WindowCenterY;
float ButtonSizeX = 200.f;
float ButtonSizeY = 100.f;
float StartButtonPosX;
float StartButtonPosY;
float QuitButtonPosX;
float QuitButtonPosY;
float RankButtonPosX;
float RankButtonPosY;
float HowToPlayButtonPosX;
float HowToPlayButtonPosY;


CP_Image MainMenuBackground;


void MainMenuInit(void)
{
	InitMenuUI();
	MainMenuBackground = CP_Image_Load("./Assets/MainMenuBackground.png");

	CP_System_SetWindowSize(1600, 900);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	WindowCenterX = (float)CP_System_GetWindowWidth()/2.f;
	WindowCenterY = (float)CP_System_GetWindowHeight()/2.f;
	StartButtonPosX = 800 - (ButtonSizeX+20.f)*2.f;//WindowCenterX + WindowCenterX/2.f - (ButtonSizeX / 2.f) ;
	StartButtonPosY = 900.f- (ButtonSizeY + 5.f) * 2.f - 15.f;//WindowCenterY - (ButtonSizeY)-5.f;
	QuitButtonPosX = 800 + (ButtonSizeX + 20.f) * 1.f;//WindowCenterX + WindowCenterX / 2.f - (ButtonSizeX / 2.f);
	QuitButtonPosY = 900.f - (ButtonSizeY + 5.f) * 2.f + 15.f;//WindowCenterY + (ButtonSizeY)+5.f;
	RankButtonPosX = 800 - (ButtonSizeX + 20.f) * 1.f;//WindowCenterX + WindowCenterX / 2.f - (ButtonSizeX / 2.f);
	RankButtonPosY = 900.f - (ButtonSizeY + 5.f) * 2.f + 15.f;//WindowCenterY;
	HowToPlayButtonPosX = 800 + (ButtonSizeX + 20.f) * 0.f;
	HowToPlayButtonPosY = 900.f - (ButtonSizeY + 5.f) * 2.f - 15.f;
	PlayMainMenuBGM();

}


void MainMenuUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	CP_Image_Draw(MainMenuBackground, 0,0, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight(),255);
	CP_Settings_TextSize(50.f);
	
	//StartButton
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Image_Draw(StartBoard, StartButtonPosX, StartButtonPosY, ButtonSizeX, ButtonSizeY, 255);
	//CP_Graphics_DrawRect(StartButtonPosX, StartButtonPosY, ButtonSizeX, ButtonSizeY);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("Start",StartButtonPosX+(ButtonSizeX /2.0f) , StartButtonPosY + (ButtonSizeY / 2.f));
	
	//QuitButton
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Image_Draw(QuitBoard, QuitButtonPosX, QuitButtonPosY, ButtonSizeX, ButtonSizeY, 255);
	//CP_Graphics_DrawRect(QuitButtonPosX, QuitButtonPosY, ButtonSizeX, ButtonSizeY);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("Quit", QuitButtonPosX + (ButtonSizeX / 2.0f) , QuitButtonPosY + (ButtonSizeY / 2.f));
	
	//RankButton
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Image_Draw(RankBoard, RankButtonPosX, RankButtonPosY, ButtonSizeX, ButtonSizeY, 255);
	//CP_Graphics_DrawRect(RankButtonPosX, RankButtonPosY, ButtonSizeX, ButtonSizeY);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("Rank", RankButtonPosX + (ButtonSizeX / 2.0f), RankButtonPosY + (ButtonSizeY / 2.f));

	//HowToPlayButton
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Image_Draw(HowBoard, HowToPlayButtonPosX, HowToPlayButtonPosY, ButtonSizeX, ButtonSizeY, 255);
	//CP_Graphics_DrawRect(RankButtonPosX, RankButtonPosY, ButtonSizeX, ButtonSizeY);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("HowTo", HowToPlayButtonPosX + (ButtonSizeX / 2.0f), HowToPlayButtonPosY + (ButtonSizeY / 2.f));
	
	UpdateMainMenuKeyInput();
}

void MainMenuExit(void)
{
	
}

void UpdateMainMenuKeyInput(void)
{
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
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
		else if (MousePosX >= RankButtonPosX &&
			MousePosX <= RankButtonPosX + ButtonSizeX &&
			MousePosY >= RankButtonPosY &&
			MousePosY <= RankButtonPosY + ButtonSizeY)
		{
			CP_Engine_SetNextGameState(RankMenuInit, RankMenuUpdate, RankMenuExit);
		}
		else if (MousePosX >= HowToPlayButtonPosX &&
			MousePosX <= HowToPlayButtonPosX + ButtonSizeX &&
			MousePosY >= HowToPlayButtonPosY &&
			MousePosY <= HowToPlayButtonPosY + ButtonSizeY)
		{
			CP_Engine_SetNextGameState(HowToPlayMenuInit, HowToPlayMenuUpdate, HowToPlayMenuExit);
		}
	}
}