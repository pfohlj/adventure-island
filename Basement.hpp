/*****************************************************************************************
** Program Filename: Basement.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface for the Basement class.  Basement is a child of the 
** Location class. For information on individual data members and methods, see the 
** comments here, or in the companion file, Basement.cpp
*****************************************************************************************/

#ifndef BASEMENT_HPP
#define BASEMENET_HPP
#include "Location.hpp"
#include <string>

class Basement : public Location
{
private:

	Item * silverKey;		// pointer to the Silver Key item that can be gained in Basement
	int numRiddlesSolved;   // keeps track of the number of riddles solved
	bool completedRiddles;	// indicates whether user has completed all 3 required riddles
	bool attemptedRiddles;	// indicates whether use has attempted to solve the riddles

	std::string riddleFiles[10];	// array of riddle file names for random selection
	int riddleAnswers[10];			// corresponding array to riddleFiles containing correct answer
	int *usedRiddles;				// pointer to be used to create an array for tracking those
									// riddles that have already been used.

public:

	// constructors & destructor
	Basement(List*);
	Basement(List*, Location*, Location*, Location*, Location*);
	~Basement();

	// set methods
	void setNumRiddlesSolved(int);
	void setCompletedRiddles(bool);
	void setAttemptedRiddles(bool);

	// get methods
	int getNumRiddlesSolved() const;
	bool getCompletedRiddles() const;
	bool getAttemptedRiddles() const;

	/* overrides of pure virtual methods from Location class */

	// display methods
	void describeLocation() override;
	void briefDescription() override;

	// interaction methods
	int determineInteraction() override;
	int determineMove() override;

	// handler methods
	bool handleInteract(List*&, bool&, int) override;
	bool handleMove(List*, Location*&, int) override;

private:

	// methods only called by public methods of class.
	void setupRiddleArrays();
	bool attemptRiddles();
};

#endif // !BASEMENT_HPP