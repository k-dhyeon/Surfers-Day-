#include "ComboSystem.h"
#include "GlobalVariables.h"
#include <string.h>
#include "BGM.h"
#define COMBO_NUM 2

char ComboArr[COMBO_NUM][COMBO_COMMAND_LENGTH] =
{
	{'A','W','D'},
	{'D','W','A'}
};

void CheckCombo()
{
	for (int i = 0; i < COMBO_NUM; i++)
	{
		if (strstr(CharacterData.ComboCommand, ComboArr[i]) != NULL)
		{
			switch (i)
			{
			case 0 :
				SetCharacterState(COMBO1);
				break;
			case 1:
				SetCharacterState(COMBO2);
				break;
			default:
				break;
			}
			PlaySFXCombo();
			for (int j = 0; j < COMBO_COMMAND_LENGTH; j++)
			{
				CharacterData.ComboCommand[j] = '\0';
			}
			break;
			
			
		}
	}
}
