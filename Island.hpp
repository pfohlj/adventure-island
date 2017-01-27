/*****************************************************************************************
** Program Filename: Island.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Island class. For information on 
** specific data members and methods, please see their corresponding comment blocks or the
** companion document Island.cpp.
*****************************************************************************************/

#ifndef ISLAND_HPP
#define ISLAND_HPP

#include "Player.hpp"
#include "Location.hpp"
#include "List.hpp"

class Island
{
private:

	Location *startingLocation; // pointer to the player's starting location
	Location **gameLocations;   // array of game locations

	List *gameItems;			// list of available items in the game
	Player *adventurer;			// pointer to the player

	int movesMade;				// tracks number of moves made
	int movesRemaining;			// tracks moves remaining

	bool gameOver;				// track game over state
	bool templeAdded;			// keep track of add / delete action

public:

	// constructors & destructor
	Island();
	~Island();

	// set methods
	void setMovesMade(int);
	void setMovesRemaining(int);
	void setGameOver(bool);
	void setTempleAdded(bool);

	// get methods
	int getMovesMade() const;
	int getMovesRemaining() const;
	bool getGameOver() const;
	bool getTempleAdded();

	// game management methods
	void doTurn();

private:

	// functions used by constructor / destructor
	Location* buildIsland();
	void fillGameItems() const;
	void destroyIsland();
	void addTemple();
};

#endif // !ISLAND_HPP