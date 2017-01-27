/*****************************************************************************************
** Program Filename: Reef.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: This is the interface file for the reef class. For information on 
** specific data members or functions, please see their accompanying comments or the 
** Reef.cpp file.
*****************************************************************************************/

#ifndef REEF_HPP
#define REEF_HPP
#include "Location.hpp"

class Reef : public Location
{
private:

	Item *goldKey;
	bool goldKeyDiscovered;

public:

	// constructor & destructor
	Reef(List*);
	Reef(List*, Location*, Location*, Location*, Location*);
	~Reef();

	// get / set methods
	bool getGoldKeyDiscovered() const;
	void setGoldKeyDiscovered(bool);

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

#endif // !REEF_HPP