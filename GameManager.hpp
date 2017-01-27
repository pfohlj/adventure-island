/*****************************************************************************************
** Program Filename: GameManager.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the GameManager class.  For information on
** individual data members of functions, please see their corresponding comments.
*****************************************************************************************/

#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP
#include "Island.hpp"

class GameManager
{
private:

	Island *gameIsland; // pointer to an Island object.  Used for creating new games.
	bool quitGame;		// tracks whether use has quit the game.

public:

	// constructor & destructor
	GameManager();
	~GameManager();

	// get & set method
	void setQuitGame(bool);
	bool getQuitGame() const;

	// game management methods
	void run();

private:

	// methods that are called by run and other sub functions
	int getMenuChoice();
	void handleMenuChoice(int);
	void play();
	void instructions();
	void cheat();
	void quit();
};

#endif // !GAME_MANAGER_HPP