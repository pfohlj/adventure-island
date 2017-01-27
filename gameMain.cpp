/*****************************************************************************************
** Program Filename: gameMain.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This file contains the main method for the whole game.  It relies on the
** GameManager class to control the games execution.
*****************************************************************************************/

#include "GameManager.hpp"

/*****************************************************************************************
** Function: main
** Description: main function of the whole game
** Parameters: n/a
*****************************************************************************************/

int main()
{
	GameManager game;
	game.run();
	
	return 0;
}
