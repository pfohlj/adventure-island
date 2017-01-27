/*****************************************************************************************
** Program Filename: Player.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: this is the interface file for the Player class.  For information on
** specific data members and functions, please see their comments and the file Player.cpp.
*****************************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "List.hpp"
#include "Location.hpp"

// user's choice of action
enum ActionChoice { Look, Interact, Move, ManageInventory, Quit };

// exception class
class INVALID_PATH_TAKEN {};

class Player
{
private:

	List *leatherBag; // pointer to the Player's bag of Items (inventory)
	Location *currentLocation; // pointer to the player's current location

public:

	// constructor & destructor
	Player();
	Player(Location*);
	~Player();

	// inventory manipulation
	void addToBag(Item*);
	void removeFromBag();
	List* getLeatherBag() const;
	Location* getCurrentLocation() const;

	// gameplay methods
	void look();
	bool interact(bool&);
	bool move();
	void viewManageInventory();
	void quit(bool&);

	// display methods
	void displayActions() const;		
	void displayBagContents() const;

	// management methods
	bool doTurn(bool&, int, int);

	// user input methods
	ActionChoice getPlayerActionChoice();
};

#endif // !PLAYER_HPP
