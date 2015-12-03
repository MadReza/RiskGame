#include "BattleEngine.h"
		
bool BattleEngine::attack(Country *attackerCountry, Country *defenderCountry) {
	int* attackerRollsList = nullptr;
	int* defenderRollsList = nullptr;
	Player *attackerPlayer = attackerCountry->getOwner();
	Player *defenderPlayer = defenderCountry->getOwner();
	bool countryConquered = false;

	int	attackerNumRoll, defenderNumRoll;
	bool allInMode = false;
	
	system("cls");
	cout << "\n\t*****Attacking*****\n\n";
		
	displayBattleInfo(attackerPlayer, defenderPlayer, attackerCountry, defenderCountry);
		
	allInMode = isAllInMode(attackerPlayer);

	if (allInMode){
		goto allIn;
	}

playerAttack:
	attackerNumRoll = attackerRoll(attackerPlayer, defenderPlayer, attackerCountry, defenderCountry);
	if (attackerNumRoll == 0) //User Cancelled
		goto stop;
	goto skipAllIn;

allIn:

	attackerNumRoll = attackerCountry->getNumArmies() > 2 ? 3 : 2;

skipAllIn:
	defenderNumRoll = defenderCountry->getNumArmies() > 1 ? 2 : 1;

	//Creating the arrays that will contains the rolls list
	attackerRollsList = generateDescSortedRollList(attackerNumRoll);
	defenderRollsList = generateDescSortedRollList(defenderNumRoll);

	
	
	compareRolls(attackerCountry, defenderCountry,attackerRollsList, defenderRollsList, attackerNumRoll, defenderNumRoll);

	system("cls");
	cout << "\n\t*****RESULT*****\n\n";
	displayBattleInfo(attackerPlayer, defenderPlayer, attackerCountry, defenderCountry);
	cout << endl;

	//displaying attacker rolls
	cout << " Attackers rolls :" << endl;
	for (int i = 0; i < attackerNumRoll; i++)
		cout << attackerRollsList[i] << ", "; //TODO PRETTY THIS
	//displaying Defender rolls
	cout << "\n Defender rolls :" << endl;
	for (int i = 0; i < defenderNumRoll; i++)
		cout << defenderRollsList[i] << ", "; //TODO PRETTY THIS

	cout << endl; 

	int num_ArmiesToSend;

	//Defender Lost
	if (defenderLost(attackerCountry, defenderCountry, attackerCountry->getNumArmies(), defenderCountry->getNumArmies())){
		//Display
		displayDefenderLost();
		cout << endl;
		cout << "Defender lost his country" << endl;
		cout << attackerPlayer->getName() << " now owns " << defenderCountry->getName() << endl;

		//Process
		attackerPlayer->setTurnVictory(true);
		attackerPlayer->setBattlesWonTotal(attackerPlayer->getBattlesWonTotal() + 1);
		num_ArmiesToSend = numberOfArmiesToSend(attackerPlayer, attackerNumRoll, attackerCountry->getNumArmies());
		defenderCountry->setOwner(attackerPlayer);
		//Move Army from country to new country
		attackerCountry->addArmies(-num_ArmiesToSend);
		defenderCountry->addArmies(num_ArmiesToSend);

		cout << attackerPlayer->getName() << " sent " << num_ArmiesToSend << " to " << defenderCountry->getName() << endl;
		system("pause");
		
		countryConquered = true;
		goto stop;
	}

	//Attacker Lost
	if (attackerLost(attackerCountry, defenderCountry, attackerCountry->getNumArmies(), defenderCountry->getNumArmies())){	//TODO reformating: doesn't need to pass NumArmies
		
		displayAttackerLost();
		cout << endl;
		cout << "\n\t\tAttacker ran out of armies\n";
		defenderPlayer->setBattlesWonTotal(defenderPlayer->getBattlesWonTotal() + 1);//Add 1 to the number of Battle won
		goto stop;
	}

	//Loop back if allin
	if (allInMode){
		system("pause");
		goto allIn;
	}
	else{
		if (isContinue() && (attackerCountry->getOwner()->getType() == Player::Human))
			goto playerAttack;
	}

	//Attack phase is over
stop:

 	//Clean
	if (attackerRollsList != nullptr)
		delete[]attackerRollsList;//Deallocate memory
	if (defenderRollsList != nullptr)
		delete[]defenderRollsList;//Deallocate memory
	return countryConquered;
}

int* BattleEngine::generateDescSortedRollList(int size){
	int* rollList = new int[size];

	for (int i = 0; i < size; i++){
		rollList[i] = roll();
	}

	//Sort Descending
	sort(rollList, rollList + size, greater<int>());

	return rollList;
}

int BattleEngine::roll(int min, int max){
	
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 1000);
	return (distribution(generator) % max)+min;
	//return rand() % max + min;
}

//Check if the attack is over. (Attack Phase is over when there's is no defending armies or attacker contains only 1 army).
bool BattleEngine::isAttackOver(int attackerNum_armies, int defenderNum_armies){
	if (defenderNum_armies < 1 || attackerNum_armies <= 1)
		return true;
	else
		return false;
}

bool BattleEngine::defenderLost(Country* attackerCountry, Country *defenderCountry, int attackerNum_armies, int defenderNum_armies)
{
	if (isAttackOver(attackerCountry->getNumArmies(), defenderCountry->getNumArmies()) && defenderCountry->getNumArmies() < 1)
		return true;
	return false;
}

bool BattleEngine::attackerLost(Country* attackerCountry, Country *defenderCountry, int attackerNum_armies, int defenderNum_armies)
{
	if (isAttackOver(attackerCountry->getNumArmies(), defenderCountry->getNumArmies()) && attackerCountry->getNumArmies() <= 1)
		return true;
	return false;
}

//isContinue Function check whether the user wants to keep attacking or not.
bool BattleEngine::isContinue(){

	char choice;
	do{
		cout << "\nDo you wish to launch another attack ? y/n : ";
		cin >> choice;
	} while (choice != 'y' && choice == 'Y' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y')
		return true;
	return false;
}

/* All in Function uses the maximum number of dice on both sides and runs automatically until the attack results in either 
	a) the defending country to be conquered and all armies of the conquering country are moved to the conquered country
or  b) the attacking country runs out of armies and cannot attack anymore */
bool BattleEngine::isAllInMode(Player *attackerPlayer){

	//Attacker is a computer player no need to ask anything 
	if (!attackerPlayer->isHuman(*attackerPlayer))
		return true;

	//Attacker is Human
	char choice;
	do{
		cout << "\nDo you wish to go All in ? y/n: ";
		cin >> choice;	
	} while (choice != 'y' && choice != 'n');

	system("cls");

	if (choice == 'y')
		return true;
	return false;
}

/*This function makes the attacking player place a number of armies in the conquered country which is greater or equal than the number of
dice that was used in the attack that resulted in conquering the country*/
int BattleEngine::numberOfArmiesToSend(Player* attackerPlayer, int numberOfRolls, int attackerNumArmies){
	int numArmtoSend, minimumTransArmy;
	minimumTransArmy = numberOfRolls >= attackerNumArmies ? attackerNumArmies - 1 : numberOfRolls;

	//Attacker Player is a computer? then randomize the # of armies to be send (
	if (!attackerPlayer->isHuman(*attackerPlayer)) {
		numArmtoSend = roll(minimumTransArmy, attackerNumArmies - minimumTransArmy); //return random number between (min trans armies and max armies -1)			
		cout << "\n" << attackerPlayer->getName() << " returned " << numArmtoSend << " Army(ies)\n" << endl;	//TODO check formatting Kendy, Sentence restructure
		return numArmtoSend;
	}
	else{
		//Attacker Player is Human
		do{
			cout << endl;
			cout << "How many armies do you wish to send to your new country (" << minimumTransArmy << " to " << attackerNumArmies - 1 << "): ";
			/*cin >> numArmtoSend;*/
		} while (!std::validInteger(numArmtoSend, minimumTransArmy, attackerNumArmies - 1)/*numArmtoSend < minimumTransArmy || numArmtoSend >= attackerNumArmies*/);
		return numArmtoSend;
	}
}

int BattleEngine::attackerRoll(Player* attackerPlayer, Player* defenderPlayer, Country *attackerCountry, Country *defenderCountry)
{
	start:
	//Determine the # of armies the attacker will send
	int sentArmies; 
	system("cls");
	displayBattleInfo(attackerPlayer, defenderPlayer, attackerCountry, defenderCountry);
	cout << attackerPlayer->getName() << " : How many armies do you wish to send to attack?";
	cout << "(Not more than " << attackerCountry->getNumArmies() - 1 << ") and 0 to cancel current attack: " << endl;

	/*cin >> sentArmies; INFO: validInteger Takes Care*/ 

	//if Users input an invalid number return to start 
	if (!std::validInteger(sentArmies, 0, attackerCountry->getNumArmies() - 1)/*sentArmies > attackerCountry->getNumArmies() - 1 || sentArmies < 0*/)
		goto start;

	//Will determine how many rolls the Attacker have (3,2 or 1)
	if (sentArmies >= 3)
		return 3;
	return sentArmies;	//return 2 or 1 or 0 to cancel
}

//loop and verify the attacker and defender corresponding dices
void BattleEngine::compareRolls(Country *attackerCountry, Country* defenderCountry, int* attackerRollsList, int* defenderRollsList, int attackerNumRoll, int defenderNumRoll)
{
	//Will return the minimum number of roll that we will compare (3,2 or 1)
	int minNumOfRolls = std::min(attackerNumRoll, defenderNumRoll);

	for (int i = 0; i < minNumOfRolls; i++){
		if (attackerRollsList[i] > defenderRollsList[i]){
			defenderCountry->addArmies(-1);//Defender lose
			if (defenderCountry->getNumArmies() == 0) //Make sure the defender # of armies don't go below 0
				break;
		}
		else{
			if (attackerCountry->getNumArmies() <= 1) //Make sure the attacker # of armies don't go below 1
				break;
			attackerCountry->addArmies(-1); //Attacker lose
		}
	}
}

//Will display the Battle Information before the attack
void BattleEngine::displayBattleInfo(Player* attackerPlayer, Player* defenderPlayer, Country* attackerCountry, Country* defenderCountry){

	cout << setfill(' ') << setw(29) << "Attacker" << setfill(' ') << setw(19) << "Defender" << endl;
	cout << " " << setfill('#') << setw(54) << "";
	cout << endl;
	//Name Output
	cout << "#" << setfill(' ') << setw(12) << "Player:  ";
	cout << "#" << setfill(' ') << setw(13) << attackerPlayer->getName() << setfill(' ') << setw(8);
	cout << "#" << setfill(' ') << setw(13) << defenderPlayer->getName() << setfill(' ') << setw(8) << "#" << endl;

	//Type Output
	string attackerType = attackerPlayer->getType() == 0 ? "Human" : "Computer";
	string defenderType = defenderCountry->getOwner()->getType() == 0 ? "Human" : "Computer";
	cout << "#" << setfill(' ') << setw(12) << "Type:  ";
	cout << "#" << setfill(' ') << setw(13) << attackerType << setfill(' ') << setw(8);
	cout << "#" << setfill(' ') << setw(13) << defenderType << setfill(' ') << setw(8) << "#" << endl;

	//Country Name output
	cout << "#" << setfill(' ') << setw(12) << "Country:  ";
	cout << "#" << setfill(' ') << setw(13) << attackerCountry->getName() << setfill(' ') << setw(8);
	cout << "#" << setfill(' ') << setw(13) << defenderCountry->getName() << setfill(' ') << setw(8) << "#" << endl;

	//Army output
	cout << "#" << setfill(' ') << setw(12) << "Armies:  ";
	cout << "#" << setfill(' ') << setw(13) << attackerCountry->getNumArmies() << setfill(' ') << setw(8);
	cout << "#" << setfill(' ') << setw(13) << defenderCountry->getNumArmies() << setfill(' ') << setw(8) << "#" << endl;

	cout << " " << setfill('#') << setw(54) << "";
	cout << endl;
}

void BattleEngine::displayDefenderLost()
{
	system("pause");
	system("cls");
	cout << "______ ___________ _____ _   _______ ___________   _     _____ _____ _____ " << endl;
	cout << "|  _  \\  ___|  ___|  ___| \\ | |  _  \\  ___| ___ \\ | |   |  _  /  ___|_   _|" << endl;
	cout << "| | | | |__ | |_  | |__ |  \\| | | | | |__ | |_/ / | |   | | | \\ `--.  | |  " << endl;
	cout << "| | | |  __||  _| |  __|| . ` | | | |  __||    /  | |   | | | |`--. \\ | |  " << endl;
	cout << "| |/ /| |___| |   | |___| |\\  | |/ /| |___| |\\ \\  | |___\\ \\_/ /\\__/ / | |  " << endl;
	cout << "|___/ \\____/\\_|   \\____/\\_| \\_/___/ \\____/\\_| \\_| \\_____/\\___/\\____/  \\_/  " << endl;
}

void BattleEngine::displayAttackerLost()
{
	system("pause");
	system("cls");
	cout << "  ___ _____ _____ ___  _____  _   __ ___________   _     _____ _____ _____ " << endl;
	cout << " / _ \\_   _|_   _/ _ \\/  __ \\| | / /|  ___| ___ \\ | |   |  _  /  ___|_   _|" << endl;
	cout << "/ /_\\ \\| |   | |/ /_\\ \\ /  \\/| |/ / | |__ | |_/ / | |   | | | \\ `--.  | |  " << endl;
	cout << "|  _  || |   | ||  _  | |    |    \\ |  __||    /  | |   | | | |`--. \\ | |  " << endl;
	cout << "| | | || |   | || | | | \\__/\\| |\\  \\| |___| |\\ \\  | |___\\ \\_/ /\\__/ / | |  " << endl;
	cout << "\\_| |_/\\_/   \\_/\\_| |_/\\____/\\_| \\_/\\____/\\_| \\_| \\_____/\\___/\\____/  \\_/  " << endl;
}