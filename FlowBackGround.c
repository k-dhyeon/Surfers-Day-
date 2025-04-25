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
    // �̹��� ũ��
    float imageWidth = (float)CP_Image_GetWidth(SeaAnimationData.SeaImage[0]);
    float imageHeight = (float)CP_Image_GetHeight(SeaAnimationData.SeaImage[0]);
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
        CP_Image_DrawSubImage(SeaAnimationData.SeaImage[0], drawX, GameData.LaneMin.y, imageWidth, drawHeight, (imageWidth / 3.f)*i, 0.f, (imageWidth / 3.f) * (i+1), imageHeight, 255);
        //CP_Image_DrawSubImage	(CP_Image img, float x, float y, float w, float h, float u0, float v0, float u1, float v1, int alpha);
        //CP_Image_DrawSubImage(CharacterData.CharacterImage, GameData.LaneMin.x + CharacterData.CharacterPos.x, GameData.LaneMin.y + CharacterData.CharacterPos.y - CharacterData.CharaterDrawSize.y + CharacterData.CharacterCollisionSize.y, CharacterData.CharaterDrawSize.x, CharacterData.CharaterDrawSize.y, 100.f * CharacterData.AnimationFrame, 0.f, 100.f * (CharacterData.AnimationFrame+1), 100.f, 255);
    }


}
*/

void DraawSkyBackGround()
{
    
}
void DrawFarBackGround()
{
    BridgeAnimationData.AnimationTimer += CP_System_GetDt();
    if (BridgeAnimationData.AnimationTimer > 0.3f)
    {
        if (BridgeAnimationData.Index == 1)
        {
            BridgeAnimationData.Index = 0;
            BridgeAnimationData.AnimationTimer = 0.f;
        }
        else
        {
            BridgeAnimationData.Index++;
            BridgeAnimationData.AnimationTimer = 0.f;
        }
    }
    //float imageWidth = (float)CP_Image_GetWidth(BridgeAnimationData.Image);
    float imageHeight = (float)CP_Image_GetHeight(BridgeAnimationData.Image);
    CP_Image_Draw(BridgeAnimationData.Image, 0.f, GameData.LaneMin.y - imageHeight, GameData.LaneMax.x, imageHeight, 255);
    //CP_Image_DrawSubImage(BridgeAnimationData.Image, 0.f, GameData.LaneMin.y - imageHeight, GameData.LaneMax.x, imageHeight, (imageWidth / 2.f) * SeaAnimationData.SeaIndex, 0.f, (imageWidth / 2.f) * (SeaAnimationData.SeaIndex + 1), imageHeight, 255);
 

}

void DrawNearBackGround()
{

}
