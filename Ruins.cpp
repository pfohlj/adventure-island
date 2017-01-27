/*****************************************************************************************
** Program Filename: Ruins.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implenentation file for the ruins clas. For information on a
** specific function, please see its accompanying comment block.
*****************************************************************************************/

#include "Ruins.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: calls the Location constructor and sets gateOpened and pathCleared
** Parameters: n/a
*****************************************************************************************/

Ruins::Ruins() :
	Location()
{
	setGateOpened(false);
	setPathCleared(false);
}

/*****************************************************************************************
** Function: constructor
** Description: passes 4 pointers to the Location constructor and sets gateOpened and pathCleared.
** Parameters: 4 pointers to location and a pointer to the master list of game items
*****************************************************************************************/

Ruins::Ruins(Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	setGateOpened(false);
	setPathCleared(false);
}

/*****************************************************************************************
** Function: destructor
** Description: disconnects all of the objects pointers to Locations
** Parameters:
*****************************************************************************************/

Ruins::~Ruins()
{
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: setGateOpened
** Description: sets the value of gateOpened
** Parameters: gateOpened - boolean value
*****************************************************************************************/

void Ruins::setGateOpened(bool gateOpened)
{
	this->gateOpened = gateOpened;
}

/*****************************************************************************************
** Function: setPathCleared
** Description: sets the value of pathCleared
** Parameters: pathCleared - boolean value
*****************************************************************************************/

void Ruins::setPathCleared(bool pathCleared)
{
	this->pathCleared = pathCleared;
}

/*****************************************************************************************
** Function:getGateOpened
** Description: returns the value of gateOpened
** Parameters: n/a
*****************************************************************************************/

bool Ruins::getGateOpened() const
{
	return gateOpened;
}

/*****************************************************************************************
** Function: getPathCleared
** Description: returns the value of pathCleared
** Parameters: n/a
*****************************************************************************************/

bool Ruins::getPathCleared() const
{
	return pathCleared;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Ruins::describeLocation()
{
	printFile("./text/ruins/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Ruins::briefDescription()
{
	printFile("./text/ruins/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Ruins::determineInteraction()
{
	int interaction;
	
	if (!getGateOpened())
	{
		printFile("./text/ruins/interact1.txt");  
		interaction = validateIntRange(1, 4);
	}
	else
	{
		printFile("./text/ruins/interact2.txt"); 
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

int Ruins::determineMove()
{
	int move;

	if (!getGateOpened())
	{
		printFile("./text/ruins/move1.txt");
		move = validateIntRange(1, 4);
	}
	else
	{
		printFile("./text/ruins/move2.txt"); 
		move = validateIntRange(1, 5);
	}

	return move;
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members. 
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.
** Boolean value not needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Ruins::handleInteract(List*& leatherBag, bool&, int choice)
{
	if (!getGateOpened())
	{
		switch (choice)
		{
		case 1:

			if (leatherBag->isAlreadyOnList("Red Orb"))
			{
				setGateOpened(true);
				printFile("./text/ruins/totemUnlockGate.txt");
			}
			else
			{
				printFile("./text/ruins/totemNoOrb.txt");
			}

			return true;

		case 2:

			printFile("./text/ruins/lockedGate.txt");
			return true;

		case 3:

			printFile("./text/ruins/goldenAltar.txt");
			return true;

		default: return false;
		}
	}

	switch (choice)
	{
	case 1: 

		printFile("./text/ruins/totemGateUnlocked.txt");
		return true;

	case 2: 

		printFile("./text/ruins/goldenAltar.txt");
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

bool Ruins::handleMove(List* leatherBag, Location*& currentLocation, int choice)
{
	if (!getGateOpened())
	{
		switch (choice)
		{
		case 1:

			currentLocation = getWest();
			return true;

		case 2:

			if (getPathCleared())
			{
				currentLocation = getNorth();
				
				return true;
			}
			
			if (leatherBag->isAlreadyOnList("Machete"))
			{
				printFile("./text/clearPath.txt");
				std::cin.get();
				setPathCleared(true);
				currentLocation = getNorth();
				
				return true;
			}

			printFile("./text/jungleNoAccess.txt");
			std::cin.get();
			return true;

		case 3:

			currentLocation = getEast();
			return true;

		default: return false;
		}
	}

	switch (choice)
	{
	case 1:

		currentLocation = getWest();
		return true;

	case 2:

		if (getPathCleared())
		{
			currentLocation = getNorth();

			return true;
		}

		if (leatherBag->isAlreadyOnList("Machete"))
		{
			printFile("./text/clearPath.txt");
			std::cin.get();
			setPathCleared(true);
			currentLocation = getNorth();

			return true;
		}

		printFile("./text/jungleNoAccess.txt");
		std::cin.get();
		return true;

	case 3:

		currentLocation = getEast();
		return true;

	case 4:

		currentLocation = getSouth();
		return true;

	default: return false;
	}
}