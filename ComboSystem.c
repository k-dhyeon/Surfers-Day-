#include "ComboSystem.h"
#include "GlobalVariables.h"
#include <string.h>
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
			//TODO : COMBO
			for (int j = 0; j < COMBO_COMMAND_LENGTH; j++)
			{
				CharacterData.ComboCommand[j] = '\0';
			}
			break;
			
			
		}
	}
}
