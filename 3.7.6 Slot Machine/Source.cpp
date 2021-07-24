#include<iostream>
#include<cstdlib>
#include<ctime>

/*
If the player enters “1”, the program should ask the user to enter in his or her bet. 

The program needs to verify that a legal bet was placed; 
that is, a bet greater than zero and less than or equal to the amount of
money the player has. 

After the player has input his or her bet, the program must calculate three random
numbers in the range [2, 7] and output them neatly to the screen. 

menu

enter 1 play enter 2 exit

 if(number1 == 7 && number2 == 7 && number3 == 7) 10X
 if(number1 == number2 && number1 == number3 && number2 == number3) 5x
if(number1 == number2 || number1 == number3 || number2 == number3) 3x
else, the player loses his or her bet. 


check money, have money continue else quit 

Player’s chips: $1000
1) Play slot. 2) Exit. 1
Enter your bet: 1500
You did not enter a valid bet.
Enter your bet: 1000
3 3 7
You win!
Player’s chips: $3000
1) Play slot. 2) Exit. 2

*/


using namespace std;

int Random(int low, int high);

int Game(int a);

int main()
{
	auto quit = false;
	auto money = 1000;
	auto choice = 0;
	srand(time(0));

	while (!quit)
	{
		cout << "Player’s chips: $" << money << endl;
		cout << "1) Play slot. 2) Exit. ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			money = Game(money);
			break;
		case 2:
			quit = true;
			cout << "Exiting…";
			break;
		}
		if (money <= 0)
		{
			quit = true;
			cout << "Exiting…";
		}
	}

	return 0;
}
int Random(int low, int high)
{
	return low + rand() % ((high + 1) - low);
}
int Game(int a)
{
	auto activeGame = true;
	while (activeGame)
	{
		auto bet = 0;
		auto number1 = 0;
		auto number2 = 0;
		auto number3 = 0;

		cout << "Enter your bet: ";
		cin >> bet;

		if (a >= bet)
		{
			number1 = Random(2, 7);
			number2 = Random(2, 7);
			number3 = Random(2, 7);
			cout << number1 << " " << number2 << " " << number3 << endl;

			if (number1 == 7 && number2 == 7 && number3 == 7)
			{
				cout << "You win! << endl";
				a += bet * 10;
			}
			else if (number1 == number2 && number1 == number3 && number2 == number3)
			{
				cout << "You win! << endl";
				a += bet * 5;
			}
			else if (number1 == number2 || number1 == number3 || number2 == number3)
			{
				cout << "You win! << endl";
				a += bet * 3;
			}
			else
			{
				cout << "You loose" << endl;
				a -= bet;
			}
				
			activeGame = false;
		}
		else
			cout << "You did not enter a valid bet." << endl;

	}

	return a;
}