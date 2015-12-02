#include "BattleEngine.h"
	
BattleEngine::BattleEngine(Country *attacker, Country *defender){
		
	attackerCountry = attacker;
	defenderCountry = defender;

	attackerPlayer = attackerCountry->getOwner();
	defenderPlayer = defenderCountry->getOwner();

	attack();
}

BattleEngine::~BattleEngine(){

}
		
void BattleEngine::attack() {
	 
	srand((unsigned)time(0)); //generate random number based on computer clocks

	int	attackerNumRoll, defenderNumRoll;
	bool allInMode = false;
	
	system("cls");
	cout << "\n\n\t\tAttacking\n\n";
		
	displayBattleInfo(attackerCountry->getNumArmies(), defenderCountry->getNumArmies());

	system("pause");

	//Detect if the Attacker is a computer Player. if it is do Strategy
	if (!attackerPlayer->isHuman(*attackerPlayer)){
		allInMode = true;
		goto allIn;
	}
		
	allInMode = isAllInMode();
	if (allInMode){
		goto allIn;
	}

	//Label if the user choose to send another atttack
	start:

	//Determine the # of armies the attacker will send
	cout << attackerPlayer->getName() << " : How many armies do you wish to send to attack? (Not more than ( " << attackerCountry->getNumArmies() - 1 << " )\n";
	int sentArmies;
	cin >> sentArmies;

	//if Users input an invalid number return to start 
	if (sentArmies > attackerCountry->getNumArmies() - 1 || sentArmies <= 0)
		goto start;

	//Will determine how many rolls the Attacker have (3,2 or 1)
	if (sentArmies >= 3)
		attackerNumRoll = 3;
	else if (sentArmies == 2)
		attackerNumRoll = 2;
	else
		attackerNumRoll = 1;

	//Label if the user choose the all in mode
	allIn:

	//Will determine how many rolls both the defender and the attacker will have.
	if (allInMode)
		attackerCountry->getNumArmies() > 2 ? attackerNumRoll = 3 : attackerNumRoll = 2;

	defenderCountry->getNumArmies() > 1 ? defenderNumRoll = 2 : defenderNumRoll = 1;

	//Creating the arrays that will contains the rolls list
	int* attackerRollsList = new int[attackerNumRoll];
	int* defenderRollsList = new int[defenderNumRoll];

	generateRollList(attackerRollsList, attackerNumRoll);//will generate the attacker rolls
	generateRollList(defenderRollsList, defenderNumRoll);//will generate the defender rolls 

	//This is a method taken from the std libraries. this method will sort arrays in descending orders.
	sort(attackerRollsList, attackerRollsList + attackerNumRoll, greater<int>());
	sort(defenderRollsList, defenderRollsList + defenderNumRoll, greater<int>());

	cout << "\nAttacker # armies : " << attackerCountry->getNumArmies() << "\tDefender # armies : " << defenderCountry->getNumArmies() << endl;
	cout << " Attackers rolls :" << endl;//displaying attacker rolls
	//for loop that iterates through the Arrays and display all its elements
	for (int i = 0; i < attackerNumRoll; i++)
		cout << attackerRollsList[i] << ", ";

	cout << "\n Defender rolls :" << endl;//displaying Defender rolls
	//for loop that iterates through the Arrays and display all its elements
	for (int i = 0; i < defenderNumRoll; i++)
		cout << defenderRollsList[i] << ", ";

	//Will return the minimum number of roll that we will compare (3,2 or 1)
	int minNumOfRolls = std::min(attackerNumRoll, defenderNumRoll);

	//loop and verify the attacker and defender corresponding dices
	for (int i = 0; i < minNumOfRolls; i++){
		if (attackerRollsList[i] > defenderRollsList[i]){
			defenderCountry->addArmies(-1);//Defender lose
			if (defenderCountry->getNumArmies() == 0)//Make sure the defender # of armies don't go below 0
				break;
		}
		else{
			if (attackerCountry->getNumArmies() <= 1)//Make sure the attacker # of armies don't go below 1
				break;
			attackerCountry->addArmies(-1); //Attacker lose
		}
	}

	cout << "\n\nAttacker # armies : " << attackerCountry->getNumArmies() << "\tDefender # armies : " << defenderCountry->getNumArmies() << endl;//Displaying the armies

	int num_ArmiesToSend;

	//Defender armies reach 0
	if (isAttackOver(attackerCountry->getNumArmies(), defenderCountry->getNumArmies()) && defenderCountry->getNumArmies() < 1){
		cout << "\n\t\tDefender lost, Attacker conquered the defending country\n";
		attackerPlayer->setBattlesWonTotal(attackerPlayer->getBattlesWonTotal() + 1);
		num_ArmiesToSend = numberOfArmiesToSend(attackerNumRoll, attackerCountry->getNumArmies());
		defenderCountry->setOwner(attackerPlayer);
		defenderCountry->addArmies(num_ArmiesToSend);
		cout << endl << attackerPlayer->getName() << "sent " << num_ArmiesToSend << "to " << defenderCountry->getName();
		cout << attackerPlayer->getName() << "now owns " << defenderCountry->getName();
		goto stop;
	}

	//Attacker armies reach 1
	if (isAttackOver(attackerCountry->getNumArmies(), defenderCountry->getNumArmies()) && attackerCountry->getNumArmies() <= 1){
		cout << "\n\t\tAttacker ran out of armies\n";
		defenderPlayer->setBattlesWonTotal(defenderPlayer->getBattlesWonTotal() + 1);//Add 1 to the number of Battle won
		goto stop;
	}

	//If user choose all in mode the program will go to allIn label and loop until the attack phase is over.
	if (allInMode){
		if (isAttackOver(attackerCountry->getNumArmies(), defenderCountry->getNumArmies()))
			goto stop;
		goto allIn;
	}
	else{
		//If user choose to attack again. the program will go to the start label.
		if (isContinue() && (attackerCountry->getOwner()->getType() == Player::Human))
			goto start;
	}
	//Attack phase is over
	stop:

	//display Batte Info
	displayBattleInfo(attackerCountry->getNumArmies(), defenderCountry->getNumArmies());
	cout << "\t\t\nTurns end\n\n";

	delete[]attackerRollsList;//Deallocate memory
	delete[]defenderRollsList;//Deallocate memory
}

void BattleEngine::generateRollList(int* emptyArray, int size){
	for (int i = 0; i < size; i++){
		emptyArray[i] = roll();
	}
}

int BattleEngine::roll(int min, int max){
	return rand() % max + min;
}

//Check if the attack is over. (Attack Phase is over when there's is no defending armies or attacker contains only 1 army).
bool BattleEngine::isAttackOver(int attackerNum_armies, int defenderNum_armies){
	if (defenderNum_armies < 1 || attackerNum_armies <= 1)
		return true;
	else
		return false;
}

//isContinue Function check whether the user wants to keep attacking or not.
bool BattleEngine::isContinue(){

	char choice;
	do{
		cout << "\nDo you wish to launch another attack ? y/n : ";
		cin >> choice;

		if (choice == 'y' || choice == 'Y')
			return true;
		else
			return false;
	} while (choice != 'y' && choice != 'n');
}

/* All in Function uses the maximum number of dice on both sides and runs automatically until the attack results in either a) the
defending country to be conquered and all armies of the conquering country are moved to the conquered country
or b) the attacking country runs out of armies and cannot attack anymore */
bool BattleEngine::isAllInMode(){

	//Attacker is a computer player no need to ask anything 
	if (!attackerPlayer->isHuman(*attackerPlayer))
		return true;

	//Attacker is Human
	char choice;
	do{
		cout << "\nDo you wish to go All in ? y/n : ";
		cin >> choice;

		if (choice == 'y')
			return true;
		else
			return false;
	} while (choice != 'y' && choice != 'n');
}

/*This function makes the attackin player place a number of armies in the conquered country which is greater or equal than the number of
dice that was used in the attack that resulted in conquering the country*/
int BattleEngine::numberOfArmiesToSend(int numberOfRolls, int attackerNumArmies){
	int numArmtoSend, minimumTransArmy;
	numberOfRolls >= attackerNumArmies ? minimumTransArmy = attackerNumArmies - 1 : minimumTransArmy = numberOfRolls;

	//Attacker Player is a computer? then randomize the # of armies to be send (
	if (!attackerPlayer->isHuman(*attackerPlayer)) {
		numArmtoSend = (rand() % ((attackerNumArmies)-minimumTransArmy)) + minimumTransArmy; //return random number between (min trans armies and max armies -1)
		cout << "\n" << attackerPlayer->getName() << " returned " << numArmtoSend << " Army(ies)\n" << endl;
		return numArmtoSend;
	}
	else{
		//Attacker Player is Human
		do{
			cout << "\n" << attackerPlayer->getName() << " : How many armies do you wish to send to your new country ? : ";
			cout << " Minimum number of transferable armies : " << minimumTransArmy << "\tMaximum number of transferable armies : " << attackerNumArmies - 1 << endl;
			cin >> numArmtoSend;
			if (numArmtoSend < minimumTransArmy || numArmtoSend >= attackerNumArmies){
				cout << "\nWarning : Minimum number of transferable armies : " << minimumTransArmy << "\nMaximum number of transferable armies : " << attackerNumArmies - 1 << endl;
			}
		} while (numArmtoSend < minimumTransArmy || numArmtoSend >= attackerNumArmies);
		return numArmtoSend;
	}
}

//Will display the Battle Information before the attack
void BattleEngine::displayBattleInfo(int attackerNumOfArmies, int defenderNumOfArmies){

	cout << setfill(' ') << setw(12) << "Attacker" << setfill(' ') << setw(12) << "Defender" << endl;
	cout << "\u2554" << setfill('═') << setw(15) << "╦" << setfill('═') << setw(10) << "╗" << endl;

	//Name Output
	cout << "║" << setfill(' ') << setw(8) << attackerPlayer->getName() << setfill(' ') << setw(8);
	cout << "║" << setfill(' ') << setw(8) << defenderPlayer->getName() << setfill(' ') << setw(8) << "║" << endl;

	//Type Output
	string attackerType = attackerPlayer->getType() == 0 ? "Human" : "Computer";
	string defenderType = defenderCountry->getOwner()->getType() == 0 ? "Human" : "Computer";
	cout << "║" << setfill(' ') << setw(8) << attackerType << setfill(' ') << setw(8);
	cout << "║" << setfill(' ') << setw(8) << defenderType << setfill(' ') << setw(8) << "║" << endl;

	//Country Name output
	cout << "║" << setfill(' ') << setw(8) << attackerCountry->getName() << setfill(' ') << setw(8);
	cout << "║" << setfill(' ') << setw(8) << defenderCountry->getName() << setfill(' ') << setw(8) << "║" << endl;

	//Army output
	cout << "║" << setfill(' ') << setw(8) << attackerCountry->getNumArmies() << setfill(' ') << setw(8);
	cout << "║" << setfill(' ') << setw(8) << defenderCountry->getNumArmies() << setfill(' ') << setw(8) << "║" << endl;

	cout << "╚" << setfill('═') << setw(10) << "╩" << setfill('═') << setw(10) << "╝" << endl;


	cout << endl << endl << endl;



	cout << "Attacker : " << attackerPlayer->getName();
	attackerPlayer->getType() == 0 ? cout << "\tType: Human" : cout << "\tType: Computer"; //if getType return 0 (first value) Player is human else a computer
	cout << "\tCountry : " << attackerCountry->getName(); cout << "\tNumber of armies : " << attackerNumOfArmies << endl;

	cout << "Defender : " << defenderCountry->getOwner()->getName(); 
	defenderCountry->getOwner()->getType() == 0 ? cout << "\tType: Human" : cout << "\tType: Computer";
	cout << "\tCountry : " << defenderCountry->getName(); cout << "\tNumber of armies : " << defenderNumOfArmies << endl;
}
