#include "FlowBackGround.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "Math.h"
float scrollOffset = 0.0f;

void FlowWater()
{
    // 이미지 크기
    float imageWidth = (float)CP_Image_GetWidth(SeaImage[0]);

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
        CP_Image_Draw(SeaImage[0], drawX, GameData.LaneMin.y, imageWidth, drawHeight, 255);
    }
}
