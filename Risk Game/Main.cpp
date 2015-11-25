#include "GameDriver.h"
#include "GUI.h"
#include <thread>

using std::thread;

int main()
{
	Gui myGui;
	GameDriver *myRiskGame = GameDriver::getInstance();	//Lazy Loading the Game

	thread gameThread = myRiskGame->startGameThread();

	myGui.start();

	gameThread.join();

	system("pause");
	return 0;
}