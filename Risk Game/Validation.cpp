#include "Validation.h"

namespace std
{
	/*
	HOWTO:

	int answer 
	while(!std::vInteger(anwer, lower, upper)){
		cout << "Error message here > ";
	}

	*/
	bool vInteger(int& integer, const int& lower, const int& upper)
	{
		integer = 0;
		std::cin >> integer;
		if (!std::cin >> integer || integer < lower || integer > upper){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		return true;
	}

	bool vY_N(char &answer)
	{
		if (answer == 'y' || answer == 'n' || answer == 'Y' || answer == 'N')
			return true;
		return false;
	}
}