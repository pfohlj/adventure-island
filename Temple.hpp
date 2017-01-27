/*****************************************************************************************
** Program Filename: Temple.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Temple class, a class derived from the
** Location class.  For information on methods, please see Temple.cpp
*****************************************************************************************/

#ifndef TEMPLE_HPP
#define TEMPLE_HPP
#include "Location.hpp"

class Temple : public Location
{
public:
	Temple();
	Temple(Location*, Location*, Location*, Location*);
	~Temple();

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

#endif // !TEMPLE_HPP
