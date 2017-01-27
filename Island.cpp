/*****************************************************************************************
** Program Filename: Island.cpp 
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Island class.  For more information
** on speicfic methods, please see the corresponding header documents.
*****************************************************************************************/

#include "Island.hpp"
#include "Beach.hpp"
#include "Reef.hpp"
#include "Hut.hpp"
#include "Basement.hpp"
#include "Cliff.hpp"
#include "Cave.hpp"
#include "Ruins.hpp"
#include "Dungeon.hpp"
#include "Clearing.hpp"
#include "HelperFunctions.hpp"
#include <iostream>
#include "Temple.hpp"

/*****************************************************************************************
** Function: constructor
** Description: creates a new list item to store the available items, fills that list with
** items, builds the island, creates the player, and then sets the value of movesMade, 
** movesRemaining, gameOver, and templeAdded.
** Parameters: n/a
*****************************************************************************************/

Island::Island()
{
	gameItems = new List(8);
	fillGameItems();
	startingLocation = buildIsland();
	adventurer = new Player(startingLocation);
	setMovesMade(0);
	setMovesRemaining(100);
	setGameOver(false);
	setTempleAdded(false);
}

/*****************************************************************************************
** Function: destructor
** Description: frees the memory allocated for adventurer and gameItems.  Calls 
** destroyIsland to free the memory allocated for each of the various Location objects.
** Parameters: n/a
*****************************************************************************************/

Island::~Island()
{
	delete adventurer;
	delete gameItems;
	startingLocation = nullptr;

	destroyIsland();
}

/*****************************************************************************************
** Function: setMovesMade
** Description: sets the value of movesMade
** Parameters: movesMade - integer value
*****************************************************************************************/

void Island::setMovesMade(int movesMade)
{
	this->movesMade = movesMade;
}

/*****************************************************************************************
** Function: setMovesRemaining
** Description: sets the value of movesRemaining
** Parameters: movesRemaining - integer value
*****************************************************************************************/

void Island::setMovesRemaining(int movesRemaining)
{
	this->movesRemaining = movesRemaining;
}

/*****************************************************************************************
** Function: setGameOver
** Description: sets the value of gameOver
** Parameters: gameOver - boolean value
*****************************************************************************************/

void Island::setGameOver(bool gameOver)
{
	this->gameOver = gameOver;
}

/*****************************************************************************************
** Function: setTempleAdded
** Description: sets the value of templeAdded
** Parameters: templeAdded - boolean value
*****************************************************************************************/

void Island::setTempleAdded(bool templeAdded)
{
	this->templeAdded = templeAdded;
}

/*****************************************************************************************
** Function: getTempleAdded
** Description: returns the value of templeAdded
** Parameters: n/a
*****************************************************************************************/

bool Island::getTempleAdded()
{
	return templeAdded;
}

/*****************************************************************************************
** Function: getGameOver
** Description: returns the value of gameOver
** Parameters: n/a
*****************************************************************************************/

bool Island::getGameOver() const
{
	return gameOver;
}

/*****************************************************************************************
** Function: getMovesMade
** Description: returns the value of movesMade
** Parameters: n/a
*****************************************************************************************/

int Island::getMovesMade() const
{
	return movesMade;
}

/*****************************************************************************************
** Function: getMovesRemaining
** Description: returns the value of movesRemaining
** Parameters:
*****************************************************************************************/

int Island::getMovesRemaining() const
{
	return movesRemaining;
}

/*****************************************************************************************
** Function: doTurn
** Description: calls the doTurn method of the adventurer object.  If the player did 
** something, movesMade and movesRemaining are incremented.  If the player gained the blue
** orb, the addTemple method is called.  If the player runs out of moves, the game is 
** ended.
** Parameters: n/a
*****************************************************************************************/

void Island::doTurn()
{
	List *tempList = adventurer->getLeatherBag();
	bool startWithBlueOrb = tempList->isAlreadyOnList("Blue Orb");

	bool incrementTurn = adventurer->doTurn(gameOver, getMovesMade(), getMovesRemaining());

	if (incrementTurn) // player did something
	{
		setMovesMade(getMovesMade() + 1);
		setMovesRemaining(getMovesRemaining() - 1);
	}

	if (!startWithBlueOrb &&
		tempList->isAlreadyOnList("Blue Orb"))  // player gained Blue Orb this turn
	{
		addTemple();
	}

	tempList = nullptr;

	if (getMovesRemaining() == 0) // player ran out of turns
	{
		setGameOver(true);
		system("clear");
		printFile("./text/noMoreActions.txt");
	}

	Location *tempLocation = adventurer->getCurrentLocation();

	if (getTempleAdded() &&
		tempLocation == gameLocations[6]) // temple was added and player just emerged from the dungeon
	{
		printFile("./text/islandAddTemple.txt");
		std::cin.get();
		setTempleAdded(false);
	}
}

/*****************************************************************************************
** Function: buildIsland
** Description: creates 9 new Location objects, storing them in a dynamically allocated 
** array.  Links each of these arrays together to create a navigable structure within which
** to hold the game. 
** Parameters: n/a
*****************************************************************************************/

Location* Island::buildIsland() 
{
	gameLocations = new Location*[9];
	gameLocations[0] = new Beach(gameItems);
	gameLocations[1] = new Reef(gameItems);
	gameLocations[2] = new Hut(gameItems);
	gameLocations[3] = new Basement(gameItems);
	gameLocations[4] = new Cliff(gameItems);
	gameLocations[5] = new Cave(gameItems);
	gameLocations[6] = new Ruins();
	gameLocations[7] = new Dungeon(gameItems);
	gameLocations[8] = new Clearing(gameItems);

	gameLocations[0]->setAllPaths(gameLocations[2], gameLocations[8], gameLocations[6], gameLocations[1]);
	gameLocations[1]->setAllPaths(nullptr, gameLocations[0], nullptr, nullptr);
	gameLocations[2]->setAllPaths(gameLocations[3], gameLocations[4], gameLocations[8], gameLocations[0]);
	gameLocations[3]->setAllPaths(nullptr, nullptr, gameLocations[2], nullptr);
	gameLocations[4]->setAllPaths(gameLocations[2], gameLocations[5], gameLocations[6], gameLocations[8]);
	gameLocations[5]->setAllPaths(nullptr, nullptr, nullptr, gameLocations[4]);
	gameLocations[6]->setAllPaths(gameLocations[8], gameLocations[4], gameLocations[7], gameLocations[0]);
	gameLocations[7]->setAllPaths(gameLocations[6], nullptr, nullptr, nullptr);
	gameLocations[8]->setAllPaths(gameLocations[2], gameLocations[4], gameLocations[6], gameLocations[0]);

	return gameLocations[0];
}

/*****************************************************************************************
** Function: fillGameItems
** Description: adds the game's 8 required objects to the gameItems List object
** Parameters: n/a
*****************************************************************************************/

void Island::fillGameItems() const
{
	gameItems->add_createItem("String");
	gameItems->add_createItem("Hook");
	gameItems->add_createItem("Gold Key");
	gameItems->add_createItem("Silver Key");
	gameItems->add_createItem("Machete");
	gameItems->add_createItem("Rope Ladder");
	gameItems->add_createItem("Red Orb");
	gameItems->add_createItem("Blue Orb");
}

/*****************************************************************************************
** Function: destroyIsland
** Description: frees the dynamically allocated memory used for the gameLocations array
** Parameters: n/a
*****************************************************************************************/

void Island::destroyIsland() 
{
	for (int i = 0; i < 9; i++)
	{
		delete gameLocations[i];
	}

	delete[] gameLocations;
}

/*****************************************************************************************
** Function: addTemple
** Description: deletes the center clearing and in its place, creates a Temple object,
** with all of the same connections the clearing did.
** Parameters: n/a
*****************************************************************************************/

void Island::addTemple()
{
	gameLocations[8]->disconnectAllPaths();
	delete gameLocations[8];

	gameLocations[8] = new Temple();
	gameLocations[8]->setAllPaths(gameLocations[2], gameLocations[4], gameLocations[6], gameLocations[0]);
	gameLocations[0]->setEast(gameLocations[8]);
	gameLocations[2]->setSouth(gameLocations[8]);
	gameLocations[4]->setWest(gameLocations[8]);
	gameLocations[6]->setNorth(gameLocations[8]);

	setTempleAdded(true);
}
