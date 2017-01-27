/*****************************************************************************************
** Program Filename: Hut.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Hut class.  For information on 
** specific functions, please see their corresponding comment blocks. 
*****************************************************************************************/

#include "Hut.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function:  constructor
** Description: calls the Location parent constructor and sets the value of string, pathCleared,
** stringdiscovered, doorDiscovered, and doorUnlocked.
** Parameters: a pointer to the master list of game objects
*****************************************************************************************/

Hut::Hut(List* masterList) :
	Location()
{
	string = masterList->getItem("String");
	setPathCleared(false);
	setStringDiscovered(false);
	setDoorDiscovered(false);
	setDoorUnlocked(false);
}

/*****************************************************************************************
** Function: constructor
** Description: passes the value of four Location pointers to the Location constructor
** and sets the value of string, pathCleared, stringdiscovered, doorDiscovered, and doorUnlocked.
** Parameters: 4 pointers to Location objects and a pointer to the master list of game
** objects.
*****************************************************************************************/

Hut::Hut(List* masterList, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) : 
	Location(north, east, south, west)
{
	string = masterList->getItem("String");
	setPathCleared(false);
	setStringDiscovered(false);
	setDoorDiscovered(false);
	setDoorUnlocked(false);
}

/*****************************************************************************************
** Function: destructor
** Description: disconnects all of the objects pointers and sets them to null values.
** Parameters: n/a
*****************************************************************************************/

Hut::~Hut()
{
	string = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: setPathCleared
** Description: sets the value of pathcleared
** Parameters: pathCleared - booleanValue
*****************************************************************************************/

void Hut::setPathCleared(bool pathCleared)
{
	this->pathCleared = pathCleared;
}

/*****************************************************************************************
** Function: setStringDiscovered
** Description: sets the value of stringDiscovered
** Parameters: stringDiscovered - boolean value
*****************************************************************************************/

void Hut::setStringDiscovered(bool stringDiscovered)
{
	this->stringDiscovered = stringDiscovered;
}

/*****************************************************************************************
** Function: setDoorDiscovered
** Description: sets the value of doorDiscovered
** Parameters: doorDiscovered - boolean value
*****************************************************************************************/

void Hut::setDoorDiscovered(bool doorDiscovered)
{
	this->doorDiscovered = doorDiscovered;
}

/*****************************************************************************************
** Function: setDoorUnlocked
** Description: sets the value of doorUnlocked
** Parameters: doorUnlocked - boolean value
*****************************************************************************************/

void Hut::setDoorUnlocked(bool doorUnlocked)
{
	this->doorUnlocked = doorUnlocked;
}

/*****************************************************************************************
** Function: getPathCleared
** Description: returns the value of pathCleared
** Parameters: n/a
*****************************************************************************************/

bool Hut::getPathCleared() const
{
	return pathCleared;
}

/*****************************************************************************************
** Function: getStringDiscovered
** Description: returns the value of stringDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Hut::getStringDiscovered() const
{
	return stringDiscovered;
}

/*****************************************************************************************
** Function: getDoorDiscovered
** Description: returns the value of doorDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Hut::getDoorDiscovered() const
{
	return doorDiscovered;
}

/*****************************************************************************************
** Function: getDoorUnlocked
** Description: returns the value of doorUnlocked
** Parameters: n/a
*****************************************************************************************/

bool Hut::getDoorUnlocked() const
{
	return doorUnlocked;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Hut::describeLocation()
{
	printFile("./text/hut/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Hut::briefDescription()
{
	printFile("./text/hut/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Hut::determineInteraction()
{
	int interaction;

	if (!getDoorDiscovered())
	{
		printFile("./text/hut/interact1.txt");  
		interaction = validateIntRange(1, 4);
	}
	else
	{
		printFile("./text/hut/interact2.txt"); 
		interaction = validateIntRange(1, 3);
	}

	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Hut::determineMove()
{
	int move;

	if (!getDoorDiscovered())
	{
		printFile("./text/hut/move1.txt");
		move = validateIntRange(1, 4);
	}
	else
	{
		printFile("./text/hut/move2.txt");
		move = validateIntRange(1, 5);
	}

	return move;
}

/*****************************************************************************************
** Function: handleInteract
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members. 
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.
** Boolean value not needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Hut::handleInteract(List*& leatherBag, bool&, int choice)
{
	if (!getDoorDiscovered())
	{
		switch (choice)
		{
		case 1: 

			setDoorDiscovered(true);
			printFile("./text/hut/discoverDoor.txt");

			return true;

		case 2: 

			printFile("./text/hut/carpet.txt");
			return true;

		case 3:

			if (leatherBag->isAlreadyOnList("String"))
			{
				printFile("./text/hut/blanketNoString.txt");
			}
			else
			{
				if (!getStringDiscovered())
				{
					setStringDiscovered(true);
					printFile("./text/hut/newString.txt");

					if (leatherBag->listIsFull())
					{
						printFile("./text/inventoryFull.txt");
					}
					else
					{
						leatherBag->addItem(string);
						std::cout << std::endl << "String ";
						printFile("./text/added.txt");
					}
				}
				else
				{
					printFile("./text/hut/oldString.txt");

					if (leatherBag->listIsFull())
					{
						printFile("./text/inventoryFull.txt");
					}
					else
					{
						leatherBag->addItem(string);
						std::cout << std::endl << "String ";
						printFile("./text/added.txt");
					}
				}
			}

			return true;

		default: return false;
		}
	}

	switch (choice)
	{
	case 1: 
		
		printFile("./text/hut/carpet.txt");
		return true;

	case 2: 

		if (leatherBag->isAlreadyOnList("String"))
		{
			printFile("./text/hut/blanketNoString.txt");
		}
		else
		{
			if (!getStringDiscovered())
			{
				setStringDiscovered(true);
				printFile("./text/hut/newString.txt");

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
				}
				else
				{
					leatherBag->addItem(string);
					std::cout << std::endl << "String ";
					printFile("./text/added.txt");
				}
			}
			else
			{
				printFile("./text/hut/oldString.txt");

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
				}
				else
				{
					leatherBag->addItem(string);
					std::cout << std::endl << "String ";
					printFile("./text/added.txt");
				}
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
** Parameters: leatherBag - pointer to the leather bag of items, currentLocation - 
** reference parameter to a pointer to the current location.  Allows the method to change 
** the user's location to their desired destination, choice - user's move choice.
*****************************************************************************************/

bool Hut::handleMove(List* leatherBag, Location*& currentLocation, int choice)
{
	if (!getDoorDiscovered())
	{
		switch (choice)
		{
		case 1:

			currentLocation = getWest();
			return true;

		case 2:

			currentLocation = getEast();
			return true;

		case 3:

			if (getPathCleared())
			{
				currentLocation = getSouth();
			}
			else if (leatherBag->isAlreadyOnList("Machete"))
			{
				printFile("./text/clearPath.txt");
				std::cin.get();
				setPathCleared(true);
				currentLocation = getSouth();
			}
			else
			{
				printFile("./text/jungleNoAccess.txt");
				std::cin.get();
			}

			return true;

		default: return false;
		}
	}

	switch (choice)
	{
	case 1:

		if (!getDoorUnlocked())
		{
			if (leatherBag->isAlreadyOnList("Gold Key"))
			{
				printFile("./text/hut/unlockDoor.txt");
				std::cin.get();
				setDoorUnlocked(true);
				currentLocation = getNorth();
			}
			else
			{
				printFile("./text/hut/lockedDoor.txt");
				std::cin.get();
			}
		}
		else
		{
			currentLocation = getNorth();
		}

		return true;

	case 2: 
		currentLocation = getWest();
		return true;
	case 3: 
		currentLocation = getEast();
		return true;
	case 4: 

		if (getPathCleared())
		{
			currentLocation = getSouth();
		}
		else if (leatherBag->isAlreadyOnList("Machete"))
		{
			printFile("./text/clearPath.txt");
			std::cin.get();
			setPathCleared(true);
			currentLocation = getSouth();
		}
		else
		{
			printFile("./text/jungleNoAccess.txt");
			std::cin.get();
		}

		return true;

	default: return false;
	}
}
