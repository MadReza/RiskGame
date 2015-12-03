#include "Screen.h"

namespace risk
{
	void changeCursorPosition(COORD coordinates)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, coordinates);
	}

	void cls(COORD coordScreen, SHORT length, SHORT height)
	{		
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


		// Get the number of character cells in the current buffer. 

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return;
		}

		dwConSize = length * height;

		// Fill the entire screen with blanks.

		if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
			(TCHAR) ' ',     // Character to write to the buffer
			dwConSize,       // Number of cells to write 
			coordScreen,     // Coordinates of first cell 
			&cCharsWritten))// Receive number of characters written
		{
			return;
		}

		// Get the current text attribute.

		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return;
		}

		// Set the buffer's attributes accordingly.

		if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
			csbi.wAttributes, // Character attributes to use
			dwConSize,        // Number of cells to set attribute 
			coordScreen,      // Coordinates of first cell 
			&cCharsWritten)) // Receive number of characters written
		{
			return;
		}

		// Put the cursor at its home coordinates.

		SetConsoleCursorPosition(hConsole, coordScreen);
	}

	void cls()
	{
		COORD coordScreen = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		// Get the number of character cells in the current buffer. 
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			//TODO: ADD ERROR HERE
			return;
		}

		cls(coordScreen, csbi.dwSize.X, csbi.dwSize.Y);
	}

	void clsObserver()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		// Get the number of character cells in the current buffer. 
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			//TODO: ADD ERROR HERE
			return;
		}
		cls(COORD_INI_OBSERVER_SCREEN, csbi.dwSize.X, OBS_SCREEN_HEIGHT);
	}

	void clsGame()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		// Get the number of character cells in the current buffer. 
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			//TODO: ADD ERROR HERE
			return;
		}
		cls(COORD_INI_GAME_SCREEN, csbi.dwSize.X, csbi.dwSize.Y);
	}
}