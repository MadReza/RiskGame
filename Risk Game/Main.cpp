#include "GameManager.h"
#include "MainMenu.h"
#include "GameDriver.h"
#include "BattleEngine\CardUtilities.h"
#include <windows.h>

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


	//http://stackoverflow.com/a/20725888
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY |
		BACKGROUND_BLUE
		);
	/*cout << "TESTING COLORS !" << endl;
	system("pause");
Select the country number 
	system("Color 1A");
	CardUtilities::print(Artillery);
	system("pause");
	system("cls");
	system("Color 2B");
	CardUtilities::print(Cavalry);
	system("pause");
	system("cls"); 
	system("Color 3C");
	CardUtilities::print(Infantry);
	system("Color 3C");

	system("pause");*/

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