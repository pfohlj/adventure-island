/*****************************************************************************************
** Program Filename: List.hpp
** Author: Joseph A Pfohl
** Date: 8/8/2016
** Description: This is the interface file for the List class. Descriptions of data
** members and individual functions can be found in the accompanying comments or in the
** List.cpp file.
*****************************************************************************************/

#ifndef LIST_H
#define LIST_H

#include "Item.hpp"		// necessary for Item**

class NOT_IN_LIST {};

class List
{
private:
	Item** list;		// array that points to items stored in the list
	int numElements;	
	int maxCapacity;

public:

	// constructor and destructor (necessary because of dynamic memory allocation)
	List();
	List(int);
	List(int, Item*);
	~List();

	// set methods
	void setNumElements(int);
	void setMaxCapacity(int);
	void setAllToNull();

	// get methods
	int getNumElements() const;
	int getMaxCapacity() const;
	Item* getItem(int) const; 
	Item* getItem(std::string) const;// throws NOT_IN_LIST exception if Item not found

	// bool methods
	bool listIsFull() const;

	// list manipulation functions
	bool add_createItem(std::string);
	bool addItem(Item*);
	void remove_deleteItem();
	void removeItem(std::string);
	bool isAlreadyOnList(std::string) const;

	// display functions
	void displayList() const;
};

#endif // !LIST_H