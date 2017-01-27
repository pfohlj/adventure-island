/*****************************************************************************************
** Program Filename: Beach.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Beach class.  For more information on
** a data member of method, see their associated comments of the companion file, Beach.cpp
*****************************************************************************************/

#ifndef BEACH_HPP
#define BEACH_HPP
#include "Location.hpp"

class Beach : public Location
{
private:

	bool macheteDiscovered;
	bool pathCleared;

	Item *machete; // pointer to machete item that can be gained in this location

public:

	// constructor & destructor 
	Beach(List*);
	Beach(List*, Location*, Location*, Location*, Location*);
	~Beach();

	// get methods
	bool getMacheteDiscovered() const;
	bool getPathCleared() const;

	// set methods
	void setMacheteDiscovered(bool);
	void setPathCleared(bool);


	// display methods
	void describeLocation() override;
	int determineInteraction() override;
	int determineMove() override;
	void briefDescription() override;

	// handler methods
	bool handleInteract(List*&, bool&, int) override;
	bool handleMove(List*, Location*&, int) override;
};

#endif // !BEACH_HPP
