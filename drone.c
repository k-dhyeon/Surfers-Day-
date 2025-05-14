#include "GlobalVariables.h"
#include "cprocessing.h"
#include "KeyInput.h"
#include "math.h"
#include "stdlib.h"
#include "AssetLib.h"
#define PI 3.14159265


float Angle = 0.f;
float Radius = 5.f;
float dronePosx;
float dronePosy;
float DraneSizeAlpha;
float DroneOffsetX = 0.f;
float DroneOffsetY = 0.f;
float DronePositionYtoXMaxOffset = 100.f;
float DroneDrawMinimumRatio = 0.8f;

float jitterTargetX = 0;
float jitterTargetY = 0;
float jitterCurrentX = 0;
float jitterCurrentY = 0;
float jitterTimer = 0.0f;
float jitterInterval = 0.5f;

void DrawLine(float CharacterX, float CharacterY, float DroneX, float DroneY);
CP_Vector LerpVector(CP_Vector V1, CP_Vector V2, float Alpha);

float AnimationTime = 0.f;
int AnimationIndex = 0;



void drone()
{
    //if (CharacterData.Energy > 100.f)
    //{
    //    AnimationTime = 0.f;
    //    AnimationIndex = 0;
    //}
    //else
    {
        AnimationTime += CP_System_GetDt();
        if (AnimationTime > 0.3f)
        {
            if (AnimationIndex == 1)
            {
                AnimationIndex--;
            }
            else
            {
                AnimationIndex++;
            }
            AnimationTime = 0.f;
        }
    }
    
    float DeltaDronePosX = targetPosition.x - CharacterData.CharacterPos.x;
    float DeltaDronePosY = targetPosition.y - CharacterData.CharacterPos.y;

    DraneSizeAlpha = (CharacterData.CharacterPos.y) / (GameData.LaneMax.y - GameData.LaneMin.y);

	dronePosx = CharacterData.CharacterPos.x + DeltaDronePosX + 570.f;
    dronePosx += DronePositionYtoXMaxOffset * -DraneSizeAlpha;
	dronePosy = CharacterData.CharacterPos.y + DeltaDronePosY + 30.f;
	dronePosy *= 2.f;

    //if (CharacterData.CharacterState == WAVING)
    //{
    //    dronePosx = CharacterData.CharacterPos.x - 100.f;
    //    dronePosy = GameData.LaneMin.y - 100.f;
    //}
    if (dronePosy > CP_System_GetWindowHeight())
    {
        dronePosy = (float)CP_System_GetWindowHeight();
    }

    Angle += CP_System_GetDt()*2.f;
    if (Angle > 360.f)
    {
        Angle -= 360.f;
    }
    DroneOffsetX = Radius * (float)cos(Angle);
    DroneOffsetY = Radius * (float)sin(Angle);

    jitterTimer += CP_System_GetDt();
    if (jitterTimer >= jitterInterval) {
        jitterTimer = 0.0f;
        // 새로운 랜덤 목표 생성 (-10 ~ +10)
        jitterTargetX = ((rand() % 100) / 100.0f - 0.5f) * 20.0f;
        jitterTargetY = ((rand() % 100) / 100.0f - 0.5f) * 20.0f;
    }

    float smoothFactor = 0.05f; // 0.1~0.2가 부드러움
    jitterCurrentX += (jitterTargetX - jitterCurrentX) * smoothFactor;
    jitterCurrentY += (jitterTargetY - jitterCurrentY) * smoothFactor;

    dronePosx += DroneOffsetX + jitterCurrentX;
    dronePosy += DroneOffsetY + jitterCurrentY;

	CP_Settings_Fill(CP_Color_Create(128, 128, 128, 255));
    float DroneWidth = (float)CP_Image_GetWidth(DroneImage);// *2.f;
    float DroneHeight = (float)CP_Image_GetHeight(DroneImage) * 2.f;
    //CP_Image_Draw(DroneImage, dronePosx - DroneWidth/2.f, dronePosy - DroneHeight/2.f, DroneWidth, DroneHeight, 255);
    CP_Image_DrawSubImage(DroneImage, dronePosx - DroneWidth / 2.f, dronePosy - DroneHeight / 2.f, DroneWidth, DroneHeight, 100.f* AnimationIndex,0.f,100.f * (AnimationIndex + 1),100.f, 255);
	//CP_Graphics_DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x, GameData.LaneMin.y + CharacterData.CharacterPos.y + CharacterData.HandOffset.y, dronePosx, dronePosy);
    float CharacterDrawRatio = 0.8f + 0.2f * (CharacterData.CharacterPos.y / (GameData.LaneMax.y - GameData.LaneMin.y));
    if (CharacterData.CharacterState == HEIGHESTWAVE)
    {
        CharacterDrawRatio = 0.5f;
        DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x - 30.f, GameData.LaneMin.y + CharacterData.CharacterPos.y * CharacterDrawRatio - 80.f, dronePosx, dronePosy);
    }
    else if (CharacterData.CharacterState == STARTWAVE || CharacterData.CharacterState == ENDWAVE)
    {
        DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x - 20.f, GameData.LaneMin.y + CharacterData.CharacterPos.y * CharacterDrawRatio - 70.f, dronePosx, dronePosy);
    }
    else if (CharacterData.CharacterState == WAVING)
    {
        DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x - 30.f, GameData.LaneMin.y + CharacterData.CharacterPos.y * CharacterDrawRatio - 48.f, dronePosx, dronePosy);
    }
    else
    {
        float HandOffsetDelta = (CharacterData.HandOffset.x - CharacterData.HandOffset.x * 0.8f) / 2.f;
        DrawLine(GameData.LaneMin.x + CharacterData.CharacterPos.x + CharacterData.HandOffset.x - HandOffsetDelta * (1 - CharacterData.CharacterPos.y / (GameData.LaneMax.y - GameData.LaneMin.y)), GameData.LaneMin.y + CharacterData.CharacterPos.y + CharacterData.HandOffset.y * CharacterDrawRatio, dronePosx, dronePosy);
    }
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

    if (bIsForwardPressed && 15.f <= curveDepth)
    {
        bTargetPositive = false;
    }
    else if (bIsBackwardPressed && 120.f >= curveDepth)
    {     
        bTargetPositive = true;
    }
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
    CP_Settings_StrokeWeight(1.f);
    for (int i = 0; i < segments; i++) {
        float t1 = i / (float)(segments);
        float t2 = (i + 1) / (float)(segments);

        // 구간별 보간
        CP_Vector p1 = LerpVector(CP_Vector_Set(CharacterX, CharacterY), CP_Vector_Set(DroneX, DroneY), t1);
        CP_Vector p2 = LerpVector(CP_Vector_Set(CharacterX, CharacterY), CP_Vector_Set(DroneX, DroneY), t2);

        // 중간이 아래로 휘도록 Y축 보정 (2차함수 형태)
        
        float curve1 = curveDepth * (4 * t1 * (1 - t1));  // 포물선
        float curve2 = curveDepth * (4 * t2 * (1 - t2));

        float Alpha = 1.f - (CharacterData.CharacterPos.y) / (GameData.LaneMax.y - GameData.LaneMin.y);
        if (Alpha < 0.05f)
        {
            Alpha = 0.05f;
        }
        curve1 *= Alpha;
        curve2 *= Alpha;
        
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