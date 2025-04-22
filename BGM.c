#include "BGM.h"


CP_Sound MainMenuBGM;
CP_Sound InGameBGM;

CP_Sound SFXBatteryRecharge;
CP_Sound SFXJump;
CP_Sound SFXCollision;
CP_Sound SFXCombo;

void PlayMainMenuBGM()
{
	CP_Sound_PlayAdvanced(MainMenuBGM, 1.0, 1.0, TRUE, CP_SOUND_GROUP_MUSIC);
}

void StopMainMenuBGM()
{
	CP_Sound_StopAll();
}

void PlayInGameBGM()
{
	CP_Sound_PlayAdvanced(InGameBGM, 1.0, 1.0, TRUE, CP_SOUND_GROUP_MUSIC);
}

void StopInGameBGM()
{
	CP_Sound_StopAll();
}

void PlaySFXBatteryRecharge()
{
	CP_Sound_PlayAdvanced(SFXBatteryRecharge, 1.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXJump()
{
	CP_Sound_PlayAdvanced(SFXJump, 1.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXCollision()
{
	CP_Sound_PlayAdvanced(SFXCollision, 1.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXCombo()
{
	CP_Sound_PlayAdvanced(SFXCombo, 1.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

