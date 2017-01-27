/*****************************************************************************************
** Program Filename: Dungeon.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: Implementation file for Dungeon class. See function comment blocks for
** more information. 
*****************************************************************************************/

#include "Dungeon.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: calls the Location constructor and sets the value of blueOrb, wordsTranslated,
** and word 1 - 4
** Parameters: pointer to master list of available game objects.
*****************************************************************************************/

Dungeon::Dungeon(List* masterList) :
	Location()
{
	blueOrb = masterList->getItem("Blue Orb");
	setAllWords(false);
	updateWordsTranslated();
}

/*****************************************************************************************
** Function: override constructro
** Description: passes 4 Location object pointers to the default constructor and sets the
** value of blueOrb, word1-4, and wordsTranslated.
** Parameters: 4 pointers to Location objects and a pointer to the games master list of
** available items.
*****************************************************************************************/

Dungeon::Dungeon(List* masterList, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	blueOrb = masterList->getItem("Blue Orb");
	setAllWords(false);
	updateWordsTranslated();
}

/*****************************************************************************************
** Function: destructor.
** Description: disconnects all pointer variables from other objects
** Parameters: n/a
*****************************************************************************************/

Dungeon::~Dungeon() 
{
	blueOrb = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: setWord1
** Description:sets the value of word1
** Parameters: word1 - boolean value
*****************************************************************************************/

void Dungeon::setWord1(bool word1)
{
	this->word1 = word1;
}

/*****************************************************************************************
** Function: setWord2
** Description:sets the value of word2
** Parameters: word2 - boolean value
*****************************************************************************************/

void Dungeon::setWord2(bool word2)
{
	this->word2 = word2;
}

/*****************************************************************************************
** Function: setWord3
** Description:sets the value of word3
** Parameters: word3 - boolean value
*****************************************************************************************/

void Dungeon::setWord3(bool word3)
{
	this->word3 = word3;
}

/*****************************************************************************************
** Function: setWord4
** Description:sets the value of word4
** Parameters: word4 - boolean value
*****************************************************************************************/

void Dungeon::setWord4(bool word4)
{
	this->word4 = word4;
}

/*****************************************************************************************
** Function: setAllWords
** Description: sets the value of words 1-4
** Parameters: value - boolean value
*****************************************************************************************/

void Dungeon::setAllWords(bool value)
{
	setWord1(value);
	setWord2(value);
	setWord3(value);
	setWord4(value);
}

/*****************************************************************************************
** Function: updateWordsTranslated
** Description: if all words are translated sets the value of wordsTranslated to true, 
** otherwise, sets it false. 
** Parameters: n/a
*****************************************************************************************/

void Dungeon::updateWordsTranslated()
{
	if (getWord1() && getWord2() && getWord3() && getWord4())
	{
		wordsTranslated = true;
	}
	else
	{
		wordsTranslated = false;
	}
}

/*****************************************************************************************
** Function: getWord1
** Description: returns the value of word1
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::getWord1() const
{
	return word1;
}

/*****************************************************************************************
** Function: getWord2
** Description: returns the value of word2
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::getWord2() const
{
	return word2;
}

/*****************************************************************************************
** Function: getWord3
** Description: returns the value of word3
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::getWord3() const
{
	return word3;
}

/*****************************************************************************************
** Function: getWord4
** Description: returns the value of word4
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::getWord4() const
{
	return word4;
}

/*****************************************************************************************
** Function: getWordsTranslated
** Description: returns the value of wordsTranslated
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::getWordsTranslated() const
{
	return wordsTranslated;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Dungeon::describeLocation()
{
	printFile("./text/dungeon/look.txt"); 
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Dungeon::briefDescription()
{
	printFile("./text/dungeon/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Dungeon::determineInteraction()
{
	printFile("./text/dungeon/interaction.txt");
	int interaction = validateIntRange(1, 2);
	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Dungeon::determineMove()
{
	printFile("./text/dungeon/move.txt"); 
	int move = validateIntRange(1, 2);
	return move;
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.
** Boolean value not needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Dungeon::handleInteract(List*& leatherBag, bool&, int choice)
{
	switch (choice)
	{
	case 1:

		if (getWordsTranslated())
		{
			if (leatherBag->isAlreadyOnList("Blue Orb"))
			{
				printFile("./text/dungeon/noOrb.txt");
			}
			else
			{
				printFile("./text/dungeon/getOrbNoLevers.txt");

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
					std::cout << "Press enter to continue...";
				}
				else
				{
					leatherBag->addItem(blueOrb);
					std::cout << "Blue Orb ";
					printFile("./text/added.txt");
				}
			}
		}
		else
		{
			if (attemptPuzzle())
			{
				printFile("./text/dungeon/discoverBlueOrb.txt");

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
				}
				else
				{
					leatherBag->addItem(blueOrb);
					std::cout << "Blue Orb ";
					printFile("./text/added.txt");
				}
			}
			else
			{
				printFile("./text/dungeon/puzzleFail.txt");
			}
		}

		return true;

	default: return false;
	}
}

/*****************************************************************************************
** Function: handleMove
** Description: accepts the user's choice of movement location and handles that choice
** based on whether the user can or cannot make that move.
** Parameters: dummy - unneeded parameter, currentLocation - reference parameter to a
** pointer to the current location.  Allows the method to change the user's location to
** their desired destination, choice - user's move choice.
*****************************************************************************************/
bool Dungeon::handleMove(List* dummy, Location*& currentLocation, int choice)
{
	switch (choice)
	{
	case 1:
		
		currentLocation = getNorth();
		return true;

	default: return false;
	}
}

/*****************************************************************************************
** Function: attemptPuzzle
** Description: prompts the user to select 4 word values for the four words that have
** popped on the signs around the island.  If the user gets all four correct, reutrns
** true. Else, returns false.
** Parameters: n/a
*****************************************************************************************/

bool Dungeon::attemptPuzzle()
{
	int puzzleSelection;

	printFile("./text/dungeon/puzzleIntro.txt");
	std::cin.get();

	system("clear");
	printFile("./text/dungeon/puzzleMenu1.txt");
	puzzleSelection = validateIntRange(1, 4);

	if (puzzleSelection == 2) 
	{
		setWord1(true);
		printFile("./text/dungeon/wordCorrect.txt");
		std::cin.get();
	}

	system("clear");
	printFile("./text/dungeon/puzzleMenu2.txt");
	puzzleSelection = validateIntRange(1, 4);

	if (puzzleSelection == 1)
	{
		setWord2(true);
		printFile("./text/dungeon/wordCorrect.txt");
		std::cin.get();
	}

	system("clear");
	printFile("./text/dungeon/puzzleMenu3.txt");
	puzzleSelection = validateIntRange(1, 4);

	if (puzzleSelection == 4)
	{
		setWord3(true);
		printFile("./text/dungeon/wordCorrect.txt");
		std::cin.get();
	}

	system("clear");
	printFile("./text/dungeon/puzzleMenu4.txt");
	puzzleSelection = validateIntRange(1, 4);

	if (puzzleSelection == 3)
	{
		setWord4(true);
		printFile("./text/dungeon/wordCorrect.txt");
		std::cin.get();
	}

	updateWordsTranslated();

	if (getWordsTranslated())
	{
		system("clear");
		return true;
	}

	system("clear");
	setAllWords(false);
	return false;
}
