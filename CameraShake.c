#include "cprocessing.h"
#include "GlobalVariables.h"
float LeftTimeLength = 0;
float zoomAmount = 1.0;
float shakeStrength = 0.0;

void InitShake()
{
    LeftTimeLength = 0;
    zoomAmount = 1.0;
    shakeStrength = 0.0;
}

void StartShake(float TargetTimeLength, float zoom, float strength) {
    LeftTimeLength = TargetTimeLength;
    zoomAmount = zoom;
    shakeStrength = strength;
}

void UpdateShake() {
    if (LeftTimeLength > 0) 
    {
        float shakeX = CP_Random_RangeFloat(-shakeStrength, shakeStrength);
        float shakeY = CP_Random_RangeFloat(-shakeStrength, shakeStrength);

        CP_Settings_Translate(/*CP_System_GetDisplayWidth() /2 - (GameData.LaneMin.x + CharacterData.CharacterPos.x) * zoomAmount + */shakeX, /*CP_System_GetDisplayHeight() / 2 - (GameData.LaneMin.y + CharacterData.CharacterPos.y) * zoomAmount +*/ shakeY);
        CP_Settings_Scale(zoomAmount, zoomAmount);

        LeftTimeLength-=CP_System_GetDt();
    }
    else 
    {
//        CP_Settings_Translate(CP_System_GetDisplayWidth() / 2 - CharacterData.CharacterPos.x, CP_System_GetDisplayHeight() / 2 - CharacterData.CharacterPos.y);
    }
}
