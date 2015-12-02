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

void CardUtilities::selectRedemption(Player * p)
{
	int infantry_count=0, artillery_count=0, cavalry_count=0;
	bool tripinf = false, tripcav = false, tripart = false, threedif = false;

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

	cout << "The following redemptions are possible: " << endl;
	if (infantry_count >= 3)
	{
		cout << "Enter 'i'. Redeem three INFANTRY cards." << endl;
	}
	if (cavalry_count >= 3)
	{
		cout << "Enter 'c'. Redeem three CAVALRY cards." << endl;
	}
	if (artillery_count >= 3)
	{
		cout << "Enter 'a'. Redeem three ARTILLERY cards." << endl;
	}
	if (artillery_count >= 1 && cavalry_count >= 1 && infantry_count >=1 )
	{
		cout << "Enter 'd'. Redeem three DIFFERENTLY suited cards (1 INFANTRY, 1 ARTILLERY, 1 CAVALRY)." << endl;
	}
	cout << "Enter 'q' to quit redemption" << endl;

	char selection;
	cout << "Please enter your selection from the above choices" << endl;
	cin >> selection;

	if (selection == 'i')
	{
		removeThreeSimilar(p, "INFANTRY"); 
		p->incrementCardRedemptionsTotal();
	}
	else if (selection == 'c')
	{
		removeThreeSimilar(p, "CAVALRY");
		p->incrementCardRedemptionsTotal();
	}
	else if (selection == 'a')
	{
		removeThreeSimilar(p, "ARTILLERY");
		p->incrementCardRedemptionsTotal();
	}
	else if (selection == 'd')
	{
		removeThreeDiff(p);
		p->incrementCardRedemptionsTotal();
	}
	else if (selection == 'q')
	{
		cout << "Exiting card redemption..." << endl;
	}

}

void CardUtilities::displayPlayerCards(Player * p)
{
	cout << "Player: " << p->getName()
		<< ", has the following card hand sequence: ";
	
	for (int i = 0; i != p->getCards().size(); i++)
	{
		cout << p->getCards()[i]->getCardSuit() << ", ";
	}

	cout << endl;
}

void CardUtilities::takePlayerCards(Player * a, Player * b)
{
	while (a->getCards().size() != 0)
	{
		b->getCards().push_back(a->getCards().back());
		a->getCards().pop_back();
	}

	cout << "All of Player: " << a->getName() << "'s cards have been moved to "
		<< b->getName() << "'s hand." << endl;
}

void CardUtilities::getVictoryCard(Player * p)
{
	p->getCards().push_back(new Card());
}
/*This return sequence is according to official Hasbro Risk rules
from: http://www.hasbro.com/common/instruct/risk.pdf*/
int CardUtilities::getRedemptionReinforcements(Player * p)
{
	int num = p->getCardRedemptionsTotal();

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

	return 0;
}

void CardUtilities::removeThreeSimilar(Player * p, string s)
{
	int counter = 3;
	do
	{
		for (int i = 0; i != p->getCards().size(); i++)
		{
			if (p->getCards()[i]->getCardSuit() == s)
			{
				//TODO
				//p->getCards()
					counter--;
			}
		}

	} while (counter > 0);
}

void CardUtilities::removeThreeDiff(Player * p)
{
}



CardUtilities::~CardUtilities()
{

}
