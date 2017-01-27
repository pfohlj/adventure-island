/*****************************************************************************************
** Program Filename:
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Cave class.  For information on 
** specific methods, see their accompanying comment blocks.
*****************************************************************************************/

#include "Cave.hpp"
#include "HelperFunctions.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: initializes the redOrb pointer with the pointer from the masterList
** parameter and then sets the boolean values to a default value of false
** Parameters: masterList - pointer to a list object containing the games available Item
** objects.
*****************************************************************************************/

Cave::Cave(List* masterList) :
	Location()
{
	redOrb = masterList->getItem("Red Orb");
	setPuzzleSolved(false);
	setAllColors(false);
}

/*****************************************************************************************
** Function: Override constructor
** Description: accepts 4 pointers to locations that are passed to the Locaiton constructor.
** also takes a masterList object and uses that to get the redOrb item.
** Parameters: 4 pointers to Locations and a pointer to the list containing the games
** available items
*****************************************************************************************/

Cave::Cave(List* masterList, Location* north = nullptr, Location* east = nullptr, 
	Location* south = nullptr, Location* west = nullptr) :
	Location(north, east, south, west)
{
	redOrb = masterList->getItem("Red Orb");
	setPuzzleSolved(false);
	setAllColors(false);
}

/*****************************************************************************************
** Function: destructor
** Description: sets the Item pointer to a null value and disconnects the object from any
** other Location objects it may be pointing to using disconnectAllPaths.
** Parameters: N/A
*****************************************************************************************/

Cave::~Cave()
{
	redOrb = nullptr;
	disconnectAllPaths();
}

/*****************************************************************************************
** Function:setPuzzleSolved
** Description: sets puzzleSolved to the value of the puzzleSolved parameter
** Parameters: puzzleSolved - boolean value
*****************************************************************************************/

void Cave::setPuzzleSolved(bool puzzleSolved)
{
	this->puzzleSolved = puzzleSolved;
}

/*****************************************************************************************
** Function: setGreenCorrect
** Description: sets greenCorrect to the value of the greenCorrect parameter
** Parameters: greenCorrect -  boolean value
*****************************************************************************************/

void Cave::setGreenCorrect(bool greenCorrect)
{
	this->greenCorrect = greenCorrect;
}

/*****************************************************************************************
** Function: setPurpleCorrect
** Description: sets purpleCorrect to the value of the purpleCorrect parameter
** Parameters: purpleCorrect - boolean value
*****************************************************************************************/

void Cave::setPurpleCorrect(bool purpleCorrect)
{
	this->purpleCorrect = purpleCorrect;
}

/*****************************************************************************************
** Function: setOrangeCorrect
** Description: sets orangeCorrect to the value of the orangeCorrect parameter
** Parameters: orangeCorrect - boolean value
*****************************************************************************************/

void Cave::setOrangeCorrect(bool orangeCorrect)
{
	this->orangeCorrect = orangeCorrect;
}

/*****************************************************************************************
** Function: setYellowCorrect
** Description: sets yellowCorrect to the value of the yellowCorrect parameter
** Parameters: yellowCorrect
*****************************************************************************************/

void Cave::setYellowCorrect(bool yellowCorrect)
{
	this->yellowCorrect = yellowCorrect;
}

/*****************************************************************************************
** Function: setTealCorrect
** Description: sets tealCorrect to the value of the tealCorrect parameter
** Parameters: tealCorret -  boolean value
*****************************************************************************************/

void Cave::setTealCorrect(bool tealCorrect)
{
	this->tealCorrect = tealCorrect;
}

/*****************************************************************************************
** Function: setAllColors
** Description: sets all of the boolean colorCorrect values to the value of the value
** parameter. (don't say that five times fast... o_O )
** Parameters: value - boolean value
*****************************************************************************************/

void Cave::setAllColors(bool value)
{
	setGreenCorrect(value);
	setPurpleCorrect(value);
	setOrangeCorrect(value);
	setYellowCorrect(value);
	setTealCorrect(value);
}

/*****************************************************************************************
** Function: getPuzzlesolved
** Description: returns the value of the puzzleSolved data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getPuzzleSolved() const
{
	return puzzleSolved;
}

/*****************************************************************************************
** Function: getGreenCorrect
** Description: returns the value of the greenCorrect data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getGreenCorrect() const
{
	return greenCorrect;
}

/*****************************************************************************************
** Function: getPurpleCorrect
** Description: returns the value of the purpleCorrect data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getPurpleCorrect() const
{
	return purpleCorrect;
}

/*****************************************************************************************
** Function: getOrangecorrect
** Description: returns the value of the orangeCorrect data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getOrangeCorrect() const
{
	return orangeCorrect;
}

/*****************************************************************************************
** Function:getYellowCorrect
** Description: returns the value of the yellowCorrect data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getYellowCorrect() const
{
	return yellowCorrect;
}

/*****************************************************************************************
** Function: getTealCorrect
** Description: returns the value of the tealCorrect data member
** Parameters: n/a
*****************************************************************************************/

bool Cave::getTealCorrect() const
{
	return tealCorrect;
}

/*****************************************************************************************
** Function: allColorsTrue
** Description:  returns true if all of the colorCorrect data members are true
** Parameters: n/a
*****************************************************************************************/

bool Cave::allColorsTrue() const
{
	if (!getGreenCorrect())
	{
		return false;
	}
	
	if (!getPurpleCorrect())
	{
		return false;
	}
	
	if (!getOrangeCorrect())
	{
		return false;
	}
	
	if (!getYellowCorrect())
	{
		return false;
	}
	
	if (!getTealCorrect())
	{
		return false;
	}
	
	return true;
}

/*****************************************************************************************
** Function: describeLocation
** Description: Prints the file containing a description of the current location to the
** screen.
** Parameters: N/A
*****************************************************************************************/

void Cave::describeLocation()
{
	printFile("./text/cave/look.txt");
}

/*****************************************************************************************
** Function: briefDescription
** Description: prints a file containing a brief description of the location
** Parameters: N/A
*****************************************************************************************/

void Cave::briefDescription()
{
	printFile("./text/cave/brief.txt");
}

/*****************************************************************************************
** Function: determineInteraction
** Description: prints a menu containing the available interactions.  Gets and validates
** the user's input, and then returns that value.
** Parameters: N/A
*****************************************************************************************/

int Cave::determineInteraction()
{
	printFile("./text/cave/interact.txt"); 
	int interact = validateIntRange(1, 4);
	return interact;
}

/*****************************************************************************************
** Function: determineMove
** Description: prints a file containing the available moves, then gets and validates the
** users choice of move.  returns the users choice.
** Parameters: N/A
*****************************************************************************************/

int Cave::determineMove()
{
	printFile("./text/cave/move.txt"); 
	int move = validateIntRange(1, 2);
	return move;
}

/*****************************************************************************************
** Function: handleInteract
** Description: accepts the user's choice of interactin and then handles that choice based
** on the value of the class' private data members.  See comments for flow of logic.
** Parameters: leatherBag - pointer by reference to the adventurer's leather bag.  Boolean 
** value notbneeded here, an integer indicating the user's choice.
*****************************************************************************************/

bool Cave::handleInteract(List*& leatherBag, bool&, int choice)
{
	switch (choice)
	{
	case 1:

		if (getPuzzleSolved()) // user already solved puzzle
		{
			if (leatherBag->isAlreadyOnList("Red Orb")) // already has red orb
			{
				printFile("./text/cave/puzzleNoResponse.txt");
			}
			else // does not have red orb
			{
				printFile("./text/cave/gainOrbNoPuzzle.txt"); 

				if (leatherBag->listIsFull()) // no room in inventory
				{
					printFile("./text/inventoryFull.txt");
					std::cout << std::endl << "Press enter to continue...";
				}
				else // room in inventory
				{
					leatherBag->addItem(redOrb);
					std::cout << "Red Orb ";
					printFile("./text/added.txt");
				}
			}
		}
		else
		{
			if (attemptPuzzle()) // user succeeds at solving puzzle
			{
				printFile("./text/cave/gainOrbAfterPuzzle.txt"); 

				if (leatherBag->listIsFull()) // no room in inventory
				{
					printFile("./text/inventoryFull.txt");
				}
				else // room in inventory
				{
					leatherBag->addItem(redOrb);
					std::cout << "Red Orb ";
					printFile("./text/added.txt");
				}
			} // user failed puzzle
			else // 
			{
				printFile("./text/cave/puzzleFail.txt");
			}
		}
		return true;

	case 2: 

		printFile("./text/cave/skeleton.txt");
		return true;

	case 3:

		printFile("./text/cave/painting.txt");
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

bool Cave::handleMove(List* dummy, Location*& currentLocation, int choice)
{
	switch (choice)
	{
	case 1: 
		currentLocation = getWest();
		return true;
	default: return false;
	}
}

/*****************************************************************************************
** Function: attemptPuzzle
** Description: prompts the user to select the correct colors to place in the numberd holes.
** The colors must be placed in the holes in the sequence green, purple, orange, yellow,
** and teal in order for the player to successfully pass the puzzle.
** Parameters: N/A
*****************************************************************************************/

bool Cave::attemptPuzzle()
{
	int puzzleSelection;

	printFile("./text/cave/puzzleIntro.txt"); 
	std::cin.get();
	system("clear");

	std::cout << "Which color will you use for hole number 1?" << std::endl;
	printFile("./text/cave/puzzleMenu.txt"); 
	puzzleSelection = validateIntRange(1, 5);

	if (puzzleSelection == 4) //  player answered correctly
	{
		setGreenCorrect(true);
		printFile("./text/cave/greenCorrect.txt");
		std::cin.get();
	}

	system("clear");
	std::cout << "Which color will you use for hole number 2?" << std::endl;
	printFile("./text/cave/puzzleMenu.txt"); 
	puzzleSelection = validateIntRange(1, 5);

	if (puzzleSelection == 1) //  player answered correctly
	{
		setPurpleCorrect(true);
		printFile("./text/cave/purpleCorrect.txt");
		std::cin.get();
	}

	system("clear");
	std::cout << "Which color will you use for hole number 3?" << std::endl;
	printFile("./text/cave/puzzleMenu.txt"); 
	puzzleSelection = validateIntRange(1, 5);

	if (puzzleSelection == 3) //  player answered correctly
	{
		setOrangeCorrect(true);
		printFile("./text/cave/orangeCorrect.txt");
		std::cin.get();
	}

	system("clear");
	std::cout << "Which color will you use for hole number 4?" << std::endl;
	printFile("./text/cave/puzzleMenu.txt"); 
	puzzleSelection = validateIntRange(1, 5);

	if (puzzleSelection == 2) // yellow
	{
		setYellowCorrect(true);
		printFile("./text/cave/yellowCorrect.txt"); 
		std::cin.get();
	}

	system("clear");
	std::cout << "Which color will you use for hole number 5?" << std::endl;
	printFile("./text/cave/puzzleMenu.txt");
	puzzleSelection = validateIntRange(1, 5);

	if (puzzleSelection == 5) //  player answered correctly
	{
		setTealCorrect(true);
		printFile("./text/cave/tealCorrect.txt"); 
		std::cin.get();
		system("clear");
	}

	if (allColorsTrue()) // user answered all correctly
	{
		setPuzzleSolved(true);
		return true;
	}

	// user did not answer all correctly
	setAllColors(false);
	return false;
}
