#pragma once

#include "cprocessing.h"

extern CP_Sound MainMenuBGM;
extern CP_Sound InGameBGM;

extern CP_Sound SFXBatteryRecharge;
extern CP_Sound SFXJump;
extern CP_Sound SFXCollision;
extern CP_Sound SFXCombo;

void PlayMainMenuBGM();

void StopMainMenuBGM();

void PlayInGameBGM();

void StopInGameBGM();

void PlaySFXBatteryRecharge();
void PlaySFXJump();
void PlaySFXCollision();
void PlaySFXCombo();