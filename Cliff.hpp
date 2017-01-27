/*****************************************************************************************
** Program Filename: Cliff.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Cliff class, a subclass of the Location 
** class.  See comments for more details.
*****************************************************************************************/

#ifndef CLIFF_HPP
#define CLIFF_HPP
#include "Location.hpp"

class Cliff : public Location
{
private:

	Item *hook; // pointer to hook item from main array of game items

	// boolean values used for move and interaction
	bool hookDiscovered;
	bool pathCleared;

public:

	// constructors & destructor
	Cliff(List*);
	Cliff(List*, Location*, Location*, Location*, Location*);
	~Cliff();

	// set methods
	void setHookDiscovered(bool);
	void setPathCleared(bool);

	// get metjhods
	bool getHookDiscovered() const;
	bool getPathCleared() const;

	/* Override of Location's pure virtual methods */

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

#endif // !CLIFF_HPP