/*****************************************************************************************
** Program Filename: HelperFunctions.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for two helper functions to greatly 
** simplify the execution of the other game files.  See the comment blocks of the 
** associated functions for more info.
*****************************************************************************************/

#include "HelperFunctions.hpp"
#include <iostream>
#include <fstream>

/*****************************************************************************************
** Function: printfile
** Description: opens a file for reading and prints the values read, character by character,
** to the screen until the EOF is reached.  Closes the file.
** Parameters: a string indicating the location of the file to read from.
*****************************************************************************************/

void printFile(std::string location)
{
	char temp;
	std::ifstream in(location);

	in.get(temp);

	while (!in.fail())
	{
		std::cout << temp;
		in.get(temp);
	}

	in.close();
}

/*****************************************************************************************
** Function: validate int range
** Description: prompts the user to input an integer that is inclusively between min and
** max.  Loops until the user correctly enter's input and then return that value.
** Parameters: min - the minumum value the numebr can be, max - the largest the number can
** be.
*****************************************************************************************/

int validateIntRange(int min, int max)
{
	int temp;
	std::cin >> std::noskipws;
	std::cout << "Make a selection: ";

	while (1)
	{
		if (std::cin >> temp &&
			temp >= min &&
			temp <= max )
		{
			std::cin.ignore(100, '\n');
			break;
		}

		std::cout << "Invalid input. Make a selection: ";

		std::cin.clear();
		std::cin.ignore(100, '\n');
	}

	return temp;
}
