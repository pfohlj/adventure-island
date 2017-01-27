/*****************************************************************************************
** Program Filename: Item.h
** Author: Joseph A Pfohl
** Date: 06/28/2016
** Description: This is the header / declaration file for the Item class.  Each instance
** of the Item class has 6 private data members.  name holds the items name, unit holds
** the items unit of measurement, purchaseAmt holds the number needed, unitPrice holds the 
** item's unit price, subTotal holds the calculated value of the item's subtotal (based 
** on purchaseAmt and unitPrice) and subTotalSet keeps track of whether the subtotal has
** already been set. Information on the class' functions can be found in the function 
** header blocks in Item.cpp.
*****************************************************************************************/

#ifndef ITEM_H
#define ITEM_H

#include <string> // required for name / unit

class Item
{
private:
	std::string name;

public:
	// default and overload constructor methods
	Item();
	Item(std::string);
	~Item();
	
	// set methods
	void setName(std::string);
	
	// get methods
	std::string getName() const;
};

#endif // !ITEM_H
