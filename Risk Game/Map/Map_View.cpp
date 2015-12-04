#include "Map_View.h"



Map_View::Map_View()
{
}

Map_View::Map_View(Map * m)
{
	_subject = m;
	//_subject->Attach(this);
}


Map_View::~Map_View()
{
	//_subject->Detach(this);
}

void Map_View::Update()
{
	Display();
}

/*The following method just iterates through the various vectors and calls the different accessors 
in a way that is better colated and formatted.*/
void Map_View::Display()
{
	cout << "Map Updated!" << endl;

	for (int i = 0; i != _subject->getMapVector().size(); i++)
	{
		for (int j = 0; j != _subject->getMapVector()[i]->getContinentVector().size(); j++)
		{
			cout << "Country: " << _subject->getMapVector()[i]->getContinentVector()[j]->getName()	
				<< ", Continent: " << _subject->getMapVector()[i]->getContinentVector()[j]->getContinentName()
				<< ", Player Owner: " << _subject->getMapVector()[i]->getContinentVector()[j]->getOwner()->getName()
				<< ", Armies Occupying: " << _subject->getMapVector()[i]->getContinentVector()[j]->getNumArmies() << endl;

			cout << "Adjacent Countries: ";
			_subject->getMapVector()[i]->getContinentVector()[j]->displayAdjacentCountries();
			cout << ". \n" << endl;

		}
	}

}
