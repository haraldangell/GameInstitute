// Map.h

#ifndef MAP_H
#define MAP_H

#include "Weapon.h"
#include "Monster.h"
#include <string>

class Map
{
public:
	// Constructor.
	Map();

	// Methods
	int  getPlayerXPos();
	int  getPlayerYPos();
	void movePlayer();
	bool checkRandomEncounter(Player &player, int number);
	void printPlayerPos();

private:
	// Data members.
	int mPlayerXPos;
	int mPlayerYPos;
};

#endif //MAP_H