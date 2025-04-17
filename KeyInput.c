
#include "cprocessing.h"
#include "GlobalVariables.h"
#include "KeyInput.h"

float MovementSpeed = 100.f;
bool bIsForwardPressed = false;
bool bIsBackwardPressed = false;
bool bIsLeftPressed = false;
bool bIsRightPressed=false;

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

	if (CP_Input_KeyTriggered(KEY_SPACE))//Jump?
	{
		if (CharacterData.JumpTimer == 0.f)
		{
			CharacterData.bHasRecentlyJumped = true;

		}
	}
	//TODO : Submersion?
	//TEST ONLY
	if (CP_Input_KeyTriggered(KEY_1))//InstantDead
	{
		CharacterData.Energy = 0.f;
	}

}



bool CheckForwardLaneCollision()
{
	if (CharacterData.CharacterPos.x + CharacterData.CharacterCollisionSize.x < GameData.LaneMax.x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckBackwardLaneCollision()
{
	if (CharacterData.CharacterPos.x > GameData.LaneMin.x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckLeftLaneCollision()
{
	if (CharacterData.CharacterPos.y > 0.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CheckRightLaneCollision()
{
	if (CharacterData.CharacterPos.y + CharacterData.CharacterCollisionSize.y < GameData.LaneMax.y - GameData.LaneMin.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UpdateCharacterPosition()
{
	if (bIsForwardPressed && !bIsBackwardPressed)
	{
		if (CheckForwardLaneCollision())
		{
			CharacterData.CharacterPos.x+= CP_System_GetDt()*MovementSpeed;
		}
	}
	if (!bIsForwardPressed && bIsBackwardPressed)
	{
		if (CheckBackwardLaneCollision())
		{
			CharacterData.CharacterPos.x -= CP_System_GetDt() * MovementSpeed*4.f;
		}
	}
	if (bIsLeftPressed && !bIsRightPressed)
	{
		if (CheckLeftLaneCollision())
		{
			CharacterData.CharacterPos.y -= CP_System_GetDt() * MovementSpeed * 2.f;
		}
	}
	if (!bIsLeftPressed && bIsRightPressed)
	{
		if (CheckRightLaneCollision())
		{
			CharacterData.CharacterPos.y += CP_System_GetDt() * MovementSpeed * 2.f;
		}
	}
}

	