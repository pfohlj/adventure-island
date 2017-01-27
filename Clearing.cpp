/*****************************************************************************************
** Program Filename: Clearing.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Clearing class. 
*****************************************************************************************/

#include "Clearing.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: default constructor
** Description: calls default Location constructor and sets value sof ropeLadder and 
** ropeLadderDiscovered
** Parameters: pointer to a List object
*****************************************************************************************/

Clearing::Clearing(List* masterList) :
	Location()
{
	ropeLadder = masterList->getItem("Rope Ladder");
	setRopeLadderDiscovered(false);
}

/*****************************************************************************************
** Function: override constructor
** Description: passes the Location constructor the value of four Location pointers.  
** Sets the ropeLadder data member and ropeLadderDiscovered
** Parameters: 4 pointers to Location objects and a pointer to a List object
*****************************************************************************************/

Clearing::Clearing(List* masterList, Location* north = nullptr, Location* east = nullptr,
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	ropeLadder = masterList->getItem("Rope Ladder");
	setRopeLadderDiscovered(false);
}

/*****************************************************************************************
** Function: destructor
** Description: disconnects object from any Locations it points to and disconnects 
** ropeLadder from the array of game items.
** Parameters: N/a
*****************************************************************************************/

Clearing::~Clearing()
{
	ropeLadder = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: setRopeLadderDiscovered
** Description: sets the value of ropeLadderDiscovered
** Parameters: ropeLadderDiscovered - boolean value
*****************************************************************************************/

void Clearing::setRopeLadderDiscovered(bool ropeLadderDiscovered)
{
	this->ropeLadderDiscovered = ropeLadderDiscovered;
}

/*****************************************************************************************
** Function:getRopeLadderDiscovered
** Description: gets value of ropeLadderDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Clearing::getRopeLadderDiscovered() const
{
	return ropeLadderDiscovered;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Clearing::describeLocation()
{
	printFile("./text/clearing/look.txt"); 
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Clearing::briefDescription()
{
	printFile("./text/clearing/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Clearing::determineInteraction()
{
	printFile("./text/clearing/interaction.txt");
	int interaction = validateIntRange(1, 3);
	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Clearing::determineMove()
{
	printFile("./text/clearing/move.txt");
	int move = validateIntRange(1, 5);
	return move;
}

/*****************************************************************************************
** Function: handleInteraction
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.  
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.  Boolean 
** value not needed here, an integer indicating the user's choice.
*****************************************************************************************/

bool Clearing::handleInteract(List*& leatherBag, bool&, int choice)
{
	switch (choice)
	{
	case 1:
		
		printFile("./text/clearing/totem.txt");
		return true;

	case 2:

		if (getRopeLadderDiscovered())
		{
			if (leatherBag->isAlreadyOnList("Rope Ladder"))
			{
				printFile("./text/clearing/emptyBox.txt");
			}
			else
			{
				printFile("./text/clearing/oldRopeLadder.txt"); 

				if (leatherBag->listIsFull())
				{
					printFile("./text/inventoryFull.txt");
				}
				else
				{
					leatherBag->addItem(ropeLadder);
					std::cout << "Rope Ladder ";
					printFile("./text/added.txt");
				}
			}
		}
		else
		{
			printFile("./text/clearing/newRopeLadder.txt");

			if (leatherBag->listIsFull())
			{
				printFile("./text/inventoryFull.txt");
			}
			else
			{
				leatherBag->addItem(ropeLadder);
				std::cout << "Rope Ladder ";
				printFile("./text/added.txt");
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

bool Clearing::handleMove(List* dummy, Location*& currentLocation, int choice)
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
