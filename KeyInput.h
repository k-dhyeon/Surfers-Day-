#pragma once
#include <stdbool.h>
#include "cprocessing.h"

extern bool bIsForwardPressed;
extern bool bIsBackwardPressed;
extern bool bIsLeftPressed;
extern bool bIsRightPressed;

extern CP_Vector targetPosition;

void InitKeyInput();

void UpdateKeyInput();




bool CheckForwardLaneCollision();
bool CheckBackwardLaneCollision();
bool CheckLeftLaneCollision();
bool CheckRightLaneCollision();

void UpdateCharacterPosition();
