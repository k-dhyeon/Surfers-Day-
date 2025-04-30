#include "GlobalVariables.h"
#include "cprocessing.h"
#include "drone.h"

float energyPosx;
float energyPosy;

float EnergyOffsetX;
float EnergyOffsetY = 0.f;

void energybar()
{
	//CharacterData.CharacterPos = CP_Vector_Set((GameData.LaneMax.x - GameData.LaneMin.x) / 5.f, (GameData.LaneMax.y - GameData.LaneMin.y) / 2.f);
	//CharacterData.Energy = 200.f;
	//CharacterData.CharacterImage = CP_Image_Load("./Assets/Swim.png");
	//CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
	// 이 코드가 에너지 바 그리는 코드다
	//CP_Image_Load("./Assets/drone.png");
	EnergyOffsetX = 0.f;//180 * (0.8f + (1.0f - 0.8f) * DraneSizeAlpha)/2.f;
	energyPosx = 0.f;//dronePosx;
	energyPosy = 0.f;//dronePosy;
	float Ratio = 1.f;//(0.8f + (1.0f - 0.8f) * DraneSizeAlpha) / 2.f;
	
	CP_Settings_Fill(CP_Color_Create(205, 92, 92, 255)); //붉은
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy - EnergyOffsetY, 200.f* Ratio, 20.f);
	CP_Settings_Fill(CP_Color_Create(29, 234, 87, 123)); //청록
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy - EnergyOffsetY, CharacterData.Energy*Ratio, 20.f);

	float JumpTimerRatio = CharacterData.JumpTimer == 0.f ? 1.f: CharacterData.JumpTimer / 5.f;
	CP_Settings_Fill(CP_Color_Create(125, 125, 125, 255)); //gray
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + 20.f - EnergyOffsetY, 200.f * Ratio, 20.f);
	CP_Settings_Fill(CP_Color_Create(9, 208, 239, 255)); //gray
	CP_Graphics_DrawRect(energyPosx - EnergyOffsetX, energyPosy + 20.f - EnergyOffsetY, 200.f * JumpTimerRatio * Ratio, 20.f);
}

