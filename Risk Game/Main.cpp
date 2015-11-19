#include "GameDriver.h"


int main()
{
	GameDriver::getInstance();	//Eager Loading so this is useless for now.

	system("pause");
	return 0;
}