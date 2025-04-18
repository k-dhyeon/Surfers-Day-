#include "GlobalVariables.h"
#include "cprocessing.h"
#include "drone.h"

float energyPosx;
float energyPosy;

void energybar()
{
	//CharacterData.CharacterPos = CP_Vector_Set((GameData.LaneMax.x - GameData.LaneMin.x) / 5.f, (GameData.LaneMax.y - GameData.LaneMin.y) / 2.f);
	//CharacterData.Energy = 200.f;
	//CharacterData.CharacterImage = CP_Image_Load("./Assets/Swim.png");
	//CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
	// 이 코드가 에너지 바 그리는 코드다
	//CP_Image_Load("./Assets/drone.png");
	
	energyPosx = CharacterData.CharacterPos.x + 500.f;
	energyPosy = CharacterData.CharacterPos.y + 30.f;
	energyPosy += energyPosy;
	float Ratio = 0.7f;
	CP_Settings_Fill(CP_Color_Create(205, 92, 92, 324)); //붉은
	CP_Graphics_DrawRect(energyPosx, energyPosy, 200.f* Ratio, 20.f);
	CP_Settings_Fill(CP_Color_Create(29, 234, 87, 123)); //청록
	CP_Graphics_DrawRect(energyPosx, energyPosy, CharacterData.Energy*Ratio, 20.f);
	
	

}

