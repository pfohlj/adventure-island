/*****************************************************************************************
** Program Filename:
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Cave class, a derived child of the 
** Location class.  For information on specific data members and functions, see their 
** comments or the companion file, Cave.cpp.
*****************************************************************************************/

#ifndef CAVE_HPP
#define CAVE_HPP
#include "Location.hpp"

// used to indicate the user's choice of color for the puzzle
enum Rock { Green, Purple, Orange, Yellow, Teal };

class Cave : public Location
{
private:

	Item *redOrb; // pointer to the Red Orb object that can be gained on this location

	// boolean values used for interaction and movement
	bool puzzleSolved;
	bool greenCorrect;
	bool purpleCorrect;
	bool orangeCorrect;
	bool yellowCorrect;
	bool tealCorrect;

public:

	// constructors & destructor
	Cave(List*);
	Cave(List*, Location*, Location*, Location*, Location*);
	~Cave();

	// set methods
	void setPuzzleSolved(bool);
	void setGreenCorrect(bool);
	void setPurpleCorrect(bool);
	void setOrangeCorrect(bool);
	void setYellowCorrect(bool);
	void setTealCorrect(bool);
	void setAllColors(bool);

	// get methods
	bool getPuzzleSolved() const;
	bool getGreenCorrect() const;
	bool getPurpleCorrect() const;
	bool getOrangeCorrect() const;
	bool getYellowCorrect() const;
	bool getTealCorrect() const;
	bool allColorsTrue() const;

	/* Overrides of pure virtual methods from Location parent class */

	// display methods
	void describeLocation() override;
	void briefDescription() override;

	// interaction methods
	int determineInteraction() override;
	int determineMove() override;

	// handler methods
	bool handleInteract(List*&, bool&, int) override;
	bool handleMove(List*, Location*&, int) override;

	// puzzle method
	bool attemptPuzzle();
};

#endif // !CAVE_HPP
