/*****************************************************************************************
** Program Filename: Dungeon.hpp
** Author: Joseph A. Pfohl
** Date: 08/08/2016
** Description: Class interface file for the Dungeon class, a subclass of the Location
** class.  See comments for more details.
*****************************************************************************************/

#ifndef DUNGEON_HPP
#define DUNGEON_HPP
#include "Location.hpp"

class Dungeon : public Location
{
private:
	
	Item *blueOrb; // poiner to blueOrb item from game's array of avilable items

	// boolean objects for interaction and movement
	bool word1;
	bool word2;
	bool word3;
	bool word4;
	bool wordsTranslated;

public:

	// constructors & destructor
	Dungeon(List*);
	Dungeon(List*, Location*, Location*, Location*, Location*);
	~Dungeon();

	// set methods
	void setWord1(bool);
	void setWord2(bool);
	void setWord3(bool);
	void setWord4(bool);
	void setAllWords(bool);
	void updateWordsTranslated();

	// get methods
	bool getWord1() const;
	bool getWord2() const;
	bool getWord3() const;
	bool getWord4() const;
	bool getWordsTranslated() const;

	/* overrides for pure virtual methods from Location parent class */

	// display methods
	void describeLocation() override;
	void briefDescription() override;

	// interaction methods
	int determineInteraction() override;
	int determineMove() override;

	// handler methods
	bool handleInteract(List*&, bool&, int) override;
	bool handleMove(List*, Location*&, int) override;
	
	// puzzle method
	bool attemptPuzzle();
};

#endif // !DUNGEON_HPP