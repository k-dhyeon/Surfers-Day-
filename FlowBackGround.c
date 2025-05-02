#include "FlowBackGround.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "Math.h"
float scrollOffset = 0.0f;

void DrawWater()
{
    SeaAnimationData.AnimationTimer += CP_System_GetDt();
    if (SeaAnimationData.AnimationTimer > 0.3f)
    {
        if (SeaAnimationData.SeaIndex == 1)
        {
            SeaAnimationData.SeaIndex = 0;
            SeaAnimationData.AnimationTimer = 0.f;
        }
        else
        {
            SeaAnimationData.SeaIndex++;
            SeaAnimationData.AnimationTimer = 0.f;
        }
    }
    float imageWidth = (float)CP_Image_GetWidth(SeaAnimationData.SeaImage);
    float imageHeight = (float)CP_Image_GetHeight(SeaAnimationData.SeaImage);
    CP_Image_DrawSubImage(SeaAnimationData.SeaImage, GameData.LaneMin.x, GameData.LaneMin.y, GameData.LaneMax.x - GameData.LaneMin.x, GameData.LaneMax.y - GameData.LaneMin.y, (imageWidth / 2.f)* SeaAnimationData.SeaIndex, 0.f, (imageWidth / 2.f)* (SeaAnimationData.SeaIndex+1), imageHeight, 255);
    //TEST
    //CP_Image_Draw(SeaAnimationData.SeaImage, GameData.LaneMin.x, GameData.LaneMin.y, GameData.LaneMax.x - GameData.LaneMin.x, GameData.LaneMax.y - GameData.LaneMin.y,255 );
}

/*
void DrawWater()
{
    // 이미지 크기
    float imageWidth = (float)CP_Image_GetWidth(SeaAnimationData.SeaImage[0]);
    float imageHeight = (float)CP_Image_GetHeight(SeaAnimationData.SeaImage[0]);
    // 프레임당 시간에 따라 누적 offset (왼쪽으로 이동)
    float deltaTime = CP_System_GetDt(); // 프레임 간 시간
    scrollOffset += GameData.Speed * deltaTime;
    scrollOffset = fmodf(scrollOffset, imageWidth); // 이미지 너비를 넘으면 wrap

    // 그릴 영역 크기
    float drawWidth = GameData.LaneMax.x - GameData.LaneMin.x;
    float drawHeight = GameData.LaneMax.y - GameData.LaneMin.y;

    // 이미지 여러 개 붙이기 위해 몇 개가 필요한지 계산
    int tilesNeeded = (int)(drawWidth / imageWidth) + 2;

    // 이미지 타일링 루프
    for (int i = 0; i < tilesNeeded; i++)
    {
        float drawX = GameData.LaneMin.x + i * imageWidth - scrollOffset;
        CP_Image_DrawSubImage(SeaAnimationData.SeaImage[0], drawX, GameData.LaneMin.y, imageWidth, drawHeight, (imageWidth / 3.f)*i, 0.f, (imageWidth / 3.f) * (i+1), imageHeight, 255);
        //CP_Image_DrawSubImage	(CP_Image img, float x, float y, float w, float h, float u0, float v0, float u1, float v1, int alpha);
        //CP_Image_DrawSubImage(CharacterData.CharacterImage, GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y - CharacterData.CharaterDrawSize.y + CharacterData.CharacterCollisionSize.y, CharacterData.CharaterDrawSize.x, CharacterData.CharaterDrawSize.y, 100.f * CharacterData.AnimationFrame, 0.f, 100.f * (CharacterData.AnimationFrame+1), 100.f, 255);
    }


}
*/

void DrawSkyBackGround()
{
    // 시간에 따라 위치 이동
 //   SkyAnimationData.Position.x -= CP_System_GetDt() * GameData.Speed/60.f;

    float imageWidth = (float)CP_System_GetWindowWidth();//(float)CP_Image_GetWidth(SkyAnimationData.Image);
    float imageHeight = (float)CP_System_GetWindowHeight()/2.f;//(float)CP_Image_GetHeight(SkyAnimationData.Image);

    // 위치가 이미지 너비보다 왼쪽으로 벗어났다면 0으로 되돌림
    //if (SkyAnimationData.Position.x <= -imageWidth)
    //{
    //    SkyAnimationData.Position.x += imageWidth;
    //}
    CP_Image_Draw(SkyAnimationData.Image, SkyAnimationData.Position.x, SkyAnimationData.Position.y, imageWidth, imageHeight, 255);
//    CP_Image_Draw(SkyAnimationData.Image, SkyAnimationData.Position.x + imageWidth, SkyAnimationData.Position.y, imageWidth, imageHeight, 255);
//    CP_Image_Draw(SkyAnimationData.Image, SkyAnimationData.Position.x + imageWidth*2, SkyAnimationData.Position.y, imageWidth, imageHeight, 255);
}
void DrawFarBackGround()
{
    FarBackgroundAnimationData.Position.x -= CP_System_GetDt()*GameData.Speed/30.f;
    float imageWidth = (float)CP_Image_GetWidth(FarBackgroundAnimationData.Image);
    float imageHeight = (float)CP_Image_GetHeight(FarBackgroundAnimationData.Image);
    CP_Image_Draw(FarBackgroundAnimationData.Image, FarBackgroundAnimationData.Position.x, FarBackgroundAnimationData.Position.y, imageWidth, imageHeight, 255);
    //CP_Image_DrawSubImage(BridgeAnimationData.Image, 0.f, GameData.LaneMin.y - imageHeight, GameData.LaneMax.x, imageHeight, (imageWidth / 2.f) * SeaAnimationData.SeaIndex, 0.f, (imageWidth / 2.f) * (SeaAnimationData.SeaIndex + 1), imageHeight, 255);
 
    if (FarBackgroundAnimationData.Position.x < -imageWidth)
    {
        FarBackgroundAnimationData.Position.x = (float)CP_System_GetWindowWidth();
    }
}

void DrawBackGroundSeaGull()
{
    for (int i = 0; i < MAX_SEAGULL_NUM; i++)
    {
        SeaGullAnimationData[i].Timer += CP_System_GetDt()* SeaGullAnimationData[i].PlayRatio;
        SeaGullAnimationData[i].Position.x -= CP_System_GetDt() * GameData.Speed / 5.f * SeaGullAnimationData[i].PlayRatio;
        float imageWidth = (float)CP_Image_GetWidth(SeaGullAnimationData[i].Image) / 5.f;
        float imageHeight = (float)CP_Image_GetHeight(SeaGullAnimationData[i].Image);
        CP_Image_DrawSubImage(SeaGullAnimationData[i].Image, SeaGullAnimationData[i].Position.x, SeaGullAnimationData[i].Position.y, imageWidth, imageHeight, imageWidth * SeaGullAnimationData[i].Index, 0.f, imageWidth * (SeaGullAnimationData[i].Index + 1), imageHeight, 255);

        if (SeaGullAnimationData[i].Timer > 1.f)
        {
            if (SeaGullAnimationData[i].Index == 4)
            {
                SeaGullAnimationData[i].Index = 0;
            }
            else
            {
                SeaGullAnimationData[i].Index++;
            }
            SeaGullAnimationData[i].Timer = 0.f;
        }

        if (SeaGullAnimationData[i].Position.x < -imageWidth)
        {
            SeaGullAnimationData[i].Position.x = CP_Random_RangeFloat((float)CP_System_GetWindowWidth(), CP_System_GetWindowWidth() + 1600.f);
            SeaGullAnimationData[i].Position.y = CP_Random_RangeFloat(100.f, CP_System_GetWindowHeight()/2.f - 150.f);
            SeaGullAnimationData[i].PlayRatio = CP_Random_RangeFloat(0.4f, 2.f);
        }
    }
   
}

void DrawNearBackGround()
{
    CP_Image Sand = CP_Image_Load("./Assets/NearDistance.png");
    float SandWidth = (float)CP_Image_GetWidth(Sand);
    float SandHeight = (float)CP_Image_GetHeight(Sand);
    CP_Image_Draw(Sand, NearBackgroundAnimationData.Position.x, NearBackgroundAnimationData.Position.y, SandWidth, SandHeight, 255);
    CP_Image_Draw(Sand, NearBackgroundAnimationData.Position.x + SandWidth, NearBackgroundAnimationData.Position.y, SandWidth, SandHeight, 255);
    CP_Image_Draw(Sand, NearBackgroundAnimationData.Position.x - SandWidth, NearBackgroundAnimationData.Position.y, SandWidth, SandHeight, 255);

    // 더 빠르게 이동 (1.1배속)
    NearBackgroundAnimationData.Position.x -= CP_System_GetDt() * GameData.Speed * 1.1f;

    float imageWidth = (float)CP_Image_GetWidth(NearBackgroundAnimationData.Image);
    float imageHeight = (float)CP_Image_GetHeight(NearBackgroundAnimationData.Image);

    // 이미지가 왼쪽 끝까지 갔을 경우, 자연스럽게 이어지도록 보정
    if (NearBackgroundAnimationData.Position.x <= -imageWidth)
    {
        NearBackgroundAnimationData.Position.x += imageWidth;
    }

    // 두 장 이어 그리기
    CP_Image_Draw(NearBackgroundAnimationData.Image, NearBackgroundAnimationData.Position.x, NearBackgroundAnimationData.Position.y, imageWidth, imageHeight, 255);
    CP_Image_Draw(NearBackgroundAnimationData.Image, NearBackgroundAnimationData.Position.x + imageWidth, NearBackgroundAnimationData.Position.y, imageWidth, imageHeight, 255);
    CP_Image_Draw(NearBackgroundAnimationData.Image, NearBackgroundAnimationData.Position.x + imageWidth*2, NearBackgroundAnimationData.Position.y, imageWidth, imageHeight, 255);

   

    
    //CP_Image_DrawSubImage(BridgeAnimationData.Image, 0.f, GameData.LaneMin.y - imageHeight, GameData.LaneMax.x, imageHeight, (imageWidth / 2.f) * SeaAnimationData.SeaIndex, 0.f, (imageWidth / 2.f) * (SeaAnimationData.SeaIndex + 1), imageHeight, 255);
}
