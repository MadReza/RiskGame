#include "GameManager.h"
#include "MainMenu.h"
#include "GameDriver.h"

//OLD 
//#include "GameDriver.h"
//#include "GUI.h"
//#include <thread>
//using std::thread;

int main()
{
	/********* GUI VERSION OF GAME ***********/
	//GameManager theGame("The Risk Game");
	//theGame.pushState(new MainMenu(&theGame));	//Starting the Game with the MainMenu.

	//theGame.gameLoop();





	// OLD DEPRECRATED WAY... Keeping for reference for now...
	//Gui myGui;
	GameDriver *myRiskGame = GameDriver::getInstance();	//Lazy Loading the Game
	myRiskGame->startGame();

	//thread gameThread = myRiskGame->startGameThread();

	//myGui.start();

	//gameThread.join();

	system("pause");
	return 0;
}