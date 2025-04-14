#include "cprocessing.h"
//#include "GlobalVariables.h"
//#include "KeyInput.h"
//#include "FlowObstacle.h"
//#include "AssetLib.h"
//#include "FlowBackGround.h"
//#include "stdio.h"
#include "MainMenu.h"





<<<<<<< HEAD

=======
void update()
{
    // If this is the first frame the left mouse button is pressed
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT))
    {
        CP_Graphics_ClearBackground(CP_Color_Create(255, 192, 203, 255));
    }
    // If left mouse button is being held
    else if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
    {
        CP_Graphics_ClearBackground(CP_Color_Create(25, 180, 220, 255));
    }
    // If left mouse button was just released
    else if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
    {
        CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 0, 255));
    }
    // Default state
    else
    {
        CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    }
}
// use CP_Engine_SetNextGameState to specify this function as the initialization function
// this function will be called once at the beginning of the program
void game_init(void)
{
	// initialize variables and CProcessing settings for this gamestate
}

// use CP_Engine_SetNextGameState to specify this function as the update function
// this function will be called repeatedly every frame
void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255,255));
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, 300.0f, 50.0f); // x,y  width, height
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() / 2.0f, (CP_System_GetWindowHeight() / 2.0f)- 80.0f, 300.0f, 50.0f); // x,y  width, height
    update();
}
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b


// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
<<<<<<< HEAD
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);
=======
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_System_SetWindowSize(1600, 900);
>>>>>>> 5572481c88055a1c8e5d86f563ca4e2e6c8a208b
	CP_Engine_Run();
	
	return 0;
}
