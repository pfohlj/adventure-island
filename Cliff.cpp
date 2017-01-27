/*****************************************************************************************
** Program Filename: Cliff.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: Implementation file for the cliff class. See comments preceeding functions
** for more detauls. 
*****************************************************************************************/

#include "Cliff.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: default constructor
** Description: calls Location constructor and sets the value of hook, hookDiscovered, and
** pathCleared.
** Parameters: masterList - pointer to list of game items
*****************************************************************************************/

Cliff::Cliff(List* masterList) :
	Location()
{
	hook = masterList->getItem("Hook");
	setHookDiscovered(false);
	setPathCleared(false);
}

/*****************************************************************************************
** Function: override constructor
** Description: passes 4 location pointers to the Location constructor and sets the values
** of hook, hookDiscovered, and pathCleared
** Parameters: 4 Location pointers and a pointer to a list object
*****************************************************************************************/

Cliff::Cliff(List* masterList, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	hook = masterList->getItem("Hook");
	setHookDiscovered(false);
	setPathCleared(false);
}

/*****************************************************************************************
** Function: destructors
** Description: disconnects hook from the game's array of items and disconnects all 
** location pointers from other Location objects. 
** Parameters: n/a
*****************************************************************************************/

Cliff::~Cliff()
{
	hook = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function:setHookDiscovered
** Description: sets the value of hookDiscovered
** Parameters: hookDiscovered - boolean value
*****************************************************************************************/

void Cliff::setHookDiscovered(bool hookDiscovered)
{
	this->hookDiscovered = hookDiscovered;
}

/*****************************************************************************************
** Function: setPathCleared
** Description: sets the value of pathCleared
** Parameters: pathCleared - boolean value
*****************************************************************************************/

void Cliff::setPathCleared(bool pathCleared)
{
	this->pathCleared = pathCleared;
}

/*****************************************************************************************
** Function: getHookDiscovered
** Description: returns the value of hookDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Cliff::getHookDiscovered() const
{
	return hookDiscovered;
}

/*****************************************************************************************
** Function: getPathCleared
** Description: returns the value of pathCleared
** Parameters: n/a
*****************************************************************************************/

bool Cliff::getPathCleared() const
{
	return pathCleared;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Cliff::describeLocation()
{
	printFile("./text/cliff/look.txt"); 
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Cliff::briefDescription()
{
	printFile("./text/cliff/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Cliff::determineInteraction()
{
	printFile("./text/cliff/interaction.txt");
	int interaction = validateIntRange(1, 3);
	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Cliff::determineMove()
{
	printFile("./text/cliff/move.txt");
	int move = validateIntRange(1, 5);
	return move;
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.  See comments for flow of logic.
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.  
** Boolean value not needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Cliff::handleInteract(List*& leatherBag, bool&, int choice)
{
	switch (choice)
	{
	case 1:
		if (!getHookDiscovered())
		{
			printFile("./text/cliff/newHook.txt");
			setHookDiscovered(true);

			if (leatherBag->listIsFull())
			{
				printFile("./text/inventoryFull.txt");
			}
			else
			{
				leatherBag->addItem(hook);
				std::cout << "Hook ";
				printFile("./text/added.txt");
			}
		}
		else
		{
			if (leatherBag->isAlreadyOnList("Hook"))
			{
				printFile("./text/cliff/rocksNoHook.txt");
			}
			else
			{
				printFile("./text/cliff/oldHook.txt");

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
				}
				else
				{
					leatherBag->addItem(hook);
					std::cout << "Hook ";
					printFile("./text/added.txt");
				}
			}
		}

		return true;

	case 2:

		if (leatherBag->isAlreadyOnList("Rope Ladder"))
		{
			printFile("./text/cliff/loopsAndRopeLadder.txt");
		}
		else
		{
			printFile("./text/cliff/loops.txt");
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

bool Cliff::handleMove(List* leatherBag, Location*& currentLocation, int choice)
{
	switch (choice)
	{
	case 1:

		currentLocation = getNorth();
		return true;

	case 2:

		if (leatherBag->isAlreadyOnList("Rope Ladder"))
		{
			printFile("./text/cliff/climbDownCliff.txt");
			std::cin.get();
			currentLocation = getEast();
		}
		else
		{
			printFile("./text/cliff/cliffNoLadder.txt");
			std::cin.get();
		}

		return true;

	case 3:

		currentLocation = getSouth();
		return true;

	case 4:

		if (!getPathCleared())
		{
			if (leatherBag->isAlreadyOnList("Machete"))
			{
				setPathCleared(true);
				printFile("./text/clearPath.txt");
				std::cin.get();
				currentLocation = getEast();
			}
			else
			{
				std::cin.get();
				printFile("./text/jungleNoAccess.txt");
			}
		}
		else
		{
			currentLocation = getWest();
		}

		return true;

	default: return false;
	}
}
