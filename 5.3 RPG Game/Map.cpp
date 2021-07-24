// Map.cpp

#include "Map.h"
#include <iostream>
#include "Random.h"
#include "Player.h"


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
	std::cout << "1) North, 2) East, 3) South, 4) West: ";
	std::cin >> selection;

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
	std::cout << std::endl;
}

bool Map::checkRandomEncounter(Player &player, int number)
{
	int roll = Random(0, 20);
	
	Monster* monster = new Monster[roll];

	
	for (int i = 0; i < roll; ++i)
	{
		if(roll >= 0 && roll <= 10)
		{
			monster[i] = Monster("Orc", 10, 8, 200, Random(5, 50),"Orc Skin", 1, "Short Sword", 2, 7);

		}
		else if(roll >= 11 && roll <= 15)
		{
			monster[i] = Monster("Goblin", 6, 6, 100, Random(10, 100), "Fish Skin", 0, "Dagger", 1, 5);

		}
		else if(roll >= 16 && roll <= 19)
		{
			monster[i] = Monster("Ogre", 20, 12, 500, Random(15, 150), "Tree Leaves", 2, "Club", 3, 8);

		}
		else if(roll == 20)
		{
			monster[i] = Monster("Orc Lord", 25, 15, 2000, Random(30, 300), "Cat Skin", 5, "Two Handed Sword", 5, 20);

		}
		roll = Random(0, 20);
	}

	if (number == 1)
	{
		std::cout << "You encountered a " << monster[0].getName() << std::endl;
	}
	else 
	{
		std::cout << "You encountered " << number << " monsters!" << std::endl;
	}
	//This have to be adjusted later to handle several monsters
	
	std::cout << "Prepare for battle!" << std::endl;



	for (int i = 0; i < number; ++i)
	{
		bool battle = false;
		while(!battle)
		{
			player.displayHitPoints();
			monster[i].displayHitPoints();
			std::cout << std::endl;

			// Player's turn to attack first.
			bool runAway = player.attack(monster[i]);

			if (runAway)
				break;

			if (monster[i].isDead())
			{
				player.victory(monster[i].getXPReward(), monster[i].getGold());
				player.levelUp();
				battle = true;

			}
			else
				monster[i].attack(player);

			if (player.isDead())
			{
				delete[] monster;
				monster = 0;
				return true;
				break;
			}
		}
			
	}
	
	delete[] monster;
	monster = 0;


	std::cout << std::endl;
	return false;
}

void Map::printPlayerPos()
{
	std::cout << "Player Position = (" << mPlayerXPos << ", " << mPlayerYPos << ")" << std::endl << std::endl;
}