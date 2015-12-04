//#include "GameManager.h"
//#include "MainMenu.h"
#include "GameDriver.h"
//#include "BattleEngine\CardUtilities.h"
//#include <windows.h>
#include <iostream>
#include <ctime> //random
//OLD 
//#include "GameDriver.h"
//#include "GUI.h"
//#include <thread>
//using std::thread;
//

#include "Screen.h"

using namespace risk;

int main()
{
	srand(time(0)); //Random Seed
	////Test output to work on.
	//for (int i = 0; i < 60; i++)
	//{
	//	std::cout << "1234567890qwertyuiopasdfghjkl;zxcvbnm,1234567890qwertyuiopasdfghjkl;zxcvbnm,1234567890qwertyuiopasdfghjkl;zxcvbnm,1234567890qwertyuiopasdfghjkl;zxcvbnm," << std::endl;
	//}

	//
	//changeCursorPosition({ 25, 25 });
	//std::cout << "RAWR";

	//system("pause");

	//clsObserver();
	//system("pause");

	//clsGame();
	//system("pause");

	//cls();
	//HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	////Loading/Preparing Risk To be Played
	//std::cout << "Preparing Game for your Enjoyment!" << std::endl;
	////check if the output screen size matches our requirements.
	//CONSOLE_SCREEN_BUFFER_INFO csbi;

	//// Get the number of character cells in the current buffer. 
	//if (!GetConsoleScreenBufferInfo(hStdout, &csbi))
	//{
	//	std::cout << "Console Buffer Error" << std::endl;
	//	system("pause");
	//	return 1;
	//}

	////Check if size match required size of Game!
	//if (csbi.dwSize.X < 200 || csbi.dwSize.Y < 300)
	//{
	//	std::cout << "Sysmte console size is set wrong." << endl;
	//	system("pause");
	//	return 2;
	//}


	//system("pause");
	//return 0;



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


	/********* GUI VERSION OF GAME ***********/
	//GameManager theGame("The Risk Game");
	//theGame.pushState(new MainMenu(&theGame));	//Starting the Game with the MainMenu.

	//theGame.gameLoop();
	/**********END OF GUI ********************/

	//Gui myGui;
	GameDriver *myRiskGame = GameDriver::getInstance();	//Lazy Loading the Game
	myRiskGame->startGame();

	//thread gameThread = myRiskGame->startGameThread();

	//myGui.start();

	//gameThread.join();

	system("pause");
	return 0;
}