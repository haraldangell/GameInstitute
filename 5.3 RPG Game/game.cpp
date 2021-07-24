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

		
		switch (selection)
		{
		case 1:
		{
			gameMap.movePlayer();

			// Check for a random encounter.  This function
			// returns a null pointer if no monsters are
			// encountered.
			int number = Random(1, mainPlayer.getLevel());

			if (number > 0)
			{
				done = gameMap.checkRandomEncounter(mainPlayer, number);
			}
			if(done)
				mainPlayer.gameover();
			break;
		}

		case 2:
		{
			int number = Random(1, mainPlayer.getLevel());
			if (1 == Random(1, 4))
			{
				done = gameMap.checkRandomEncounter(mainPlayer, number);

				if (done)
					mainPlayer.gameover();
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





