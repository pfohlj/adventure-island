/*****************************************************************************************
** Program Filename: Hut.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Hut class.  For information on individual
** data members and functions, please see their corresponding comment blocks or see the
** companion file Hut.cpp.
*****************************************************************************************/

#ifndef HUT_HPP
#define HUT_HPP
#include "Location.hpp"

class Hut : public Location
{
private:

	Item *string; // pointer to the string object from the main list of game objects.

	// boolean values for interaction and movement
	bool pathCleared;
	bool doorUnlocked;
	bool stringDiscovered;
	bool doorDiscovered;

public:

	// constuctosrs & destructor
	Hut(List*);
	Hut(List*, Location*, Location*, Location*, Location*);
	~Hut();

	// set methods
	void setPathCleared(bool);
	void setStringDiscovered(bool);
	void setDoorDiscovered(bool);
	void setDoorUnlocked(bool);

	// get methods
	bool getPathCleared() const;
	bool getStringDiscovered() const;
	bool getDoorDiscovered() const;
	bool getDoorUnlocked() const;

	/* Overrides of Location pure virtual methods */

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

#endif // !HUT_HPP