#include "CardUtilities.h"

bool CardUtilities::checkRedemption(Player * p)
{
	int infantry_count, artillery_count, cavalry_count;

	if (p->getCards().size() >= 5)
	{
		return true;
	}

	for (int i; i != p->getCards().size(); i++)
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
	vector<string> selection;
	bool badSelection = true;
	bool badRedemption = true;
	bool tripleinf, triplecav, tripleart, threediff;

	while (badRedemption)
	{
		while (badSelection) {
			displayPlayerCards(p);
			string sel1, sel2, sel3;
			cout << "Please enter the first card to redeem : " << endl;
			cin >> sel1;
			cout << "Please enter the second card to redeem : " << endl;
			cin >> sel2;
			cout << "Please enter the third card to redeem : " << endl;
			cin >> sel3;

			selection.push_back(sel1); selection.push_back(sel2); selection.push_back(sel3);

			int infcount = 0, artcount = 0, cavcount = 0;
			for (int i = 0; i < 3; i++)
			{
				if (selection[i] == "INFANTRY")
				{
					infcount++;
				}
				if (selection[i] == "ARTILLERY")
				{
					artcount++;
				}
				if (selection[i] == "CAVALRY")
				{
					cavcount++;
				}
			}

			if (infcount == 3)
			{
				badSelection = false;
				tripleinf = true;
			}
			else if (artcount == 3)
			{
				badSelection = false;
				tripleart = true;
			}
			else if (cavcount == 3)
			{
				badSelection = false;
				triplecav = true;
			}

			else if (infcount == 1 && cavcount == 1 && artcount == 1)
			{
				badSelection = false;
				threediff = true;
			}
			else
			{
				badSelection = true;
				cout << "That is a bad selection of cards please try again" << endl;
				//delete the selection to try again
				for (int i = 0; i < 3; i++)
				{
					selection.pop_back();
				}
			}
		}
		//now test against possible redemption
		int infhandcount = 0, arthandcount = 0, cavhandcount = 0;
		bool tripinfhand=false, triparthand=false, tripcavhand=false, threediffhand=false;
		int counter = 3;
		for (int i = 0; i != p->getCards().size(); i++)
		{
			if (p->getCards()[i]->getCardSuit() == "INFANTRY")
			{
				infhandcount++;
			}
			if (p->getCards()[i]->getCardSuit() == "ARTILLERY")
			{
				arthandcount++;
			}
			if (p->getCards()[i]->getCardSuit() == "CAVALRY")
			{
				cavhandcount++;
			}
		}

		if (infhandcount == 3)
		{
			tripinfhand = true;
		}
		else if (arthandcount == 3)
		{
			triparthand = true;
		}
		else if (cavhandcount == 3)
		{
			tripcavhand = true;
		}
		else if (infhandcount == 1 && cavhandcount == 1 && arthandcount == 1)
		{
			threediffhand = true;
		}

		if (tripinfhand && tripleinf)
		{
			badRedemption = false;
			removeThreeInf(p);
		}
		else if (triparthand && tripleart)
		{
			badRedemption = false;
			removeThreeArt(p);
		}
		else if (tripcavhand && triplecav)
		{
			badRedemption = false;
			removeThreeCav(p);
		}
		else if (threediffhand && threediff)
		{
			badRedemption = false;
			removeThreeDiff(p);
		}
		else
		{
			badRedemption = true;
			cout << "ERROR: That is not a possible redemption!" << endl;
		}
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

void CardUtilities::removeThreeInf(Player * p)
{
}

void CardUtilities::removeThreeArt(Player * p)
{
}

void CardUtilities::removeThreeCav(Player * p)
{
}

void CardUtilities::removeThreeDiff(Player * p)
{
}



CardUtilities::~CardUtilities()
{

}
