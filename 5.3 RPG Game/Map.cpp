// Map.cpp

#include "Map.h"
#include <iostream>
#include "Random.h"
using namespace std;

Map::Map()
{
	// Player starts at origin (0, 0)
	mPlayerXPos = 0;
	mPlayerYPos = 0;
}

int  Map::getPlayerXPos()
{
	return mPlayerXPos;
}

int  Map::getPlayerYPos()
{
	return mPlayerYPos;
}

void Map::movePlayer()
{
	int selection = 1;
	cout << "1) North, 2) East, 3) South, 4) West: ";
	cin >> selection;

	// Update coordinates based on selection.
	switch( selection )
	{
	case 1: // North
		mPlayerYPos++;
		break;
	case 2: // East
		mPlayerXPos++;
		break;
	case 3: // South
		mPlayerYPos--;
		break;
	default: // West
		mPlayerXPos--;
		break;
	}
	cout << endl;
}

Monster * Map::checkRandomEncounter()
{
	int roll = Random(0, 20);

	Monster * monster = 0;
	std::string name = "";

	if(roll >= 0 && roll <= 10)
	{
		monster = new Monster("Orc", 10, 8, 200, Random(5, 50),"Orc Skin", 1, "Short Sword", 2, 7);
		name = monster->getName();
	}
	else if(roll >= 11 && roll <= 15)
	{
		monster = new Monster("Goblin", 6, 6, 100, Random(10, 100), "Fish Skin", 0, "Dagger", 1, 5);
		name = monster->getName();
	}
	else if(roll >= 16 && roll <= 19)
	{
		monster = new Monster("Ogre", 20, 12, 500, Random(15, 150), "Tree Leaves", 2, "Club", 3, 8);
		name = monster->getName();
	}
	else if(roll == 20)
	{
		monster = new Monster("Orc Lord", 25, 15, 2000, Random(30, 300), "Cat Skin", 5, "Two Handed Sword", 5, 20);
		name = monster->getName();
	}
	//This have to be adjusted later to handle several monsters
	cout << "You encountered an " << name << "!" << endl;
	cout << "Prepare for battle!" << endl;
	cout << endl;
	return monster;
}

void Map::printPlayerPos()
{
	cout << "Player Position = (" << mPlayerXPos << ", " << mPlayerYPos << ")" << endl << endl;
}