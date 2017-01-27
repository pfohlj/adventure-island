/*****************************************************************************************
** Program Filename: Clearing.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Clearing class.  For information on 
** individual data members or functions, please see their comments of the accompanying 
** Clearing.cpp file.
*****************************************************************************************/

#ifndef CLEARING_HPP
#define CLEARING_HPP
#include "Location.hpp"

class Clearing : public Location
{
private:

	Item *ropeLadder; // pointer to the rope ladder Item that can be gained on this Location

	bool ropeLadderDiscovered;

public:

	// constructors & destructor
	Clearing(List*);
	Clearing(List*, Location*, Location*, Location*, Location*);
	~Clearing();

	// set/get method
	void setRopeLadderDiscovered(bool);
	bool getRopeLadderDiscovered() const;

	/* overrides of pure virtual methods from parent class */

	// display methods
	void describeLocation() override;
	void briefDescription() override;

	// interaction methods
	int determineInteraction() override;
	int determineMove() override;

	// handler methods
	bool handleInteract(List*&, bool&, int) override;
	bool handleMove(List*, Location*&, int) override;
};

#endif // !CLEARING_HPP