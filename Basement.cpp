/*****************************************************************************************
** Program Filename: Basement.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Basement class.  For information
** on specific functions, see their corresponding comment block.
*****************************************************************************************/

#include "Basement.hpp"
#include "HelperFunctions.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

/*****************************************************************************************
** Function: default constructor
** Description: sets up the class' private data members.  Retrieves a pointer to the 
** silver key item from the list it is passed and then after using the built in set 
** methods, calls setupRiddleArray to fill the array with the names of the files the 
** riddles are contained in.  Finally, seeds the rand function in order to setup random
** riddle generation.
** Parameters: masterList - pointer to the master list containing the Silver Key item
*****************************************************************************************/

Basement::Basement(List* masterList) :
	Location()
{
	silverKey = masterList->getItem("Silver Key");
	setNumRiddlesSolved(0);
	setCompletedRiddles(false);
	setAttemptedRiddles(false);
	setupRiddleArrays();
	usedRiddles = nullptr;
	int seed = time(0);
	srand(seed);
}

/*****************************************************************************************
** Function: overload constructor
** Description: takes pointers to other classes and passes them to the Location destructor
** before following the same pattern as the default constructor.
** Parameters: four pointers to location objects and one pointer to a list object 
** containing a pointer to the Silver Key item.
*****************************************************************************************/

Basement::Basement(List* masterList, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	silverKey = masterList->getItem("Silver Key");
	setNumRiddlesSolved(0);
	setCompletedRiddles(false);
	setAttemptedRiddles(false);
	setupRiddleArrays();
	usedRiddles = nullptr;
	int seed = time(0);
	srand(seed);
}

/*****************************************************************************************
** Function: destructor
** Description: sets the key pointer to a null value and then if the usedRiddles object
** has had memory allocated and not freed, frees that memory before disconnedting the 
** object from any other objects.
** Parameters: N/A
*****************************************************************************************/

Basement::~Basement()
{
	silverKey = nullptr;

	if (usedRiddles != nullptr) // used riddles still has allocated memory
	{
		delete [] usedRiddles;
		usedRiddles = nullptr;
	}

	disconnectAllPaths();
}

/*****************************************************************************************
** Function: setNumRiddlesSolves
** Description: sets the number of riddles solved to the parameter num
** Parameters: and integer called num
*****************************************************************************************/

void Basement::setNumRiddlesSolved(int num)
{
	numRiddlesSolved = num;
}

/*****************************************************************************************
** Function: setCompletedRiddles
** Description: sets completedriddles to the parameter value
** Parameters: boolean called value
*****************************************************************************************/

void Basement::setCompletedRiddles(bool value)
{
	completedRiddles = value;
}

/*****************************************************************************************
** Function: setAttemptedRiddles
** Description: sets attemptedRiddles to the parameter attempted
** Parameters: attempted - boolean value indicating whether riddles have been attempted
*****************************************************************************************/

void Basement::setAttemptedRiddles(bool attempted)
{
	attemptedRiddles = attempted;
}

/*****************************************************************************************
** Function: getNumRiddlessolved
** Description: returns the value of numRiddlesSolved
** Parameters: N/A
*****************************************************************************************/

int Basement::getNumRiddlesSolved() const
{
	return numRiddlesSolved;
}

/*****************************************************************************************
** Function: getCompletedRiddles
** Description: returns the value of completedRiddles
** Parameters: N/A
*****************************************************************************************/

bool Basement::getCompletedRiddles() const
{
	return completedRiddles;
}

/*****************************************************************************************
** Function: getAttemptedRiddles
** Description: returns the value of attemptedRiddles
** Parameters: N/A
*****************************************************************************************/

bool Basement::getAttemptedRiddles() const
{
	return attemptedRiddles;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the 
** screen. 
** Parameters: N/A
*****************************************************************************************/

void Basement::describeLocation()
{
	printFile("./text/basement/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Basement::briefDescription()
{
	printFile("./text/basement/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Basement::determineInteraction()
{
	printFile("./text/basement/interact.txt");
	int interact = validateIntRange(1, 2);
	return interact;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Basement::determineMove()
{
	printFile("./text/basement/move.txt");
	int interact = validateIntRange(1, 2);
	return interact;
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.  See comments for flow of logic.
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag, allows
** the function to add the silver key if the user passes the riddles.  Boolean value not
** needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Basement::handleInteract(List*& leatherBag, bool&, int choice)
{
	switch (choice)
	{
	case 1:		// user chosse  to interact with the box

		if (getCompletedRiddles())	// already completed riddles
		{
			if (leatherBag->isAlreadyOnList("Silver Key"))	// already has the Silver Key
			{
				printFile("./text/basement/emptyBox.txt");
			}
			else	// does not have the silver key
			{
				printFile("./text/basement/noGhost.txt");

				if (leatherBag->listIsFull()) // bag is full
				{
					printFile("./text/inventoryFull.txt");
				}
				else // room in bag
				{
					leatherBag->addItem(silverKey);
					std::cout << "Silver Key ";
					printFile("./text/added.txt");
				}
			}
		}
		else // user has not attempted riddles
		{
			if (attemptRiddles()) // user successfully completes riddle challenge
			{
				system("clear");
				printFile("./text/basement/riddlePass.txt");

				if (leatherBag->listIsFull()) // bag is full
				{
					printFile("./text/inventoryFull.txt");
				}
				else // bag has room
				{
					leatherBag->addItem(silverKey);
					std::cout << "Silver Key ";
					printFile("./text/added.txt");
				}
			}
			else // user fails riddles
			{
				printFile("./text/basement/riddleFail.txt");
			}
		}

		return true;

	default: return false; // user canceled interaction
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

bool Basement::handleMove(List* dummy, Location*& currentLocation, int choice)
{
	switch (choice)
	{
	case 1:

		currentLocation = getSouth();
		return true;

	default: return false;
	}
}

/*****************************************************************************************
** Function: setupRiddleArrays()
** Description: fills the riddle array with the names of the 10 riddle files, riddle_0 - 
** riddle_9.  Also initializes the answer array with answer's indexed to the location of
** the riddle's placement in the riddleFiles array.
** Parameters: N/A
*****************************************************************************************/

void Basement::setupRiddleArrays()
{
	std::string riddle = "./text/basement/riddle_"; // beginning of file location
	std::string txt = ".txt";						// postfix

	for (int i = 0; i < 10; i++)
	{
		riddleFiles[i] = riddle + std::to_string(i) + txt;
	}

	riddleAnswers[0] = 4;
	riddleAnswers[1] = 2;
	riddleAnswers[2] = 3;
	riddleAnswers[3] = 1;
	riddleAnswers[4] = 1;
	riddleAnswers[5] = 2;
	riddleAnswers[6] = 3;
	riddleAnswers[7] = 3;
	riddleAnswers[8] = 1;
	riddleAnswers[9] = 4;
}

/*****************************************************************************************
** Function: attemptRiddle
** Description: randomly selects three riddles from the riddle array and prompts the user
** for the answer.  If the user gets three in a row correct, it returns a true value.  If
** the user misses one, it returns false and resets the associated boolean values.
** Parameters: N/A
*****************************************************************************************/

bool Basement::attemptRiddles()
{
	int riddleNumber;	// store randomly generated number
	int usersAnswer;	// store user's answer
	int counter = 0;	// keep track of how many riddles have been selected
	
	// print welcome from ghost
	if (getAttemptedRiddles())
	{
		printFile("./text/basement/ghostAlreadyAttempted.txt");
		std::cin.get();
	}
	else
	{
		printFile("./text/basement/ghostFirstWelcome.txt");
		std::cin.get();
		setAttemptedRiddles(true);
	}

	// select random riddle and store that selection number in the usedRiddles array
	riddleNumber = rand() % 10;
	std::string tempString = riddleFiles[riddleNumber];
	usedRiddles = new int[3];
	usedRiddles[counter] = riddleNumber;
	counter++;

	// loop until user gets 1 wrong or 3 right
	while (getNumRiddlesSolved() < 3)
	{
		system("clear");
		std::cout << "Riddle number " << counter << ":" << std::endl;

		printFile(tempString);
		usersAnswer = validateIntRange(1, 4);

		if (usersAnswer != riddleAnswers[riddleNumber]) // user selected incorrectly
		{
			std::cout << "WRONG!" << std::endl << std::endl;
			std::cout << "Press enter to continue...";
			std::cin.get();

			// free the memory and reset number solved to 0
			delete [] usedRiddles;
			setNumRiddlesSolved(0);
			return false;
		}

		std::cout << "CORRECT!" << std::endl << std::endl;
		std::cout << "Press enter to continue...";
		std::cin.get();
		
		setNumRiddlesSolved(getNumRiddlesSolved() + 1);
		 
		// generate next randomly selected riddle
		while (getNumRiddlesSolved() != 3)
		{
			bool noMatchFound = true;
			riddleNumber = rand() % 10;

			for (int i = 0; i < counter; i ++)
			{
				if (riddleNumber == usedRiddles[i]) // number has been used
				{
					noMatchFound = false;
					break;
				}
			}

			// if generated number has not bee used
			if (noMatchFound)
			{
				usedRiddles[counter] = riddleNumber;
				tempString = riddleFiles[riddleNumber];
				counter++;
				break;
			}
		}
	}
	
	// user has successfully completed 3 riddles if this code is reached
	system("clear");
	setCompletedRiddles(true);
	delete [] usedRiddles;
	usedRiddles = nullptr;
	return true;
}
