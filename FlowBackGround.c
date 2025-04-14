#include "FlowBackGround.h"
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "Math.h"
float scrollOffset = 0.0f;

void FlowWater()
{
    // �̹��� ũ��
    float imageWidth = (float)CP_Image_GetWidth(SeaImage[0]);

    // �����Ӵ� �ð��� ���� ���� offset (�������� �̵�)
    float deltaTime = CP_System_GetDt(); // ������ �� �ð�
    scrollOffset += GameData.Speed * deltaTime;
    scrollOffset = fmodf(scrollOffset, imageWidth); // �̹��� �ʺ� ������ wrap

    // �׸� ���� ũ��
    float drawWidth = GameData.LaneMax.x - GameData.LaneMin.x;
    float drawHeight = GameData.LaneMax.y - GameData.LaneMin.y;

    // �̹��� ���� �� ���̱� ���� �� ���� �ʿ����� ���
    int tilesNeeded = (int)(drawWidth / imageWidth) + 2;

    // �̹��� Ÿ�ϸ� ����
    for (int i = 0; i < tilesNeeded; i++)
    {
        float drawX = GameData.LaneMin.x + i * imageWidth - scrollOffset;
        CP_Image_Draw(SeaImage[0], drawX, GameData.LaneMin.y, imageWidth, drawHeight, 255);
    }
}
