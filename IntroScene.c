#include "IntroScene.h"
#include "cprocessing.h"
#include "MainMenu.h"
CP_Image DigipenIcon;
CP_Image TeamIcon;
float DeltaTime;
float WindowCenterX;
float WindowCenterY;

int MapToInt(float InValue);

void Intro_init(void)
{
	CP_System_SetWindowSize(1600, 900);
	CP_System_SetWindowTitle("Surfers_Day");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	DigipenIcon = CP_Image_Load("./Assets/DigiPen_RED.png");
	TeamIcon = CP_Image_Load("./Assets/Racing Laboratory.png");
	DeltaTime = 0.f;
	WindowCenterX = CP_System_GetWindowWidth()/2.f;
	WindowCenterY = CP_System_GetWindowHeight() / 2.f;
}

void Intro_update(void)
{
	DeltaTime += CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
	{
		CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	}
	if (DeltaTime < 5.f)
	{
		if (DeltaTime < 2.5f)
		{
			CP_Image_Draw(DigipenIcon, WindowCenterX - (CP_Image_GetWidth(DigipenIcon) / 2.f), WindowCenterY - (CP_Image_GetHeight(DigipenIcon) / 2.f), (float)CP_Image_GetWidth(DigipenIcon), (float)CP_Image_GetHeight(DigipenIcon), MapToInt(DeltaTime / 2.5f));
		}
		else
		{
			CP_Image_Draw(DigipenIcon, WindowCenterX - (CP_Image_GetWidth(DigipenIcon) / 2.f), WindowCenterY - (CP_Image_GetHeight(DigipenIcon) / 2.f), (float)CP_Image_GetWidth(DigipenIcon), (float)CP_Image_GetHeight(DigipenIcon), 255 - MapToInt((DeltaTime -2.5f) / 2.5f));
		}
	}
	else
	{
		float TeamIconWidth = (float)CP_Image_GetWidth(TeamIcon) * 0.5f;
		float TeamIconHeight = (float)CP_Image_GetHeight(TeamIcon) * 0.5f;
		if (DeltaTime < 7.5f)
		{
			CP_Image_Draw(TeamIcon, WindowCenterX - (TeamIconWidth / 2.f), WindowCenterY - TeamIconHeight / 2.f, TeamIconWidth, TeamIconHeight, MapToInt((DeltaTime - 5.f) / 2.5f));
		}
		else
		{
			CP_Image_Draw(TeamIcon, WindowCenterX - (TeamIconWidth / 2.f), WindowCenterY - TeamIconHeight / 2.f, TeamIconWidth, TeamIconHeight, 255 - MapToInt((DeltaTime - 7.5f) / 2.5f));
			if (DeltaTime > 10.f)
			{
				CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
			}
		}
	}
}

void Intro_exit(void)
{
}

int MapToInt(float InValue)//Clamp 0~1 to 0~255
{
	// 범위를 벗어나지 않도록 클램핑
	if (InValue < 0.0f) InValue = 0.0f;
	if (InValue > 1.0f) InValue = 1.0f;

	// 0~255로 매핑
	return (int)(InValue * 255.0f + 0.5f);
}