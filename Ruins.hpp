/*****************************************************************************************
** Program Filename: Ruins.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for hte Ruins class, a child of the Location
** class.  For information on specific methods or data members, please see their accompanying
** comments or the Ruins.cpp file.
*****************************************************************************************/

#ifndef RUINS_HPP
#define RUNIS_HPP
#include "Location.hpp"

class Ruins : public Location
{
private:

	bool gateOpened;
	bool pathCleared;

public:

	// constructors & destructor
	Ruins();
	Ruins(Location*, Location*, Location*, Location*);
	~Ruins();

	// set methods
	void setGateOpened(bool);
	void setPathCleared(bool);

	// get methods
	bool getGateOpened() const;
	bool getPathCleared() const;

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
};

#endif // !RUINS_HPP