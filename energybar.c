#include "GlobalVariables.h"
#include "cprocessing.h"

void energybar()
{
	//CharacterData.CharacterPos = CP_Vector_Set((GameData.LaneMax.x - GameData.LaneMin.x) / 5.f, (GameData.LaneMax.y - GameData.LaneMin.y) / 2.f);
	//CharacterData.Energy = 200.f;
	//CharacterData.CharacterImage = CP_Image_Load("./Assets/Swim.png");
	//CharacterData.CharaterDrawSize = CP_Vector_Set(200.f,200.f);
	// �� �ڵ尡 ������ �� �׸��� �ڵ��
	
	CP_Settings_Fill(CP_Color_Create(205, 92, 92, 324)); //����
	CP_Graphics_DrawRect(CharacterData.CharacterPos.x + 500.f, CharacterData.CharacterPos.y + 30.f, 200.f, 20.f);
	CP_Settings_Fill(CP_Color_Create(29, 234, 87, 123)); //û��
	CP_Graphics_DrawRect(CharacterData.CharacterPos.x + 500.f, CharacterData.CharacterPos.y + 30.f, CharacterData.Energy, 20.f);

}