#ifndef SCREEN_H
#define SCREEN_H

#include <Windows.h>

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
	void changeCursorPosition(COORD coordinates);

	/*Clear a specfici part of the screens */
	void cls(COORD startPosition, SHORT length, SHORT height);
	/*Clear whole console window*/
	void cls();			
	/*Clear Part of the screen dedicated to the Observer */
	void clsObserver();	
	/*Clear Part of the screen dedicated to the Game*/
	void clsGame();
}

#endif //SCREEN_H