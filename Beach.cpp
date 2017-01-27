/*****************************************************************************************
** Program Filename: Beach.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Beach class.  For information on
** specific functions, see their preceeding comment blocks.
*****************************************************************************************/

#include "Beach.hpp"
#include "HelperFunctions.hpp"
#include "Island.hpp"
#include <fstream>
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: sets the value of the two boolean members and gets a pointer to the 
** machete Item from the gameItems list it is passed.
** Parameters: gameItems - pointer to the list of game items generated in Island.
*****************************************************************************************/

Beach::Beach(List *gameItems): 
	Location() 
{
	// starts out with path uncleared and machete undiscovered
	setMacheteDiscovered(false);
	setPathCleared(false);

	machete = gameItems->getItem("Machete");
}

/*****************************************************************************************
** Function: override constructor
** Description: passes the four Location pointers it receives to the Location 
** constructor and uses the gameItems pointer to grab a pointer to the machete Item that
** can be gained on this location.
** Parameters: four pointers to Locations indicating the connection Location objects,
** one pointer to the a List containing the Machete object.
*****************************************************************************************/

Beach::Beach(List *gameItems, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	// starts out with path uncleared and machete undiscovered
	setMacheteDiscovered(false);
	setPathCleared(false);

	machete = gameItems->getItem("Machete");
}

/*****************************************************************************************
** Function: destructor
** Description: sets machete to a null value and disconnects the object from any Locations
** it may have been pointing to.
** Parameters: n/a
*****************************************************************************************/

Beach::~Beach()
{
	machete = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: getMacheteDiscovered
** Description: returns the value of macheteDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Beach::getMacheteDiscovered() const
{
	return macheteDiscovered;
}

/*****************************************************************************************
** Function: getPathCleared
** Description: returns the value of pathCleared
** Parameters: n/a
*****************************************************************************************/

bool Beach::getPathCleared() const
{
	return pathCleared;
}

/*****************************************************************************************
** Function: setMacheteDiscovered
** Description: sets macheteDiscovered to the value of the macheteDiscovered parameter
** Parameters: macheteDiscovered - boolean value
*****************************************************************************************/

void Beach::setMacheteDiscovered(bool macheteDiscovered)
{
	this->macheteDiscovered = macheteDiscovered;
}

/*****************************************************************************************
** Function:setPathCleared
** Description: sets pathCleared to the pathCleared parameter
** Parameters: pathCleared - boolean value
*****************************************************************************************/

void Beach::setPathCleared(bool pathCleared)
{
	this->pathCleared = pathCleared;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Beach::describeLocation()
{
	printFile("./text/beach/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

int Beach::determineInteraction()
{
	printFile("./text/beach/interact.txt");
	int interaction = validateIntRange(1, 4);
	return interaction;
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Beach::determineMove()
{
	printFile("./text/beach/move.txt");
	int move = validateIntRange(1, 5);
	return move;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

void Beach::briefDescription()
{
	printFile("./text/beach/brief.txt"); 
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.  See comments for flow of logic.
** Parameters: list - the player's leather bag, unused boolean value, choice - integer 
** indicating the player's choice of interaction
*****************************************************************************************/

bool Beach::handleInteract(List*& list, bool&, int choice)
{
	if (choice == 1)
	{
		printFile("./text/beach/palms.txt");
		return true;
	}
	else if (choice == 2)
	{
		if (list->isAlreadyOnList("Silver Key")) // user already has silver key
		{
			if (list->isAlreadyOnList("Machete")) // user already has machete
			{
				printFile("./text/beach/emptyBox.txt");
				return true;
			}
			else // does not have machete
			{
				if (macheteDiscovered)	// machete previously discovered
				{
					printFile("./text/beach/oldMachete.txt");

					if (list->listIsFull()) // inventory full
					{
						printFile("./text/inventoryFull.txt");
						return true;
					}
					else // room in inventory
					{
						list->addItem(machete);
						std::cout << "Machete ";
						printFile("./text/added.txt");
						return true;
					}
				}
				else // machete not discovered yet
				{
					printFile("./text/beach/newMachete.txt");
					setMacheteDiscovered(true);

					if (list->listIsFull()) // no room in inventory
					{
						printFile("./text/inventoryFull.txt");
						return true;
					}
					else // has room in inventory
					{
						list->addItem(machete);
						std::cout << "Machete ";
						printFile("./text/added.txt");
						return true;
					}
				}
			}
		} // user does not have silver key
		else
		{
			printFile("./text/beach/chestNoKey.txt");
			return true;
		}
	}
	else if (choice == 3)
	{
		printFile("./text/beach/driftWood.txt");
		return true;
	}
	

	return false;
}

/*****************************************************************************************
** Function: handleMove
** Description: accepts the user's choice of movement location and handles that choice
** based on whether the user can or cannot make that move.
** Parameters: list - the user's leather bag, location - the user's currnent location,
** choice - the user's choice of move direction
*****************************************************************************************/

bool Beach::handleMove(List* list, Location*& location, int choice)
{
	switch (choice)
	{
	case 1: 
		
		location = getNorth();
		return true;

	case 2:

		if (!getPathCleared()) // jungle path not cleared yet
		{
			if (list->isAlreadyOnList("Machete")) // user has machete and can clear path
			{
				printFile("./text/clearPath.txt");
				std::cin.get();
				setPathCleared(true);
				location = getEast();
				return true;
			}
			
			// user does not have machete
			printFile("./text/jungleNoAccess.txt");
			std::cin.get();
			return true;
		}

		// path already cleared
		location = getEast();
		return true;

	case 3: 
		
		location = getSouth();
		return true;

	case 4: 
		
		location = getWest();
		return true;
	
	default: return false;
	}
}
