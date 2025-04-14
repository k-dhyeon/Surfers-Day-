#pragma once
#include <stdbool.h>

extern bool bIsForwardPressed;
extern bool bIsBackwardPressed;
extern bool bIsLeftPressed;
extern bool bIsRightPressed;
void UpdateKeyInput();

void CheckCollision();

bool CheckForwardLaneCollision();
bool CheckBackwardLaneCollision();
bool CheckLeftLaneCollision();
bool CheckRightLaneCollision();

void UpdateCharacterPosition();