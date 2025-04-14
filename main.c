//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright ?2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
//#include "GlobalVariables.h"
//#include "KeyInput.h"
//#include "FlowObstacle.h"
//#include "AssetLib.h"
//#include "FlowBackGround.h"
//#include "stdio.h"
#include "MainMenu.h"








// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(MainMenuInit, MainMenuUpdate, MainMenuExit);
	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	
	return 0;
}
