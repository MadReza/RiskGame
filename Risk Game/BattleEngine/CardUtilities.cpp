#include "CardUtilities.h"

const char* CardUtilities::cardTypes[] = { "Infantry", "Artillery", "Cavalry" };

bool CardUtilities::checkRedemption(Player *p)
{
	int infantry_count=0, artillery_count=0, cavalry_count=0;

	if (p->getCards()->size() >= MAX_REDEMPTION_HAND_SIZE)
	{
		return true;
	}

	getTotalOfEachCard(p, infantry_count, artillery_count, cavalry_count);

	//if there is 3 of a kind of any suit return true
	if (infantry_count >= 3 || artillery_count >= 3 || cavalry_count >= 3)
	{
		return true;
	}

	//if there is at least one of each suit return true
	if (infantry_count >= 1 && artillery_count >= 1 && cavalry_count >= 1)
	{
		return true;
	}
	
	return false;	
}

void CardUtilities::getTotalOfEachCard(Player *p, int &infantry, int &artillery, int &cavalry)
{
	for (int i = 0; i != p->getCards()->size(); i++)
	{
		switch ((*p->getCards())[i]->getCardSuit())
		{
		case Infantry:
			infantry++;
			break;
		case Artillery:
			artillery++;
			break;
		case Cavalry:
			cavalry++;
			break;
		default:
			//TODO error if other types...
			break;
		}
	}
}

bool CardUtilities::mandatoryRedemption(Player * p)
{
	if (p->getCards()->size() >= MAX_REDEMPTION_HAND_SIZE)
	{
		return true;
	}	
	return false;
}

int CardUtilities::selectRedemption(Player * p)
{
	int infantry_count=0, artillery_count=0, cavalry_count=0;

	getTotalOfEachCard(p, infantry_count, artillery_count, cavalry_count);

	char selection;
	do
	{
		cout << "The following redemptions are possible: " << endl;
		if (infantry_count >= 3)
		{
			cout << "\tEnter 'i'. Redeem three " << CardUtilities::cardTypes[Infantry] << " cards." << endl;
		}
		if (cavalry_count >= 3)
		{
			cout << "\tEnter 'c'. Redeem three " << CardUtilities::cardTypes[Cavalry] << " cards." << endl;
		}
		if (artillery_count >= 3)
		{
			cout << "\tEnter 'a'. Redeem three " << CardUtilities::cardTypes[Artillery] << " cards." << endl;
		}
		if (artillery_count >= 1 && cavalry_count >= 1 && infantry_count >= 1)
		{
			cout << "\tEnter 'd'. Redeem three DIFFERENTLY suited cards (1 " << CardUtilities::cardTypes[Infantry] << ", 1 " << CardUtilities::cardTypes[Artillery] << ", 1" << CardUtilities::cardTypes[Cavalry] << ")." << endl;
		}
		cout << "\tEnter 'q' to quit redemption" << endl;

		cout << "Please enter your selection from the above choices: ";
		cin >> selection;	//VALIDATION DONE, BELOW

	} while (selection != 'i' && selection != 'c' && selection != 'a' && selection != 'd' && selection != 'q');

	switch (selection)
	{
	case 'q':
		cout << "Exiting card redemption..." << endl;
		return 0;
	case 'c':
		removeThreeSimilar(p, Cavalry);
		break;
	case 'a':
		removeThreeSimilar(p, Artillery);
		break;
	case 'd':
		removeThreeDiff(p);
		break;
	case 'i':
		removeThreeSimilar(p, Infantry);
		break;
	default:
		//TODO unknown case found..
		break;
	}

	p->incrementCardRedemptionsTotal();
	return getRedemptionReinforcements(p);	
}

void CardUtilities::displayPlayerCards(Player * p)
{
	int infantry = 0, artillery = 0, cavalry = 0;

	getTotalOfEachCard(p, infantry, artillery, cavalry);
	
	cout << "Player: " << p->getName() << ", has the following card count: " << endl;;	//TODO DRAW CARDS AND MOVE IT TO THE OBSERVER VIEW

	//TODO Maybe Align numbers check battlenegine output
	cout << "\t" << CardUtilities::cardTypes[Cavalry] << ": " << cavalry << endl;
	cout << "\t" << CardUtilities::cardTypes[Infantry] << ":" << infantry << endl;
	cout << "\t" << CardUtilities::cardTypes[Artillery] << ": " << artillery << endl;
	
}

void CardUtilities::takePlayerCards(Player * loser, Player * winner)
{
	while (loser->getCards()->size() != 0)
	{
		winner->getCards()->push_back(loser->getCards()->back());
		loser->getCards()->pop_back();
	}

	cout << "All of Player: " << loser->getName() << "'s cards have been moved to "	<< winner->getName() << "'s hand." << endl;
}

void CardUtilities::getVictoryCard(Player * p)
{
	p->getCards()->push_back(new Card());
}

/*This return sequence is according to official Hasbro Risk rules
from: http://www.hasbro.com/common/instruct/risk.pdf*/
int CardUtilities::getRedemptionReinforcements(Player * p)
{
	if (p->getRedeemThisTurn())
	{
		return 2;
	}
	int num = p->getCardRedemptionsTotal();
	p->setRedeemThisTurn(true);

	switch (num)
	{
	case 0:
		return 0;
	case 1:
		return 4;
	case 2:
		return 6;
	case 3:
		return 8;
	case 4:
		return 10;
	case 5:
		return 12;
	case 6:
		return 16;
	default:
		break;
	}

	if (num > 6)
	{
		return (15 + ((num - 6) * 5));
	}
}

void CardUtilities::removeThreeSimilar(Player * p, CardType s)
{
	int counter = 3;
	do
	{
		deleteSuit(p, s);
		counter--;

	} while (counter > 0);
}

void CardUtilities::removeThreeDiff(Player * p)
{
	deleteSuit(p,Infantry);
	deleteSuit(p, Artillery);
	deleteSuit(p, Cavalry);
}

CardUtilities::~CardUtilities()
{

}

void CardUtilities::deleteSuit(Player *p, CardType suit)
{
	for (int i = 0; i != p->getCards()->size(); i++)
	{
		if ((*p->getCards())[i]->getCardSuit() == suit)
		{
			p->getCards()->erase(p->getCards()->begin() + i);
			return;
		}
	}

}

void CardUtilities::print(CardType card)
{
	switch (card)
	{
	case Infantry:
		printInfantry();
		break;
	case Artillery:
		printArtillery();
		break;
	case Cavalry:
		printCavalry();
		break;
	default:
		//TODO ERROR NOT IMPLEMENTED HERE
		break;
	}
}

void CardUtilities::printInfantry()
{	  
	cout << "+===============+" << endl;
	cout << "| ************* |" << endl;
	cout << "| ************* |" << endl;
	cout << "| *...........* |" << endl;
	cout << "| *..INFANTRY.* |" << endl;
	cout << "| *...........* |" << endl;
	cout << "| ************* |" << endl;
	cout << "| ************* |" << endl;
	cout << "+===============+" << endl;
}	  
void CardUtilities::printArtillery()
{
	    cout << "+===============+" << endl;
		cout << "| ************* |" << endl;
		cout << "| ************* |" << endl;
		cout << "| *...........* |" << endl;
		cout << "| *.ARTILLERY.* |" << endl;
		cout << "| *...........* |" << endl;
		cout << "| ************* |" << endl;
		cout << "| ************* |" << endl;
		cout << "+===============+" << endl;
}
void CardUtilities::printCavalry()
{
	    cout<<"+===============+"<< endl;
		cout<<"| ************* |"<< endl;
		cout<<"| ************* |"<< endl;
		cout<<"| *...........* |"<< endl;
		cout<<"| *..CAVALRY..* |"<< endl;
		cout<<"| *...........* |"<< endl;
		cout<<"| ************* |"<< endl;
		cout<<"| ************* |"<< endl;
		cout<<"+===============+"<< endl;
}

void CardUtilities::printBlank()
{
	    cout<<"+=============+"<<endl;
		cout<<"|/\\/\\/\\/\\/\\/\\/|"<<endl;
		cout<<"|\\/\\/\\/\\/\\/\\/\\|"<<endl;
		cout<<"|/\\/\\/\\/\\/\\/\\/|"<<endl;
		cout<<"|==RISK 345===|"<<endl;
		cout<<"|\\/\\/\\/\\/\\/\\/\\|"<<endl;
		cout<<"|/\\/\\/\\/\\/\\/\\/|"<<endl;
		cout<<"|\\/\\/\\/\\/\\/\\/\\|"<<endl;
		cout<<"+=============+"<<endl;
}
