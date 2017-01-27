/*****************************************************************************************
** Program Filename: Item.cpp
** Author: Joseph A Pfohl
** Date: 8/8/2016
** Description: This is the implementation file for the Item class.  Discriptions of
** individual functions can be found in their corresponding function header.
*****************************************************************************************/

#include "Item.hpp"
#include <iostream>

/*****************************************************************************************
** Function: Item()
** Description: Default constructor method for the Item class.  Sets all data members to 
** blank / zero values.
** Parameters: N/A
** Pre-Conditions: An item must be created with no parameters.
** Post-Conditions: N/A
*****************************************************************************************/

Item::Item()
{
	setName("");
}

/*****************************************************************************************
** Function: Item()
** Description: Overload constructor function that takes values for the Item's mame, unit,
** amount, and price.  Passes these values to the appropriate set methods.
** Parameters: string name, string unit, double amt, double price.
** Pre-Conditions: An item must have been created with parameters for all valid options.
** Post-Conditions: N/A
*****************************************************************************************/

Item::Item(std::string name)
{
	setName(name);
}

/*****************************************************************************************
** Function:
** Description:
** Parameters:
*****************************************************************************************/

Item::~Item()
{
	std::cout << "Item destructor" << std::endl;
}

/*****************************************************************************************
** Function: setName()
** Description: sets name equal to nameIn
** Parameters: string nameIn
** Pre-Conditions: N/A
** Post-Conditions: N/A
*****************************************************************************************/

void Item::setName(std::string nameIn)
{
	name = nameIn;
}

/*****************************************************************************************
** Function: getName()
** Description: returns the value of name
** Parameters: N/A
** Pre-Conditions: N/A 
** Post-Conditions: N/A
*****************************************************************************************/

std::string Item::getName() const
{
	return name;
}
