# RiskGame

## TODO
- [ ] 
- [ ] Reinforcement
  - [ ] Feature: Continent Bonus needs to be used/implemented.
  - [x] Bug: Reinforcement message showing twice
  - [ ] Formatting: Clean user messages for reinforcement part
  - [ ] Formatting: Card part clean up message to user.
  - [x] Add: Card ASCII Art
  - [ ] Change: Display All card 
  - [ ] Test: Card part at begenning of reinforcement.
  - [ ] Test: OverAll Reinforcement.
- [ ] Attack
  - [x] Bug: no player countries available for attack... Check user output
  - [x] Bug: no enemy countries connected to our selected attacker country
  - [ ] Test/Bug: All countries lost when transferring cards after defeat
  - [x] Bug: All In mode skips country stats being shown every step ... System("pause")
  - [ ] Bug: Dice Rolls always show 4.	
- [ ] Fortification
  - [ ] Nothing left ???
  - [ ] Bug: Exiting fortification with -1 results in "vector subscript out of range" bug
- [ ] GameDriver
  - [ ] Add Winner Notification note: Player countries size == map countries size... DO SOMETHING
  
## GRADING TODO
- [ ] Functional Requirements 35
  - [x] Map creation and editing 7
    - [x] User - driven creation of map elements, such as country, continent, and connectivity between countries. 1
    - [x] Saving a map to a file exactly as edited 1
    - [x] Loading a map from an existing file, then editing the map 1
    - [x] Use of the Adapter pattern to save / load from two different map file formats(see individual assignment 3). 2
    - [x] Verification of map correctness upon saving / loading(at least 3 types of incorrect maps, including verification that the
          map is a connected graph, and that each continent is a connected graph) 2
  - [ ] Game driver 4
    - [x] Implementation of a round - robin loop for players’ turns / phases, 
    - [ ] identification of a winner and end of game, 
    - [x] defeated player is removed from the round - robin loop. 2
    - [ ] Save / Load a game in progress using a Builder pattern(see individual assignment 3). 2
  - [ ] Game display 8 -- TOMORROW -- 
    - [ ] Player Observer that displays relevant information about a player(see individual assignment 2). 2
    - [ ] Map Observer that displays relevant information about the map(see individual assignment 2). 2
    - [ ] Game statistics Observer / Decorator that displays user - selected game statistics(see individual assignment 3). 2
		--CHRIS has this done but it is buggy and crap, it Update() doesn't work for more than two decorators
    - [ ] Game log Observer / Decorator that displays logging of user - selected players / phases(see individual assignment 3). 2
  - [ ] Startup phase 5
    - [ ] Game log and game statistics Observers are initially set to show user - selected parts(see individual assignment 3) 
          --Reza A3 has it done... needs to implement.
    - [ ] using the Observer and Decorator patterns. 1 --- See Previous Line
    - [ ] User selection of a previously user - saved map, then load the map. 1
    - [x] User chooses the number of players, all countries are randomly assigned. 1
    - [ ] Types of players are initially assigned and implemented using a Strategy pattern(see individual assignment 2).
          Types of players can be changed at any time during play. 2
  - [ ] Reinforcement phase 4
    - [ ] Calculation of correct number of reinforcement armies and placement of armies on the map. 1 @CHRIS TEST
    - [ ] Correct implementation of cards and their additional reinforcements. 3 @CHRIS TEST 
  - [ ] Attack phase 6
    - [x] Correct identification of valid attacking / attacked country. 1
    - [ ] Correct implementation of an attack using the Risk battle model. 3 @Kendy Semi done... check and test...
    - [x] Correct implementation of the post - battle movement after a victory. 1
    - [ ] A victory gives a card, eliminating a player transfers all the defeated player’s cards. 1 @CHRIS test
  - [ ] Fortification phase 1
    - [ ] Implementation of a single valid move according to the Risk rules. 1 @CHRIS do we do more than one move ?
    
Graduation stuff....
Graduate attributes—skills 15
Knowledge-base Indicator 1.3: Knowledge-base in a specific domain: demonstrated knowledge of
programming principles used in the implementation. 1
Design
Indicator 4.1: Problem identification and information gathering: knowledge and correct
understanding of the functional requirements and the game rules. 2
Indicator 4.3: Architectural and detailed design: Rationale for overall project architectural
structure. Demonstration/explanation of the correct use of three different design patterns
such as those implemented in the individual assignments.
3
Indicator 4.4: Implementation and validation: Correct use of C++ features leading to stable
execution that has been properly tested in various situations. 2
Use of tools
Indicator 5.1: Ability to use appropriate tools, techniques and resources: proficient use of
particular tools (C++ language, libraries, project management tools, etc.) for the
implementation.
2
Indicator 5.2: Ability to select appropriate tools, techniques, and resources: justified
adoption of tools in the project (e.g. compiler, IDE, libraries, project management tools,
etc).
1
Communication
Indicator 7.3: Documentation: Code readability: layout, naming. Consistent use of
comments.
2
Indicator 7.4: Oral presentation: Structure and demonstrated preparation of presentation,
using appropriate presentation techniques. Demonstrated knowledge of code base/clarity
of explanations.
2
Total 50
