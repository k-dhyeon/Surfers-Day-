#include "GlobalVariables.h"
#include "cprocessing.h"
#include "drone.h"

float energyPosx;
float energyPosy;

float EnergyOffsetX = 10.f;
float EnergyOffsetY = 10.f;

float EnergyBarWidth = 400.f;
float EnergyBarHeight = 40.f;
void energybar()
{
	//CharacterData.CharacterPos = CP_Vector_Set((GameData.LaneMax.x - GameData.LaneMin.x) / 5.f, (GameData.LaneMax.y - GameData.LaneMin.y) / 2.f);
	//CharacterData.Energy = 200.f;
	//CharacterData.CharacterImage = CP_Image_Load("./Assets/Swim.png");
	//CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
	// 이 코드가 에너지 바 그리는 코드다
	//CP_Image_Load("./Assets/drone.png");
	//EnergyOffsetX = 10.f;//180 * (0.8f + (1.0f - 0.8f) * DraneSizeAlpha)/2.f;
	energyPosx = CP_System_GetWindowWidth()- EnergyBarWidth;//dronePosx;
	energyPosy = 0.f;//dronePosy;
	float Ratio = 1.f;//(0.8f + (1.0f - 0.8f) * DraneSizeAlpha) / 2.f;
	
	CP_Settings_Fill(CP_Color_Create(205, 92, 92, 255)); //붉은
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + EnergyOffsetY, EnergyBarWidth * Ratio, EnergyBarHeight);
	CP_Settings_Fill(CP_Color_Create(29, 234, 87, 123)); //청록
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + EnergyOffsetY, CharacterData.Energy*2*Ratio, EnergyBarHeight);

	float JumpTimerRatio = CharacterData.JumpTimer == 0.f ? 1.f: CharacterData.JumpTimer / 5.f;
	CP_Settings_Fill(CP_Color_Create(125, 125, 125, 255)); //gray
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + EnergyBarHeight + EnergyOffsetY, EnergyBarWidth * Ratio, EnergyBarHeight);
	CP_Settings_Fill(CP_Color_Create(9, 208, 239, 255)); //gray
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + EnergyBarHeight + EnergyOffsetY, EnergyBarWidth * JumpTimerRatio * Ratio, EnergyBarHeight);
}

