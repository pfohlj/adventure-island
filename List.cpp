/*****************************************************************************************
** Program Filename: List.cpp
** Author: Joseph A Pfohl
** Date: 06/28/2016
** Description: This is the implementation file for the List class.  Discriptions of
** individual functions can be found in their corresponding function header.
*****************************************************************************************/

#include"List.hpp"

#include <iostream> // cout, cin, getline(), endl, cin.get()
#include <iomanip>	// setw(), noskipws
#include <cctype>	// isalpha(), tolower(), toupper()

/*****************************************************************************************
** Function: isAlreadyOnList()
** Description: loops through list comparing the names of each element with itemName.  If
** a match is found, returns true.  If no matches are found, returns false.
** Parameters: string itemName
** Pre-Conditions: item must point to an array of pointers to Items
** Post-Conditions:N/A
*****************************************************************************************/

bool List::isAlreadyOnList(std::string itemName) const
{
	for (int i = 0; i < getNumElements(); i++)
	{
		if (list[i]->getName() == itemName)
		{
			return true;
		}
	}

	return false;
}

/*****************************************************************************************
** Function: List() constructor function
** Description: The constructor initializes the default values of numElements and
** maxCapacity.  Most notably, it creates a dynamically allocated array, assigns its
** beginning memory location to list, and fills it with nullptr values.
** Parameters: N/A
** Pre-Conditions: N/A
** Post-Conditions: N/A
*****************************************************************************************/

List::List()
{
	setNumElements(0);
	setMaxCapacity(5);

	list = new Item*[getMaxCapacity()];

	for (int counter = 0; counter < getMaxCapacity(); counter++)
	{
		list[counter] = nullptr;
	}
}

/*****************************************************************************************
** Function: constructor
** Description: creates an array of pointers to Items that are all instantiated as null
** pointers.
** Parameters: capacity - integer indicating capacity of the list.
*****************************************************************************************/

List::List(int capacity)
{
	setNumElements(0);
	setMaxCapacity(capacity);

	list = new Item*[getMaxCapacity()];

	for (int counter = 0; counter < getMaxCapacity(); counter++)
	{
		list[counter] = nullptr;
	}
}

/*****************************************************************************************
** Function: constructor
** Description: creates a new list item of a given capacity.  Assigns the first item
** to a certain value and the rest to null values.
** Parameters: capacity - the capacity of the list, firstItem - poiner to the first item
** in the list.
*****************************************************************************************/

List::List(int capacity, Item *firstItem)
{
	setNumElements(0);
	setMaxCapacity(capacity);

	list = new Item*[getMaxCapacity()];

	list[0] = firstItem;

	for (int counter = 1; counter < getMaxCapacity(); counter++)
	{
		list[counter] = nullptr;
	}
}

/*****************************************************************************************
** Function: ~List() destructor function
** Description: The destructor function frees the dynamically allocated memory used by 
** each instance of the List class by deleting each dynamically allocated pointer in the
**  list array and then deleting list itself.
** Parameters: N/A
** Pre-Conditions: The List object upon which the destructor is being called must have
** been initialized.
** Post-Conditions: N/A
*****************************************************************************************/

List::~List()
{
	std::cout << "List destructor" << std::endl;

	int counter = 0;

	while (list[counter] != nullptr 
		   && counter < getMaxCapacity())
	{
		delete list[counter];
		list[counter] = nullptr;
		counter++;
	}

	delete [] list;
	list = nullptr;
}

/*****************************************************************************************
** Function: setNumElements()
** Description: Sets the value of numElements to the value of the numIn parameter
** Parameters: int numIn
** Pre-Conditions: A new List object must have been created and its private variables 
** declared.
** Post-Conditions: N/A
*****************************************************************************************/

void List::setNumElements(int numIn)
{
	numElements = numIn;
}

/*****************************************************************************************
** Function: setMaxCapacity()
** Description: sets the value of maxCapacity to teh value of the maxIn parameter
** Parameters: int maxIn
** Pre-Conditions: A new List object must have been created and its private variables 
** declared.
** Post-Conditions: N/A
*****************************************************************************************/

void List::setMaxCapacity(int maxIn)
{
	maxCapacity = maxIn;
}

/*****************************************************************************************
** Function: setAllToNull
** Description: sets all of the list's values to null pointers
** Parameters: n/a
*****************************************************************************************/

void List::setAllToNull()
{
	for (int i = 0; i < getMaxCapacity(); i++)
	{
		list[i] = nullptr;
	}
}

/*****************************************************************************************
** Function: getNumElements()
** Description: returns the value of the private variable numElements
** Parameters: N/A
** Pre-Conditions: A new List object must have been created and its private variables 
** declared.
** Post-Conditions: N/A
*****************************************************************************************/

int List::getNumElements() const
{
	return numElements;
}

/*****************************************************************************************
** Function: getMaxCapacity()
** Description: returns the value of the private variable maxCapacity
** Parameters: N/A
** Pre-Conditions: A new List object must have been created and its private variables 
** declared.
** Post-Conditions: N/A
*****************************************************************************************/

int List::getMaxCapacity() const
{
	return maxCapacity;
}

/*****************************************************************************************
** Function: getItem
** Description: returns a pointer to the item at the given index
** Parameters: index - the index to return from
*****************************************************************************************/

Item* List::getItem(int index) const
{
	return list[index];
}

/*****************************************************************************************
** Function: getItem
** Description: searches the array for the item indicated by teh string and returns a pointer
** to that Item.  If the item is not in the list, throws a NOT_IN_LIST exception.
** Parameters: desiredItem - name of the item to get
*****************************************************************************************/

Item* List::getItem(std::string desiredItem) const
{
	for (int i = 0; i < getNumElements(); i++)
	{
		if (list[i]->getName() == desiredItem)
		{
			return list[i];
		}
	}

	throw NOT_IN_LIST();

}

/*****************************************************************************************
** Function: listIsFull
** Description: returns a bool indicating if the list is full or not full
** Parameters:
*****************************************************************************************/

bool List::listIsFull() const
{
	if (getNumElements() == getMaxCapacity())
	{
		return true;
	}

	return false;
}

/*****************************************************************************************
** Function: add_createItem()
** Description: Creates a new item with the name specified and adds it to the list.
** Parameters: a string indicating the name of the item to create and add.
** Pre-Conditions: item must point to a dynamically allocated array of pointers to Items
** Post-Conditions: N/A
*****************************************************************************************/

bool List::add_createItem(std::string name)
{
	if (getNumElements() != getMaxCapacity())
	{
		list[getNumElements()] = new Item(name);
		setNumElements(getNumElements() + 1);

		return true;
	}

	return false;
}

/*****************************************************************************************
** Function: addItem
** Description: adds a preexisting pointer to an item to the list
** Parameters: itemToAdd- a pointer to the item being added (not created)
*****************************************************************************************/

bool List::addItem(Item* itemToAdd)
{
	if (getNumElements() != getMaxCapacity())
	{
		list[getNumElements()] = itemToAdd;
		setNumElements(getNumElements() + 1);

		return true;
	}

	return false;
}

/*****************************************************************************************
** Function: remove_deleteItem()
** Description: Calls the displayRemoveList() function and then loops until the user 
** correctly enters the number of an item in the list.  Frees the memory associated with
** the item to be deleted and then shifts the value of all pointers to items in higher
** indices to one index lower. 
** Parameters: N/A
** Pre-Conditions: Must be at least 1 item in the list in order for this to be called.
** Post-Conditions: N/A
*****************************************************************************************/

void List::remove_deleteItem()
{
	int itemToBeRemoved;

	std::cout << "Which item would you like to remove?" << std::endl;
	displayList();
	std::cout << std::endl << "Item number: ";

	std::cin >> std::noskipws;
	
	while(1)
	{
		if (std::cin >> itemToBeRemoved &&			// input is an int
			itemToBeRemoved >= 0 &&					// input is not netagive
			itemToBeRemoved <= getNumElements())	// input is not too large
		{
			while (std::cin.get() != '\n') ;
			break;
		}

		std::cout << "Invalid option.  Press enter to try again.";

		std::cin.clear();
		while (std::cin.get() != '\n') ;

		std::cin.get();

		system("clear");

		std::cout << "Which item would you like to remove?" << std::endl;
		displayList();
		std::cout << std::endl << "Item number: ";

	}

	itemToBeRemoved--;

	/*
	** The nullptr assignment statements ensure that every unassigned element of the array
	** remains a nullptr value.  If the deleted element is the last element in the array 
	** then the while statement will not execute so the nullptr assignment must occur in 
	** this scope.
	*/

	delete list[itemToBeRemoved];
	list[itemToBeRemoved] = nullptr;

	while (itemToBeRemoved <= (getMaxCapacity() - 2))
	{
		list[itemToBeRemoved] = list[itemToBeRemoved + 1];
		list[itemToBeRemoved + 1] = nullptr;
		
		itemToBeRemoved++;
	} 

	setNumElements(getNumElements() - 1);
}

/*****************************************************************************************
** Function: removeItem
** Description: searches the string for an item.  if a match is found, the pointer at that 
** index is assigned a null value and all non null pointer values following it are shifted
** one index lower.
** Parameters: remove - the name of the item to search for and remove
*****************************************************************************************/

void List::removeItem(std::string remove)
{
	int itemToBeRemoved = 0;

	while (itemToBeRemoved < getNumElements() 
		   && list[itemToBeRemoved]->getName() != remove)
	{
		itemToBeRemoved++;
	}

	if (itemToBeRemoved < getNumElements())
	{
		list[itemToBeRemoved] = nullptr;

		while (itemToBeRemoved <= (getMaxCapacity() - 2))
		{
			list[itemToBeRemoved] = list[itemToBeRemoved + 1];
			list[itemToBeRemoved + 1] = nullptr;

			itemToBeRemoved++;
		}

		setNumElements(getNumElements() - 1);
	}
}

/*****************************************************************************************
** Function: displayList()
** Description: Outputs the contents of the list.
** Parameters: N/A
** Pre-Conditions: list must contain >= 1 poiners to items
** Post-Conditions: N/A
*****************************************************************************************/

void List::displayList() const
{
	std::cout << "===================================" << std::endl;
	std::cout << "|            INVENTORY            |" << std::endl;
	std::cout << "===================================" << std::endl;
	
	for (int i = 0; i < getNumElements(); i++)
	{
		std::cout << "|" << i + 1 << ". " << std::setw(30) << std::left << list[i]->getName() 
			<< "|" << std::endl;
	}

	std::cout << "===================================" << std::endl;
}