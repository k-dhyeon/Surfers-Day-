
#include "KeyInput.h"

#include "cprocessing.h"
#include "GlobalVariables.h"
#include "ComboSystem.h"
#include "BGM.h"

float MovementSpeed = 100.f;
bool bIsForwardPressed = false;
bool bIsBackwardPressed = false;
bool bIsLeftPressed = false;
bool bIsRightPressed=false;

float movementDelayTimer = 0.0f;
float movementDelayDuration = 0.2f; // 0.2초 지연
CP_Vector targetPosition;
int initialized = 0;

void InitKeyInput()
{
	initialized = 0;
}

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
	if (CharacterData.CharacterState == STARTWAVE || CharacterData.CharacterState == ENDWAVE)
	{
		bIsLeftPressed = false;
		bIsRightPressed = false;
		return;
	}
	if (CP_Input_KeyTriggered(KEY_SPACE))//Jump?
	{
		if (CharacterData.CharacterState == STANDING)
		{
			if (CharacterData.JumpTimer == 0.f)
			{
				PlaySFXJump();
				SetCharacterState(JUMPUP);
				CharacterData.ComboIndex = 0;
				for (int i = 0; i < COMBO_COMMAND_LENGTH;i++)
				{
					CharacterData.ComboCommand[i] = '\0';
				}
			}
		}
	}
	if (CharacterData.CharacterState == JUMPUP || CharacterData.CharacterState == JUMPDOWN)
	{
		if (CP_Input_KeyTriggered(KEY_W))//Move Left
		{
			if (CharacterData.ComboIndex < COMBO_COMMAND_LENGTH - 1)
			{
				CharacterData.ComboCommand[CharacterData.ComboIndex] = 'W';
				CharacterData.ComboIndex++;
			}
		}
		if (CP_Input_KeyTriggered(KEY_S))//Move Right
		{
			if (CharacterData.ComboIndex < COMBO_COMMAND_LENGTH - 1)
			{
				CharacterData.ComboCommand[CharacterData.ComboIndex] = 'S';
				CharacterData.ComboIndex++;
			}
		}
		if (CP_Input_KeyTriggered(KEY_A))//Move Backward
		{
			if (CharacterData.ComboIndex < COMBO_COMMAND_LENGTH - 1)
			{
				CharacterData.ComboCommand[CharacterData.ComboIndex] = 'A';
				CharacterData.ComboIndex++;
			}
		}
		if (CP_Input_KeyTriggered(KEY_D))//Move Forward
		{
			if (CharacterData.ComboIndex < COMBO_COMMAND_LENGTH - 1)
			{
				CharacterData.ComboCommand[CharacterData.ComboIndex] = 'D';
				CharacterData.ComboIndex++;
			}
		}
		CheckCombo();
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
	if (CharacterData.CharacterPos.x + CharacterData.CharacterCollisionSize.x + CharacterData.CharacterCollisionOffset.x < GameData.LaneMax.x)
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

//void UpdateCharacterPosition()
//{
//	if (bIsForwardPressed && !bIsBackwardPressed)
//	{
//		if (CheckForwardLaneCollision())
//		{
//			CharacterData.CharacterPos.x += CP_System_GetDt() * MovementSpeed * 2.f;
//		}
//	}
//	if (!bIsForwardPressed && bIsBackwardPressed)
//	{
//		if (CheckBackwardLaneCollision())
//		{
//			CharacterData.CharacterPos.x -= CP_System_GetDt() * MovementSpeed * 4.f;
//		}
//	}
//	if (bIsLeftPressed && !bIsRightPressed)
//	{
//		if (CheckLeftLaneCollision())
//		{
//			CharacterData.CharacterPos.y -= CP_System_GetDt() * MovementSpeed * 2.5f;
//		}
//	}
//	if (!bIsLeftPressed && bIsRightPressed)
//	{
//		if (CheckRightLaneCollision())
//		{
//			CharacterData.CharacterPos.y += CP_System_GetDt() * MovementSpeed * 2.5f;
//		}
//	}
//}

void UpdateCharacterPosition()
{
	float dt = CP_System_GetDt();
	float moveAmount = dt * MovementSpeed;

	// 최초 1회 현재 위치를 목표 위치로 초기화
	if (!initialized) {
		targetPosition = CharacterData.CharacterPos;
		initialized = 1;
	}

	// 누적 목표 위치 계산
	if (bIsForwardPressed && !bIsBackwardPressed)
	{
		if (targetPosition.x > GameData.LaneMax.x)
		{
			targetPosition.x = GameData.LaneMax.x;
		}
		if (CheckForwardLaneCollision())
		{
			targetPosition.x += moveAmount * 2.f;
			
		}
	}
	if (!bIsForwardPressed && bIsBackwardPressed)
	{
		if (targetPosition.x < GameData.LaneMin.x)
		{
			targetPosition.x = GameData.LaneMin.x;
		}
		if (CheckBackwardLaneCollision())
		{
			targetPosition.x -= moveAmount * 4.f;
		}
	}
	if (bIsLeftPressed && !bIsRightPressed)
	{
		if (targetPosition.y < 0.f)
		{
			targetPosition.y = 0.f;
		}
		if (CheckLeftLaneCollision())
		{
			targetPosition.y -= moveAmount * 2.5f;
		}	
	}
	if (!bIsLeftPressed && bIsRightPressed)
	{
		if (targetPosition.y > GameData.LaneMax.y - GameData.LaneMin.y - CharacterData.CharacterCollisionSize.y)
		{
			targetPosition.y = GameData.LaneMax.y - GameData.LaneMin.y - CharacterData.CharacterCollisionSize.y;
		}
		if (CheckRightLaneCollision())
		{
			targetPosition.y += moveAmount * 2.5f;
		}
	}

	// 목표 위치로 부드럽게 이동 (보간 방식)
	float smoothFactor = 8.0f; // 클수록 빠르게 목표로 접근
	CharacterData.CharacterPos.x += (targetPosition.x - CharacterData.CharacterPos.x) * smoothFactor * dt;
	CharacterData.CharacterPos.y += (targetPosition.y - CharacterData.CharacterPos.y) * smoothFactor * dt;
}