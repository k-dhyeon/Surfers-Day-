#include "GlobalVariables.h"
#include "cprocessing.h"

#define SCREEN_WIDTH dronePosx + 50
#define SCREEN_HEIGHT dronePosy

float dronePosx;
float dronePosy;

void DrawLine(float CharacterX, float CharacterY, float DroneX, float DroneY);
CP_Vector LerpVector(CP_Vector V1, CP_Vector V2, float Alpha);

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

	//CP_Graphics_DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x, GameData.LaneMin.y + CharacterData.CharacterPos.y + CharacterData.HandOffset.y, dronePosx, dronePosy);
    DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x, GameData.LaneMin.y + CharacterData.CharacterPos.y + CharacterData.HandOffset.y, dronePosx, dronePosy);
}

void DrawLine(float CharacterX, float CharacterY, float DroneX, float DroneY)
{
    float curveDepthMin = 30.f;
    float curveDepthMax = 90.f;
    static float curveDepth = 30.f;
    static float CurrentTargetcurveDepth = 45.f;
    static bool bTargetPositive = true;
    int segments = 30;  // 줄을 나눌 구간 수
    static float CurveDepthDelta = 0.5f;

    if (bTargetPositive)
    {
        curveDepth += CurveDepthDelta;
    }
    else
    {
        curveDepth -= CurveDepthDelta;
    }
    if ((bTargetPositive && CurrentTargetcurveDepth < curveDepth) || (!bTargetPositive && CurrentTargetcurveDepth > curveDepth))
    {
        bTargetPositive = !bTargetPositive;
        if (bTargetPositive)
        {
            CurrentTargetcurveDepth = CP_Random_RangeFloat(curveDepth, curveDepthMax);
        }
        else
        {
            CurrentTargetcurveDepth = CP_Random_RangeFloat(curveDepthMin, curveDepth);
        }
        CurveDepthDelta = CP_Random_RangeFloat(0.2f,1.f);
    }

    for (int i = 0; i < segments; i++) {
        float t1 = i / (float)(segments);
        float t2 = (i + 1) / (float)(segments);

        // 구간별 보간
        CP_Vector p1 = LerpVector(CP_Vector_Set(CharacterX, CharacterY), CP_Vector_Set(DroneX, DroneY), t1);
        CP_Vector p2 = LerpVector(CP_Vector_Set(CharacterX, CharacterY), CP_Vector_Set(DroneX, DroneY), t2);

        // 중간이 아래로 휘도록 Y축 보정 (2차함수 형태)
        
        float curve1 = curveDepth * (4 * t1 * (1 - t1));  // 포물선
        float curve2 = curveDepth * (4 * t2 * (1 - t2));

        
        p1.y += curve1;
        p2.y += curve2;

        CP_Graphics_DrawLine(p1.x, p1.y, p2.x, p2.y);
    }
}

CP_Vector LerpVector(CP_Vector V1, CP_Vector V2, float Alpha)
{
    float X = V1.x + (V2.x - V1.x) * Alpha;
    float Y = V1.y + (V2.y - V1.y) * Alpha;
    return CP_Vector_Set(X,Y);
}