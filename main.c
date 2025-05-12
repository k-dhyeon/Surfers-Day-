#include "cprocessing.h"
//#include "GlobalVariables.h"
//#include "KeyInput.h"
//#include "FlowObstacle.h"
//#include "AssetLib.h"
//#include "FlowBackGround.h"
//#include "stdio.h"
#include "IntroScene.h"







// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(Intro_init, Intro_update, Intro_exit);
	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);

	CP_Engine_Run();
	
	return 0;
}
