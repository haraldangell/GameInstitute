// game.cpp

#include "Map.h"
#include "Player.h"
#include "Random.h"
#include "Store.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

bool done = false;
void monsterHunt(Monster* monster, Player& player);

int main()
{
	srand(time(0));

	Map gameMap;

	Player mainPlayer;

	mainPlayer.createCharater();

	// Begin adventure.

	while (!done)
	{
		// Each loop cycly we output the player position and 
		// a selection menu.

		gameMap.printPlayerPos();

		if (gameMap.getPlayerXPos() == 1 && gameMap.getPlayerYPos() == 1)
		{
			Store store;
			store.enter(mainPlayer, "The Store");
		}
		int selection = 1;
		cout << "1) Move, 2) Rest, 3) View Stats, 4) Quit: ";
		cin >> selection;

		std::vector<Monster*> monster;
		switch (selection)
		{
		case 1:
		{
			gameMap.movePlayer();

			// Check for a random encounter.  This function
			// returns a null pointer if no monsters are
			// encountered.
			int test = Random(1, mainPlayer.getLevel());
			if (test == 0)
				for (int i = 0; i < test; ++i)
					monster.push_back(gameMap.checkRandomEncounter());
			if (!monster.empty())
				for (int i = 0; i < test; ++i)
				{
					monsterHunt(monster[i], mainPlayer);
					if (monster[i]->isDead())
					{
						delete monster[i];
					}
				}


			break;
		}

		case 2:
		{
			if (1 == Random(1, 4))
			{
				monster.push_back(gameMap.checkRandomEncounter());
				if (monster.empty())
					monsterHunt(monster[0], mainPlayer);

			}

			mainPlayer.rest();
			break;
		}
		case 3:
		{
			mainPlayer.viewStats();
			break;
		}
		case 4:
		{
			done = true;
			break;
		}

		}
	}
}
void monsterHunt(Monster * monster, Player & player)
{
	// Check for a random encounter.  This function
	// returns a null pointer if no monsters are
	// encountered.
	// 'monster' not null, run combat simulation.
		// Loop until a 'break' statement.
	while (true)
	{
		// Display hitpoints.
		player.displayHitPoints();
		monster->displayHitPoints();
		cout << endl;

		// Player's turn to attack first.
		bool runAway = player.attack(*monster);

		if (runAway)
			break;

		if (monster->isDead())
		{
			player.victory(monster->getXPReward(), monster->getGold());
			player.levelUp();
		}
		else
			monster->attack(player);

		if (player.isDead())
		{
			player.gameover(done);
			done = true;
			break;
		}



	}

	// The pointer to a monster returned from
	// checkRandomEncounter was allocated with
	// 'new', so we must delete it to avoid
	// memory leaks.



}