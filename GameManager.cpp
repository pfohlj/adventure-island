/*****************************************************************************************
** Program Filename: GameManager.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the GameManager class.  For information
** on individual methods, see their corresponding header block.
*****************************************************************************************/

#include "GameManager.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: sets the value of quieGame and gameIsland
** Parameters: N/a
*****************************************************************************************/

GameManager::GameManager()
{
	setQuitGame(false);
	gameIsland = nullptr;
}

/*****************************************************************************************
** Function: destructor
** Description: ensures that any memory allocated for gameIsland is freed
** Parameters: n/a
*****************************************************************************************/

GameManager::~GameManager()
{
	if (gameIsland != nullptr)
	{
		delete gameIsland;
		gameIsland = nullptr;
	}
}

/*****************************************************************************************
** Function: setQuitGame
** Description: sets the value of quitGame
** Parameters: quitGame - boolean value
*****************************************************************************************/

void GameManager::setQuitGame(bool quitGame)
{
	this->quitGame = quitGame;
}

/*****************************************************************************************
** Function: getQuitGame
** Description: retunrns the value of quitGame
** Parameters: N/a
*****************************************************************************************/

bool GameManager::getQuitGame() const
{
	return quitGame;
}

/*****************************************************************************************
** Function: run
** Description: loops through the main menu, handling the user's selection, until the user
** opts to quit.
** Parameters: n/a
*****************************************************************************************/

void GameManager::run()
{
	while (!getQuitGame())
	{
		int choice = getMenuChoice();
		handleMenuChoice(choice);
	}
}

/*****************************************************************************************
** Function: getMenuChoice
** Description: prompts the user to select a value from the main menu, gets and validates
** that choice, and return teh value
** Parameters: n/a
*****************************************************************************************/

int GameManager::getMenuChoice()
{
	system("clear");
	printFile("./text/game/mainMenu.txt");
	int choice = validateIntRange(1, 4);
	return choice;
}

/*****************************************************************************************
** Function: handleMenuchoice
** Description: directs the program to execute the proper function based on the user's 
** selection
** Parameters: choice - the user's choice from the menu
*****************************************************************************************/

void GameManager::handleMenuChoice(int choice)
{
	switch (choice)
	{
	case 1: 

		play();
		break;

	case 2: 

		instructions();
		break;

	case 3: 

		cheat();
		break;

	case 4: 

		quit();
		break;

	}
}

/*****************************************************************************************
** Function: play
** Description: creates a new Island object and repeats the doTurn method of that object
** until an end game state is reached as indicated by the Island's gameOver member.
** Parameters: N/a
*****************************************************************************************/

void GameManager::play()
{
	gameIsland = new Island;

	system("clear");
	printFile("./text/gameIntro.txt");
	std::cin.get();

	while (!gameIsland->getGameOver()) // while the game is not over
	{
		gameIsland->doTurn();
	}

	delete gameIsland; // free memory
	gameIsland = nullptr;
}

/*****************************************************************************************
** Function: instructions
** Description: prints the game's instructions
** Parameters: n/a
*****************************************************************************************/

void GameManager::instructions()
{
	system("clear");
	printFile("./text/game/instructions.txt");
	std::cin.get();
}

/*****************************************************************************************
** Function: cheat
** Description: prints a cheat that shows a step by step guide to winning the game.
** Parameters: n/a
*****************************************************************************************/

void GameManager::cheat()
{
	system("clear");
	printFile("./text/game/cheat.txt");
	std::cin.get();
}

/*****************************************************************************************
** Function: quit
** Description: sets the quitGame value to end the run loop
** Parameters: n/a
*****************************************************************************************/

void GameManager::quit()
{
	setQuitGame(true);
}
