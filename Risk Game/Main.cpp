//#include "GameManager.h"
//#include "MainMenu.h"
#include "GameDriver.h"
#include <iostream>
#include "Screen.h"

using namespace risk;

int main()
{
	//Loading/Preparing Risk To be Played
	std::cout << "Preparing Game for your Enjoyment!" << std::endl;
	while (!checkConsoleSize(200, 300))
	{
		std::cout << "Console buffer needs to be set to the following settings: " << std::endl;
		std::cout << "Screen Buffer Size: " << std::endl;
		std::cout << "\tWidth: 200" << std::endl;
		std::cout << "\tHeight: 300" << std::endl;
		std::cout << "Window Size:" << std::endl;
		std::cout << "\tWidth: 200" << std::endl;
		std::cout << "\tHeight: 75" << std::endl;
		system("pause");
	}

	std::cout << "Game prepared! Enjoy!" << endl;
	system("pause");
	cls();

	/************************COLOR PART **********************************/
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
	/*****************************END OF COLOR********************************/

	GameDriver *myRiskGame = GameDriver::getInstance();	//Lazy Loading the Game
	myRiskGame->startGame();


	/********* GUI VERSION OF GAME ***********/
	//GameManager theGame("The Risk Game");
	//theGame.pushState(new MainMenu(&theGame));	//Starting the Game with the MainMenu.

	//theGame.gameLoop();
	/**********END OF GUI ********************/

	system("pause");
	return 0;
}