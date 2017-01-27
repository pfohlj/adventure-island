/*****************************************************************************************
** Program Filename: Location.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the Location class.  For information on 
** data members or individual functions, see their comments or the accompanying file,
** Location.cpp.  Location is an abstract class and as such, has a number of pure virtual
** methods only instantiated in its children.
*****************************************************************************************/

#ifndef LOCATION_HPP
#define LOCATION_HPP
#include "List.hpp"

class Location
{
protected:

	// pointers to other locations the object is connected to
	Location *north;
	Location *east;
	Location *south;
	Location *west;

public:

	// constructors & destructor
	Location();
	Location(Location*, Location*, Location*, Location*);
	virtual ~Location();	// default destructor behavior desired.  children
									// can implement enhanced destructors.

	// set methods
	void setNorth(Location*);
	void setEast(Location*);
	void setSouth(Location*);
	void setWest(Location*);
	void setAllPaths(Location*, Location*, Location*, Location*);
	void disconnectAllPaths();

	// get methods
	Location* getNorth() const;
	Location* getEast() const;
	Location* getSouth() const;
	Location* getWest() const;

	/* pure virtual methods to be implemented by sub-classes */

	// display methods
	virtual void describeLocation() = 0;
	virtual void briefDescription() = 0;

	// interaction methods
	virtual int determineInteraction() = 0;
	virtual int determineMove() = 0;

	// handler methods
	virtual bool handleInteract(List*&, bool&, int) = 0;
	virtual bool handleMove(List*, Location*&, int) = 0;
};

#endif // !LOCATION_HPP