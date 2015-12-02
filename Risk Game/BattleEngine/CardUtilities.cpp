#include "CardUtilities.h"

bool CardUtilities::checkRedemption(Player * p)
{
	int infantry_count=0, artillery_count=0, cavalry_count=0;

	if (p->getCards().size() >= 5)
	{
		return true;
	}

	for (int i = 0; i != p->getCards().size(); i++)
	{
		if (p->getCards()[i]->getCardSuit() == "INFANTRY")
		{
			infantry_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "ARTILLERY")
		{
			artillery_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "CAVALRY")
		{
			cavalry_count++;
		}
	}

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

bool CardUtilities::mandatoryRedemption(Player * p)
{
	if (p->getCards().size() >= MAX_REDEMPTION_HAND_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CardUtilities::selectRedemption(Player * p)
{
	int infantry_count=0, artillery_count=0, cavalry_count=0;

	for (int i=0; i != p->getCards().size(); i++)
	{		
		if (p->getCards()[i]->getCardSuit() == "INFANTRY")
		{
			infantry_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "ARTILLERY")
		{
			artillery_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "CAVALRY")
		{
			cavalry_count++;
		}
	}

	char selection;
	do
	{
		cout << "The following redemptions are possible: " << endl;
		if (infantry_count >= 3)
		{
			cout << "\tEnter 'i'. Redeem three INFANTRY cards." << endl;
		}
		if (cavalry_count >= 3)
		{
			cout << "\tEnter 'c'. Redeem three CAVALRY cards." << endl;
		}
		if (artillery_count >= 3)
		{
			cout << "\tEnter 'a'. Redeem three ARTILLERY cards." << endl;
		}
		if (artillery_count >= 1 && cavalry_count >= 1 && infantry_count >= 1)
		{
			cout << "\tEnter 'd'. Redeem three DIFFERENTLY suited cards (1 INFANTRY, 1 ARTILLERY, 1 CAVALRY)." << endl;
		}
		cout << "\tEnter 'q' to quit redemption" << endl;

		cout << "Please enter your selection from the above choices: ";
		cin >> selection;	//TODO VALIDATION
	} while (selection != 'i' && selection != 'c' && selection != 'a' && selection != 'd' && selection != 'q');

	if (selection == 'q')
	{
		cout << "Exiting card redemption..." << endl;
		return 0;
	}	
	else if (selection == 'c')
	{
		removeThreeSimilar(p, "CAVALRY");
	}
	else if (selection == 'a')
	{
		removeThreeSimilar(p, "ARTILLERY");
	}
	else if (selection == 'd')
	{
		removeThreeDiff(p);
	}
	else if (selection == 'i')
	{
		removeThreeSimilar(p, "INFANTRY");
	}

	p->incrementCardRedemptionsTotal();
	return getRedemptionReinforcements(p);	
}

void CardUtilities::displayPlayerCards(Player * p)
{
	cout << "Player: " << p->getName()
		<< ", has the following card hand sequence: ";
	
	for (int i = 0; i != p->getCards().size(); i++)
	{
		cout << p->getCards()[i]->getCardSuit() << ", ";
	}

	//TODO: Add Emptry Drawing....

	cout << endl;
}

void CardUtilities::takePlayerCards(Player * loser, Player * winner)
{
	while (loser->getCards().size() != 0)
	{
		winner->getCards().push_back(loser->getCards().back());
		loser->getCards().pop_back();
	}

	cout << "All of Player: " << loser->getName() << "'s cards have been moved to "
		<< winner->getName() << "'s hand." << endl;
}

void CardUtilities::getVictoryCard(Player * p)
{
	p->getCards().push_back(new Card());
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

void CardUtilities::removeThreeSimilar(Player * p, string s)
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
	deleteSuit(p,"INFANTRY");
	deleteSuit(p, "ARTILLERY");
	deleteSuit(p, "CAVALRY");
}

CardUtilities::~CardUtilities()
{

}

void CardUtilities::deleteSuit(Player *p, string suit)
{
	for (int i = 0; i != p->getCards().size(); i++)
	{
		if (p->getCards()[i]->getCardSuit() == suit)
		{
			p->getCards().erase(p->getCards().begin() + i);
			return;
		}
	}

}
