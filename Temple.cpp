/*****************************************************************************************
** Program Filename: Temple.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Temple class.  For informaton
** on a specific method, please see its preceeding comment block.
*****************************************************************************************/

#include "Temple.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: default constructor
** Description: calls Location constructor
** Parameters: n/a
*****************************************************************************************/

Temple::Temple() :
	Location() {}

/*****************************************************************************************
** Function: override constructor
** Description: passes 4 location pointers to the Location constructor.
** Parameters: 4 Location pointers
*****************************************************************************************/

Temple::Temple(Location *north = nullptr, Location *east = nullptr, 
	Location *south = nullptr, Location *west = nullptr) :
	Location(north, east, south, west) {}

/*****************************************************************************************
** Function: destructor
** Description: disconnects the Temple object from all other Location objecgts.
** Parameters: n/a
*****************************************************************************************/

Temple::~Temple()
{
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Temple::describeLocation()
{
	printFile("./text/temple/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Temple::briefDescription()
{
	printFile("./text/temple/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Temple::determineInteraction()
{
	printFile("./text/temple/interact.txt");
	int interaction = validateIntRange(1, 2);
	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Temple::determineMove()
{
	printFile("./text/temple/move.txt");
	int move = validateIntRange(1, 5);
	return move;
}

/*****************************************************************************************
** Function: handleInteract
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members. 
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.
** gameOver changed to true if user has both the red and the blue orbs, an integer 
** indicating the user's choice.
*****************************************************************************************/

bool Temple::handleInteract(List*& leatherBag, bool& gameOver, int choice)
{
	switch (choice)
	{
	case 1:

		if (leatherBag->isAlreadyOnList("Red Orb") &&
			leatherBag->isAlreadyOnList("Blue Orb"))
		{
			system("clear");
			printFile("./text/temple/templeCollapse.txt");
			std::cin.get();
			system("clear");
			printFile("./text/temple/endGame.txt");
			gameOver = true;
		}
		else
		{
			printFile("./text/temple/altarNoOrb.txt");
		}

		return true;

	default: return false;
	}
}

/*****************************************************************************************
** Function: handleMove
** Description: accepts the user's choice of movement location and handles that choice
** based on whether the user can or cannot make that move.
** Parameters: leatherBag - unneeded parameter, currentLocation - reference parameter to a
** pointer to the current location.  Allows the method to change the user's location to
** their desired destination, choice - user's move choice.
*****************************************************************************************/

bool Temple::handleMove(List* leatherBag, Location*& currentLocation, int choice)
{
	switch (choice)
	{
	case 1: 
		
		currentLocation = getNorth();
		return true;

	case 2: 
		
		currentLocation = getEast();
		return true;

	case 3: 
		
		currentLocation = getSouth();
		return true;

	case 4: 
		
		currentLocation = getWest();
		return true;

	default: return false;
	}
}
