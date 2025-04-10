#pragma once
#include <stdbool.h>

bool bIsForwardPressed = false;
bool bIsBackwardPressed = false;
bool bIsLeftPressed = false;
bool bIsRightPressed = false;
void UpdateKeyInput();

void CheckCollision();

