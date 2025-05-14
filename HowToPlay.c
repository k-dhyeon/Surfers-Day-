#include "cprocessing.h"
#include "HowToPlay.h"
#include "MainMenu.h"
#include "AssetLib.h"
CP_Image HowToPlayBackGround;

float ExitButtonX = 700.f;
float ExitButtonY = 900.f - (105.f);
float ExitButtonSizeX = 200.f;
float ExitButtonSizeY = 100.f;

void HowToPlayMenuInit(void)
{
	HowToPlayBackGround = CP_Image_Load("./Assets/howtoplay.png");
}

void HowToPlayMenuUpdate(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255,255,255,255));
	CP_Image_Draw(HowToPlayBackGround,0.f,0.f,1600.f,900.f,255);

	//HowToPlayButton
	CP_Settings_Fill(CP_Color_Create(64, 64, 64, 255));
	CP_Image_Draw(UIBoard, ExitButtonX, ExitButtonY, ExitButtonSizeX, ExitButtonSizeY, 255);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Exit", ExitButtonX + 100.f, ExitButtonY + 50.f);

	UpdateHowToPlayMenuKeyInput();
}

void HowToPlayMenuExit(void)
{

}

void UpdateHowToPlayMenuKeyInput(void)
{
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}
	else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		float MousePosX = CP_Input_GetMouseX();
		float MousePosY = CP_Input_GetMouseY();
		if (MousePosX >= ExitButtonX &&
			MousePosX <= ExitButtonX + ExitButtonSizeX &&
			MousePosY >= ExitButtonY &&
			MousePosY <= ExitButtonY + ExitButtonSizeY)
		{
			CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
		}
	}
}