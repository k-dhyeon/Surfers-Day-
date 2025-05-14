#include "BGM.h"
#include "stdbool.h"

CP_Sound MainMenuBGM;
CP_Sound InGameBGM;

CP_Sound SFXBatteryRecharge;
CP_Sound SFXJump;
CP_Sound SFXCollision;
CP_Sound SFXCombo;
CP_Sound SFXGameOver;
CP_Sound SFXMedal;
bool bIsMainMenuPlaying = false;

void PlayMainMenuBGM()
{
	if (!bIsMainMenuPlaying)
	{
		CP_Sound_PlayAdvanced(MainMenuBGM, 1.0, 1.0, TRUE, CP_SOUND_GROUP_MUSIC);
		bIsMainMenuPlaying = true;
	}
}

void StopMainMenuBGM()
{
	CP_Sound_StopAll();
	bIsMainMenuPlaying = false;
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
	CP_Sound_PlayAdvanced(SFXCollision, 5.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXCombo()
{
	CP_Sound_PlayAdvanced(SFXCombo, 1.0, 1.0, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXGameOver()
{
	CP_Sound_PlayAdvanced(SFXGameOver, 4.f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
}

void PlaySFXMedal()
{
	CP_Sound_PlayAdvanced(SFXMedal, 1.f, 1.0f, FALSE, CP_SOUND_GROUP_SFX);
}