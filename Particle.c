﻿#include "Particle.h"

void generate_splash_particles(float OffsetX, float OffsetY) {
    if (CharacterData.CharacterState == STANDING)
    {
        float MaxRadiusX = 0.f;
        float MaxRadiusY = 0.f;
        if (bIsForwardPressed)
        {
            MaxRadiusX = 100.f;
            MaxRadiusY = 60.f;
            //MaxRadiusX = 200.f;
            //MaxRadiusY = 100.f;
        }
        else if (bIsBackwardPressed)
        {
            return;
        }
        else
        {
            MaxRadiusX = 50.f;
            MaxRadiusY = 40.f;
        }
        float CharacterDrawRatio = 0.8f + 0.2f * (CharacterData.CharacterPos.y / (GameData.LaneMax.y - GameData.LaneMin.y));
        CP_Settings_NoStroke();
        for (int i = 0; i < PARTICLE_COUNT; ++i) {
            // 타원 반지름
            float radius_x = CP_Random_RangeFloat(10.f, MaxRadiusX);  // 가로 넓이 (좌우 퍼짐)
            float radius_y = CP_Random_RangeFloat(3.f, MaxRadiusY);  // 세로 높이 (위로 튀는 정도)
            // 물보라 중심 좌표 (캐릭터 뒤쪽)
            float cx = CharacterData.CharacterPos.x - radius_x / 2.f + (CharacterData.CharaterDrawSize.x * (1 - CharacterDrawRatio) / 2.f); // 살짝 뒤로
            float cy = GameData.LaneMin.y + CharacterData.CharacterPos.y + CharacterData.CharacterCollisionOffset.y + 20.f;

            // 반투명 흰색
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, CP_Random_RangeInt(100, 200)));

            float angle = PI * i / (PARTICLE_COUNT - 1); // 0~π
            float x = cx + radius_x * cosf(angle);
            float y = cy - radius_y * sinf(angle); // 위쪽 튐


            // 입자 크기 랜덤
            CP_Graphics_DrawCircle(x + OffsetX, y + OffsetY, CP_Random_RangeFloat(5.f, 25.f * CharacterDrawRatio));
        }
        CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
    }
}

void generate_whale_blow_particles(float OffsetX, float OffsetY) {
    float MaxRadiusX = 100.f;  // 좌우 퍼짐
    float MaxRadiusY = 60.f;   // 위로 튐

    CP_Settings_NoStroke();
    OffsetX -= 100.f;
    
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        // 타원 반지름
        float radius_x = CP_Random_RangeFloat(10.f, MaxRadiusX);  // 가로 넓이 (좌우 퍼짐)
        float radius_y = CP_Random_RangeFloat(3.f, MaxRadiusY);   // 세로 높이 (위로 튀는 정도)

        // 반투명 흰색
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, CP_Random_RangeInt(100, 200)));

        // 각 입자가 위쪽으로 뿜어져 나가는 모양을 만들어줍니다.
        float angle = PI * i / (PARTICLE_COUNT - 1); // 0~π 범위

        // 입자들이 위쪽으로 뿜어지는 형태로 만들기
        float x = OffsetX + radius_x * cosf(angle);  // 좌우 퍼짐
        float y = OffsetY - radius_y * sinf(angle);  // 위로 튀어오름

        // 입자 크기 랜덤
        float particle_size = CP_Random_RangeFloat(5.f, 25.f);

        // 입자 그리기
        CP_Graphics_DrawCircle(x, y, particle_size);
    }
    OffsetX += 200.f;
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        // 타원 반지름
        float radius_x = CP_Random_RangeFloat(10.f, MaxRadiusX);  // 가로 넓이 (좌우 퍼짐)
        float radius_y = CP_Random_RangeFloat(3.f, MaxRadiusY);   // 세로 높이 (위로 튀는 정도)

        // 반투명 흰색
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, CP_Random_RangeInt(100, 200)));

        // 각 입자가 위쪽으로 뿜어져 나가는 모양을 만들어줍니다.
        float angle = PI * i / (PARTICLE_COUNT - 1); // 0~π 범위

        // 입자들이 위쪽으로 뿜어지는 형태로 만들기
        float x = OffsetX + radius_x * cosf(angle);  // 좌우 퍼짐
        float y = OffsetY - radius_y * sinf(angle);  // 위로 튀어오름

        // 입자 크기 랜덤
        float particle_size = CP_Random_RangeFloat(5.f, 25.f);

        // 입자 그리기
        CP_Graphics_DrawCircle(x, y, particle_size);
    }
    OffsetX -= 100.f;
    for (int i = 0; i < PARTICLE_COUNT; ++i) {
        
        // 반투명 흰색
        CP_Settings_Fill(CP_Color_Create(255, 255, 255, CP_Random_RangeInt(30, 200)));


        // 입자들이 위쪽으로 뿜어지는 형태로 만들기
        float x = CP_Random_RangeFloat(OffsetX - 10.f, OffsetX + 10.f);
        float y = CP_Random_RangeFloat(OffsetY, OffsetY + 70.f);

        // 입자 크기 랜덤
        float particle_size = CP_Random_RangeFloat(5.f, 25.f);

        // 입자 그리기
        CP_Graphics_DrawCircle(x, y, particle_size);
    }
}