#include "KeyInput.h"
#include "cprocessing.h"

void UpdateKeyInput()
{

	if (CP_Input_KeyDown(KEY_W))//Move Left
	{
		bIsLeftPressed = true;
	}
	else
	{
		bIsLeftPressed = false;
	}
	if (CP_Input_KeyDown(KEY_S))//Move Right
	{
		bIsRightPressed = true;
	}
	else
	{
		bIsRightPressed = false;
	}
	if (CP_Input_KeyDown(KEY_D))//Move Forward
	{
		bIsForwardPressed = true;
	}
	else
	{
		bIsForwardPressed = false;
	}
	if (CP_Input_KeyDown(KEY_A))//Move Back
	{
		bIsBackwardPressed = true;
	}
	else
	{
		bIsBackwardPressed = false;
	}
	if (CP_Input_KeyDown(KEY_SPACE))//Jump?
	{

	}
	//TODO : Submersion?
}

void CheckCollision()
{
	
}
