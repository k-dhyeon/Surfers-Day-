#include "FlowBackGround.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "Math.h"
void FlowWater()
{
    //  �̹��� ũ��
    float imageWidth = (float)CP_Image_GetWidth(SeaImage[0]);
    //  �����Ӹ��� ���� offset (�������� �̵�)
    float scrollOffset = 0.0f;
    scrollOffset += GameData.Speed * CP_System_GetFrameCount();
    scrollOffset = fmodf(scrollOffset, imageWidth);
    

    //  �׸� ���� ũ�� (Lane ũ��)
    float drawWidth = GameData.LaneMax.x - GameData.LaneMin.x;
    float drawHeight = GameData.LaneMax.y - GameData.LaneMin.y;

    //  offset�� �̹������� ũ�� �ǵ�����
    if (scrollOffset >= imageWidth)
        scrollOffset -= imageWidth;

    //  �̹��� ���� �� ���̱� ���� �� ���� �ʿ����� ���
    int tilesNeeded = (int)(drawWidth / imageWidth) + 2; // +2�� ��ƴ ������

    //  �̹��� Ÿ�ϸ� ����
    for (int i = 0; i < tilesNeeded; i++) 
    {
        float drawX = GameData.LaneMin.x + i * imageWidth - scrollOffset;
        CP_Image_Draw(SeaImage[0],drawX,GameData.LaneMin.y,imageWidth,drawHeight,255);
    }
}
