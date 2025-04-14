#pragma once
#include <stdbool.h>

<<<<<<< HEAD
extern bool bIsForwardPressed;
extern bool bIsBackwardPressed;
extern bool bIsLeftPressed;
extern bool bIsRightPressed;
=======
bool bIsForwardPressed = false;
bool bIsBackwardPressed = false;
bool bIsLeftPressed = false;
bool bIsRightPressed = false;
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b
void UpdateKeyInput();

void CheckCollision();

<<<<<<< HEAD
bool CheckForwardLaneCollision();
bool CheckBackwardLaneCollision();
bool CheckLeftLaneCollision();
bool CheckRightLaneCollision();

void UpdateCharacterPosition();
=======
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b
