#include "GlobalVariables.h"
#include "cprocessing.h"

#define SCREEN_WIDTH dronePosx + 50
#define SCREEN_HEIGHT dronePosy

float dronePosx;
float dronePosy;

void dronexy()
{
	dronePosx = CharacterData.CharacterPos.x + 570.f;
	dronePosy = CharacterData.CharacterPos.y + 30.f;
}

void drone()
{
	dronePosx = CharacterData.CharacterPos.x + 570.f;
	dronePosy = CharacterData.CharacterPos.y + 30.f;
	dronePosy += dronePosy;


	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
	CP_Graphics_DrawCircle(dronePosx, dronePosy, 180);

	CP_Graphics_DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y, dronePosx, dronePosy);
}