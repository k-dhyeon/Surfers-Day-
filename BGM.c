#include "BGM.h"


CP_Sound MainMenuBGM;
CP_Sound InGameBGM;


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
