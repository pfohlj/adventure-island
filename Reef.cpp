/*****************************************************************************************
** Program Filename: Reef.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Reef class.  For information on a
** specific function, please see its preceeding comment block.
*****************************************************************************************/

#include "Reef.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: calls the Location constructor and sets the value of goldKeyDiscovered and
** goldKey.
** Parameters:
*****************************************************************************************/

Reef::Reef(List* gameItems) :
	Location()
{
	setGoldKeyDiscovered(false);
	goldKey = gameItems->getItem("Gold Key");
}

/*****************************************************************************************
** Function: overload constructor
** Description: passes 4 Location pointers to the Location constructor and sets the value
** of goldKeyDiscovered and goldKey.
** Parameters: 4 pointers to locations and a pointer to the game's master list of items.
*****************************************************************************************/

Reef::Reef(List* gameItems, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	setGoldKeyDiscovered(false);
	goldKey = gameItems->getItem("Gold Key");
}

/*****************************************************************************************
** Function: destructor
** Description: disconnects all of the reef's pointer variables from other objects.
** Parameters: n/a
*****************************************************************************************/

Reef::~Reef()
{
	goldKey = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function: getGoldKeyDiscovered
** Description: returns value of goldKeyDiscovered
** Parameters: n/a
*****************************************************************************************/

bool Reef::getGoldKeyDiscovered() const
{
	return goldKeyDiscovered;
}

/*****************************************************************************************
** Function: setGoldKeyDiscovered
** Description: sets value of goldKeyDiscovered
** Parameters: goldKeyDiscovered - boolean value
*****************************************************************************************/

void Reef::setGoldKeyDiscovered(bool goldKeyDiscovered)
{
	this->goldKeyDiscovered = goldKeyDiscovered;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Reef::describeLocation()
{
	printFile("./text/reef/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Reef::briefDescription()
{
	printFile("./text/reef/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Reef::determineInteraction()
{
	printFile("./text/reef/interact.txt");
	int interaction = validateIntRange(1, 4);
	return interaction;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Reef::determineMove()
{
	printFile("./text/reef/move.txt");
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

bool Reef::handleInteract(List*& list, bool&, int choice)
{
	switch (choice)
	{
	case 1:

		if (list->isAlreadyOnList("String") &&
			list->isAlreadyOnList("Hook"))
		{
			if (list->isAlreadyOnList("Gold Key"))
			{
				printFile("./text/reef/fishNoKey.txt");
				return true;
			}
			else
			{
				if (goldKeyDiscovered)
				{
					printFile("./text/reef/oldGoldKey.txt");

					if (list->listIsFull())
					{
						printFile("./text/inventoryFull.txt");
						return true;
					}
					else
					{
						list->addItem(goldKey);
						std::cout << "Gold Key ";
						printFile("./text/added.txt");
						return true;
					}
				}
				else
				{
					printFile("./text/reef/newGoldKey.txt");
					setGoldKeyDiscovered(true);

					if (list->listIsFull())
					{
						printFile("./text/inventoryFull.txt");
						return true;
					}
					else
					{
						list->addItem(goldKey);
						std::cout << "Gold Key ";
						printFile("./text/added.txt");
						return true;
					}
				}
			}
		}
		else
		{
			printFile("./text/reef/noFish.txt");
			return true;
		}

	case 2:
		
		printFile("./text/reef/floatingBottle.txt");
		return true;

	case 3:

		printFile("./text/reef/seaweed.txt");
		return true;

	default:

		return false;
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

bool Reef::handleMove(List* dummy, Location*& currentLocation, int choice)
{
	if (choice == 1)
	{
		currentLocation = getEast();
		return true;
	}

	return false;
}
