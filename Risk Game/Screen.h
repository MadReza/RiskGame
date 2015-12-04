#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>
#include <conio.h>
#include <iostream>

using std::cin;

namespace risk
{
	//Observer screen part
	/*Coordinate where Observer Screen Starts*/
	const COORD COORD_INI_OBSERVER_SCREEN = { 0, 0 };    
	/*Observer Screen Max Height*/
	const SHORT OBS_SCREEN_HEIGHT = 25;

	//GameLogic Part of Screen
	const COORD COORD_INI_GAME_SCREEN = { 0, 27 };    

	/*Change Cursor position */
	void setCursorPosition(COORD coordinates);

	/*Get Current Cursor position*/
	COORD getCursorPosition();

	/*Clear a specfici part of the screens */
	void cls(COORD startPosition, SHORT length, SHORT height);
	/*Clear whole console window*/
	void cls();			
	/*Clear Part of the screen dedicated to the Observer */
	void clsObserver();	
	/*Clear Part of the screen dedicated to the Game*/
	void clsGame();

	/*Wait for Input to continue*/
	void pause();

	/*Make sure the console is set to the correct size */
	bool checkConsoleSize(int width, int height);

	/*For Multiple Observer Part Displaying
	E.g.: Decorator pattern decorating another*/
	extern bool obsDisplaying;
}

#endif //SCREEN_H