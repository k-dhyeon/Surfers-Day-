#include "FlowBackGround.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "Math.h"
void FlowWater()
{
    //  이미지 크기
    float imageWidth = (float)CP_Image_GetWidth(SeaImage[0]);
    //  프레임마다 누적 offset (왼쪽으로 이동)
    float scrollOffset = 0.0f;
    scrollOffset += GameData.Speed * CP_System_GetFrameCount();
    scrollOffset = fmodf(scrollOffset, imageWidth);
    

    //  그릴 영역 크기 (Lane 크기)
    float drawWidth = GameData.LaneMax.x - GameData.LaneMin.x;
    float drawHeight = GameData.LaneMax.y - GameData.LaneMin.y;

    //  offset이 이미지보다 크면 되돌리기
    if (scrollOffset >= imageWidth)
        scrollOffset -= imageWidth;

    //  이미지 여러 개 붙이기 위해 몇 개가 필요한지 계산
    int tilesNeeded = (int)(drawWidth / imageWidth) + 2; // +2는 빈틈 방지용

    //  이미지 타일링 루프
    for (int i = 0; i < tilesNeeded; i++) 
    {
        float drawX = GameData.LaneMin.x + i * imageWidth - scrollOffset;
        CP_Image_Draw(SeaImage[0],drawX,GameData.LaneMin.y,imageWidth,drawHeight,255);
    }
}
