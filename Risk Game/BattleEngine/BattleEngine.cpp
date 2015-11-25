
//----------------------------------------------------- 
//Advanced program design with C++
//COMP 345 -- Fall 2015
//----------------------------------------------------- 

/* 

'' This program will implements the mechanics of a country attacking another using dice as
described in the project description. The player chooses one of the countries he owns that contains two or more
armies, and declares an attack on an adjacent country that is owned by another player. A battle is then simulated
by the attacker rolling at most 3 dice (which should not be more than the number of armies contained in the
attacking country) and the defender rolling at most 2 dice (which should not be more than the number of armies
contained in the defending country). The outcome of the attack is determined by comparing the defender¡¯s best 2
dice roll with the attacker¡¯s best dice roll. If the defender rolls greater or equal to the attacker then the attacker
loses an army, otherwise the defender loses an army. If the defender rolled two dice then his other dice roll is
compared to the attacker's second best dice roll and a second army is lost by the attacker or defender in the
same way. The attacker can choose to continue attacking until either all his armies or all the defending armies
have been eliminated. If all the defender's armies are eliminated the attacker captures the territory. The attacking
player must then place a number of armies in the conquered country which is greater or equal than the number of
dice that was used in the attack that resulted in conquering the country. There must be an ¡°all-in¡± attack mode that
uses the maximum number of dice on both sides and runs automatically until the attack results in either a) the
defending country to be conquered and all armies of the conquering country are moved to the conquered country
or b) the attacking country runs out of armies and cannot attack anymore ''

* From Project Description. 
* @author Kendy Jeune 27014465 (Team 12)
* @Version Microsoft Visual Studio 2013
*/

#include <iostream> 
#include <string>
#include "BattleEngine.h"

#include "Player.h"
#include <cstdlib>// In order to use the random number generator we need to include the <cstdlib> header
#include <ctime>
#include <algorithm> //sort algorithm used
#include <functional>

using namespace std;


void Attack();//Foward declaration
bool isAllInMode();//Foward declaration
bool isContinue();//Foward declaration
void generateRollList(int* emptyArray, int size);//Foward declaration
int roll();//Foward declaration
int numberOfArmiesToSend(Country country1, int numberOfRolls, int attackerNumArmies);//Foward declaration
bool isAttackOver(int attackerNum_armies, int defenderNum_armies);//Foward declaration

	Country *attackerCountry;
	Country *defenderCountry;
	
	Player *attacker_player;
	Player *defender_player;
	
	BattleEngine::BattleEngine(Country *country1, Country *country2){
		
		attackerCountry = country1;
		defenderCountry = country2;

		attacker_player = attackerCountry->getOwner();
		defender_player = defenderCountry->getOwner();

		attack();
	
	}

	BattleEngine::~BattleEngine(){
		delete attackerCountry;
		delete defenderCountry;

	}
		
	void BattleEngine::attack() {
		
		//Declaring local variable
		int attackerNum_armies = attackerCountry->getNumArmies();
		int defenderNum_armies = defenderCountry->getNumArmies();
		int num_ArmiesToSend;
		srand((unsigned)time(0)); //generate random number based on computer clocks

		int	attackerNum_Roll, defenderNum_Roll;
		bool allInMode = false;

		//cout << "\nAttacker # armies : " << attackerNumOfArmies << "\tDefender # armies : " << defenderNumOfArmies << endl;
		cout << "\t\t\n\nBeginning of Attacking Phase\n\n";
		
		//display Batte Info
		displayBattleInfo(attackerNum_armies, defenderNum_armies);

		//Detect if the Attacker is a computer Player. if it is do Strategy
		if (!attacker_player->isHuman(*attacker_player)){
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
		cout << attacker_player->getName() << " : How many armies do you wish to send to attack? (Not more than ( " << attackerNum_armies - 1 << " )\n";
		int sentArmies;
		cin >> sentArmies;

		//if Users input an invalid number return to start 
		if (sentArmies > attackerNum_armies - 1 || sentArmies <= 0)
			goto start;

		//Will determine how many rolls the Attacker have (3,2 or 1)
		if (sentArmies >= 3)
			attackerNum_Roll = 3;
		else if (sentArmies == 2)
			attackerNum_Roll = 2;
		else
			attackerNum_Roll = 1;

		//Label if the user choose the all in mode
	allIn:

		//Will determine how many rolls both the defender and the attacker will have.
		if (allInMode)
			attackerNum_armies > 2 ? attackerNum_Roll = 3 : attackerNum_Roll = 2;

		defenderNum_armies > 1 ? defenderNum_Roll = 2 : defenderNum_Roll = 1;

		//Creating the arrays that will contains the rolls list
		int* attackerRollsList = new int[attackerNum_Roll];
		int* defenderRollsList = new int[defenderNum_Roll];

		generateRollList(attackerRollsList, attackerNum_Roll);//will generate the attacker rolls
		generateRollList(defenderRollsList, defenderNum_Roll);//will generate the defender rolls 

		//This is a method taken from the std libraries. this method will sort arrays in descending orders.
		sort(attackerRollsList, attackerRollsList + attackerNum_Roll, greater<int>());
		sort(defenderRollsList, defenderRollsList + defenderNum_Roll, greater<int>());

		cout << "\nAttacker # armies : " << attackerNum_armies << "\tDefender # armies : " << defenderNum_armies << endl;
		cout << " Attackers rolls :" << endl;//displaying attacker rolls
		//for loop that iterates through the Arrays and display all its elements
		for (int i = 0; i < attackerNum_Roll; i++)
			cout << attackerRollsList[i] << ", ";

		cout << "\n Defender rolls :" << endl;//displaying Defender rolls
		//for loop that iterates through the Arrays and display all its elements
		for (int i = 0; i < defenderNum_Roll; i++)
			cout << defenderRollsList[i] << ", ";

		//Will return the minimum number of roll that we will compare (3,2 or 1)
		int minNumOfRolls = std::min(attackerNum_Roll, defenderNum_Roll);

		//loop and verify the attacker and defender corresponding dices
		for (int i = 0; i < minNumOfRolls; i++){
			if (attackerRollsList[i] > defenderRollsList[i]){

				defenderNum_armies -= 1; //Defender lose
				if (defenderNum_armies == 0)//Make sure the defender # of armies don't go below 0
					break;
			}
			else{
				if (attackerNum_armies <= 1)//Make sure the attacker # of armies don't go below 1
					break;
				attackerNum_armies -= 1; //Attacker lose
			}
		}

		cout << "\n\nAttacker # armies : " << attackerNum_armies << "\tDefender # armies : " << defenderNum_armies << endl;//Displaying the armies

		//Defender armies reach 0
		if (isAttackOver(attackerNum_armies, defenderNum_armies) && defenderNum_armies < 1){
			cout << "\n\t\tDefender lost, Attacker conquered the defending country\n";
			attacker_player->setBattlesWonTotal(attacker_player->getBattlesWonTotal() + 1);//Add 1 to the number of Battle won
			num_ArmiesToSend = numberOfArmiesToSend(attackerNum_Roll, attackerNum_armies);
			goto stop;
		}

		//Attacker armies reach 1
		if (isAttackOver(attackerNum_armies, defenderNum_armies) && attackerNum_armies <= 1){
			cout << "\n\t\tAttacker ran out of armies\n";
			defender_player->setBattlesWonTotal(defender_player->getBattlesWonTotal() + 1);//Add 1 to the number of Battle won
			goto stop;
		}

		//If user choose all in mode the program will go to allIn label and loop until the attack phase is over.
		if (allInMode){
			if (isAttackOver(attackerNum_armies, defenderNum_armies))
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
		displayBattleInfo(attackerNum_armies, defenderNum_armies);
		cout << "\t\t\nTurns end\n\n";

		delete[]attackerRollsList;//Deallocate memory
		delete[]defenderRollsList;//Deallocate memory
	}
	// This function generates the List of rolls for each player in an attack situation.
	void BattleEngine::generateRollList(int* emptyArray, int size){
		for (int i = 0; i < size; i++){
			emptyArray[i] = roll();
		}
	}

	//return random value from 1 to 6
	int BattleEngine::roll(){
		return rand() % 6 + 1;
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
		if (attacker_player->isHuman(*attacker_player))
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
		if (attacker_player->isHuman(*attacker_player)) {
			numArmtoSend = (rand() % ((attackerNumArmies)-minimumTransArmy)) + minimumTransArmy; //return random number between (min trans armies and max armies -1)
			cout << "\t" << attacker_player->getName() << " returned " << numArmtoSend << " Army(ies)\n" << endl;
			return numArmtoSend;
		}
		else{
			//Attacker Player is Human
			do{
				cout << "\n" << attacker_player->getName() << " : How many armies do you wish to send to your new country ? : ";
				cout << " Minimum number of transferable armies : " << minimumTransArmy << "\tMaximum number of transferable armies : " << attackerNumArmies - 1 << endl;
				cin >> numArmtoSend;
				if (numArmtoSend < minimumTransArmy || numArmtoSend >= attackerNumArmies){
					cout << "\nWarning : Minimum number of transferable armies : " << minimumTransArmy << "\tMaximum number of transferable armies : " << attackerNumArmies - 1 << endl;
				}
			} while (numArmtoSend < minimumTransArmy || numArmtoSend >= attackerNumArmies);
			return numArmtoSend;
		}
	}

	//Will display the Battle Information before the attack
	void BattleEngine::displayBattleInfo(int attackerNumOfArmies, int defenderNumOfArmies){
		cout << "Attacker : " << attacker_player->getName();
		attacker_player->getType() == 0 ? cout << "\tType: Human" : cout << "\tType: Computer"; //if getType return 0 (first value) Player is human else a computer
		cout << "\tCountry : " << attackerCountry->getName(); cout << "\tNumber of armies : " << attackerNumOfArmies << endl;

		cout << "Defender : " << defenderCountry->getOwner()->getName(); 
		defenderCountry->getOwner()->getType() == 0 ? cout << "\tType: Human" : cout << "\tType: Computer";
		cout << "\tCountry : " << defenderCountry->getName(); cout << "\tNumber of armies : " << defenderNumOfArmies << endl;
	}
