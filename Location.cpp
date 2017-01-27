/*****************************************************************************************
** Program Filename: Location.cpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the implementation file for the Location class.  For information 
** on an individual method, please see its accompanying comment block.
*****************************************************************************************/

#include "Location.hpp"
#include <iostream>

/*****************************************************************************************
** Function: constructor
** Description: sets all location values equal to nullptr
** Parameters: n/a
*****************************************************************************************/

Location::Location()
{
	setNorth(nullptr);
	setEast(nullptr);
	setSouth(nullptr);
	setWest(nullptr);
}

/*****************************************************************************************
** Function: override constructor
** Description: sets all location pointer values equal to the parameters pased to the function
** Parameters: four pointer variables to other Locations
*****************************************************************************************/

Location::Location(Location *north = nullptr, Location *east = nullptr, 
	Location *south = nullptr, Location *west = nullptr)
{
	setNorth(north);
	setEast(east);
	setSouth(south);
	setWest(west);
}

/*****************************************************************************************
** Function: destructor
** Description: serves no purpose.  Is virtual to allow children to implement as needed
** Parameters: n/a
*****************************************************************************************/

Location::~Location()
{
	// nothing here
}

/*****************************************************************************************
** Function: setNorth
** Description: sets the value of north
** Parameters: north - pointer to a Location
*****************************************************************************************/

void Location::setNorth(Location* north)
{
	this->north = north;
}

/*****************************************************************************************
** Function: setEast
** Description: sets the value of east
** Parameters: east - pointer to a Location
*****************************************************************************************/

void Location::setEast(Location* east)
{
	this->east = east;
}

/*****************************************************************************************
** Function: setSouth
** Description: sets the value of south
** Parameters: south - pointer to a Location
*****************************************************************************************/

void Location::setSouth(Location* south)
{
	this->south = south;
}

/*****************************************************************************************
** Function: setWest
** Description: sets the value of west
** Parameters: west - pointer to a Location object
*****************************************************************************************/

void Location::setWest(Location* west)
{
	this->west = west;
}

/*****************************************************************************************
** Function: setAllPaths
** Description: sets the value of all of the paths to the passed in parameters
** Parameters: 4 pointers to other Location objects
*****************************************************************************************/

void Location::setAllPaths(Location* north, Location* east, Location* south, Location* west)
{
	setNorth(north);
	setEast(east);
	setSouth(south);
	setWest(west);
}

/*****************************************************************************************
** Function: disconnectAllPaths
** Description: sets the value of all the Location pointers to null values 
** Parameters: n/a
*****************************************************************************************/

void Location::disconnectAllPaths()
{
	setAllPaths(nullptr, nullptr, nullptr, nullptr);
}

/*****************************************************************************************
** Function: getNorth
** Description: returns north
** Parameters: n/a
*****************************************************************************************/

Location* Location::getNorth() const
{
	return north;
}

/*****************************************************************************************
** Function: getEast
** Description: returns east
** Parameters:
*****************************************************************************************/

Location* Location::getEast() const
{
	return east;
}

/*****************************************************************************************
** Function: getSouth
** Description: returns south
** Parameters: n/a
*****************************************************************************************/

Location* Location::getSouth() const
{
	return south;
}

/*****************************************************************************************
** Function: getWest
** Description: returns west
** Parameters: n/a
*****************************************************************************************/

Location* Location::getWest() const
{
	return west;
}
