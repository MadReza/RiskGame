//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

//Observer Class, based on reused code from ClockObserver in-class sample code
#pragma once
#include "../Observer.h"
#include "Map.h"


class Map_View : public Observer
{
public:
	Map_View();
	Map_View(Map* m);
	~Map_View();
	void Update(); //Updates the Map_view
	void Display(); //Method for outputting the map state to console

private:
	Map *_subject;
};

