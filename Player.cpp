/*****************************************************************************************
** Program Filename: Player.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Player class.  For information on 
** specific functions, please see the leading comment block.
*****************************************************************************************/

#include "Player.hpp"
#include "HelperFunctions.hpp"
#include <iostream>
#include <fstream>

/*****************************************************************************************
** Function: constructor
** Description: sets leatherBag and currentLocation to null values
** Parameters: n/a
*****************************************************************************************/

Player::Player()
{
	leatherBag = nullptr;
	currentLocation = nullptr;
}

/*****************************************************************************************
** Function: constructor
** Description: sets leather bag to a new List of 5 objects and currentLocatioin to the 
** value of the passed parameter
** Parameters: startingLocation - pointer to a Location
*****************************************************************************************/

Player::Player(Location* startingLocation)
{
	leatherBag = new List(5);
	currentLocation = startingLocation;
}

/*****************************************************************************************
** Function: destructor
** Description: deallocates any memory allocated for pointer objects and disconnects those
** that are connected to the Island's pointers.
** Parameters: n/a
*****************************************************************************************/

Player::~Player()
{
	leatherBag->setAllToNull();

	if (leatherBag != nullptr)
	{
		delete leatherBag;
		leatherBag = nullptr;
	}
	
	currentLocation = nullptr;
}

/*****************************************************************************************
** Function: addToBag
** Description: adds the parameter to the player's bag
** Parameters: itemToAdd - pointer to the itemBeing added.
*****************************************************************************************/

void Player::addToBag(Item* itemToAdd)
{
	leatherBag->addItem(itemToAdd);
}

/*****************************************************************************************
** Function: removeFromBag
** Description: Prompts the user to select an object to remove and then removes that 
** item from teh user's bag.
** Parameters: n/a
*****************************************************************************************/

void Player::removeFromBag()
{
	system("clear");
	displayBagContents();
	std::cout << "Which item would you like to remove?" << std::endl;
	
	int numElements = leatherBag->getNumElements();

	int itemNumber = validateIntRange(1, numElements);
	itemNumber--;

	Item *tempItem = leatherBag->getItem(itemNumber);
	std::string tempString = tempItem->getName();

	leatherBag->removeItem(tempString);
	std::cout << tempString << " removed from bag." << std::endl << std::endl;
	std::cout << "Press enter to continue...";
	std::cin.get();

	tempItem = nullptr;
}

/*****************************************************************************************
** Function: getLeatherBag
** Description: returns a pointer to the user's bag
** Parameters: n/a
*****************************************************************************************/

List* Player::getLeatherBag() const
{
	return leatherBag;
}

/*****************************************************************************************
** Function: getCurrentLocation
** Description: returns currentLocation
** Parameters: n/a
*****************************************************************************************/

Location* Player::getCurrentLocation() const
{
	return currentLocation;
}

/*****************************************************************************************
** Function: look
** Description: calls the describeLocation method of the player's current location
** Parameters: n/a
*****************************************************************************************/

void Player::look()
{
	system("clear");
	currentLocation->describeLocation();
	std::cin.get();
}

/*****************************************************************************************
** Function: interact
** Description: gets the user's desired interaction and then passes that choice to the 
** location's handler method.  Once completed, returns the player to the main menu.
** Parameters: gameOver - game state boolean
*****************************************************************************************/

bool Player::interact(bool &gameOver)
{
	bool playerInteracted;
	system("clear");
	int interactionChoice = currentLocation->determineInteraction();
	system("clear");
	playerInteracted = currentLocation->handleInteract(leatherBag, gameOver, interactionChoice);

	if (playerInteracted)
	{
		std::cin.get();
	}

	return playerInteracted;
}

/*****************************************************************************************
** Function: move
** Description: gets the players imput for desired moves and passes that to teh current
** location's handler method, returning whetehr or not the player actually moved.
** Parameters: n/a
*****************************************************************************************/

bool Player::move()
{
	bool playerMoved;
	system("clear");
	int moveChoice = currentLocation->determineMove();
	system("clear");
	playerMoved = currentLocation->handleMove(leatherBag, currentLocation, moveChoice);
	return playerMoved;
}

/*****************************************************************************************
** Function: viewManage inventory
** Description: allows the user to view their current inventory and if they so desire,
** remove and objecdt from their inventory
** Parameters: n/a
*****************************************************************************************/

void Player::viewManageInventory()
{
	system("clear");

	if (leatherBag->getNumElements() != 0)
	{
		displayBagContents();

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Remove an item." << std::endl;
		std::cout << "2. Return to menu." << std::endl;

		int playerChoice = validateIntRange(1, 2);

		if (playerChoice == 1)
		{
			removeFromBag();
		}
	}
	else
	{
		std::cout << "Nothing in inventory." << std::endl << std::endl;
		std::cout << "Press enter to continue...";
		std::cin.get();
	}

	
}

/*****************************************************************************************
** Function: quit
** Description: changes the gameOver state to a true, ending the game
** Parameters: gameOver - reference value of gameOver boolean value
*****************************************************************************************/

void Player::quit(bool &gameOver)
{
	gameOver = true;
}

/*****************************************************************************************
** Function: displayActions
** Description: prints the actions the user can choose from
** Parameters: n/a
*****************************************************************************************/

void Player::displayActions() const
{
	printFile("./text/actions.txt");
}

/*****************************************************************************************
** Function: displayBagContents
** Description: display's the contents of the user's bag
** Parameters: n/a
*****************************************************************************************/

void Player::displayBagContents() const
{
	leatherBag->displayList();
}

/*****************************************************************************************
** Function: doTurn
** Description: gets the user's desired action choice and then passes control to the
** appropriate method for handling that choice.
** Parameters: gameOver - passed on to the appropriate handler methods, made - boolean
** indicating something has been done, remaining - number of turns remaining
*****************************************************************************************/

bool Player::doTurn(bool &gameOver, int made, int remaining)
{
	ActionChoice choice;
	bool playerDidSomething;

	system("clear");
	currentLocation->briefDescription();

	std::cout << std::endl << "Actions used: " << made << "   Actions remaining: " << remaining << std::endl;

	displayActions();	
	choice = getPlayerActionChoice();

	switch (choice)
	{
	case Look: 

		look();
		return false;

	case Interact: 

		playerDidSomething =  interact(gameOver);
		return playerDidSomething;

	case Move: 
		
		playerDidSomething =  move();
		return playerDidSomething;

	case ManageInventory: 
		
		viewManageInventory();
		return false;

	case Quit:
		quit(gameOver);
		return false;
	}

	throw INVALID_PATH_TAKEN();
}

/*****************************************************************************************
** Function: getPlayerActionChoice
** Description: gets the user's input and returns the appropriate ActionChoice data
** type.
** Parameters: n/a
*****************************************************************************************/

ActionChoice Player::getPlayerActionChoice()
{
	ActionChoice playersChoice;

	int choice = validateIntRange(1, 5);

	switch (choice)
	{
	case 1: 
		
		playersChoice = Look;
		break;

	case 2: 
		
		playersChoice = Interact;
		break;

	case 3: 
		
		playersChoice = Move;
		break;

	case 4: 
		
		playersChoice = ManageInventory;
		break;

	default: 

		playersChoice = Quit;
	}

	return playersChoice;
}
