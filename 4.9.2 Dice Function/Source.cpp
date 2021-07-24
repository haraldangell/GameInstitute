#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

void Dice(int& die1, int& die2);
void Dice(int* die1, int* die2);

int main()
{
	srand(time(0));
	auto die1 = 0;
	auto die2 = 0;
	auto money = 1000;
	auto bet = 0;


	cout << "Before any function: Die 1: " << die1 << " and Die 2: " << die2 << endl;
	Dice(die1, die2);
	cout << "After Ref. function: Die 1: " << die1 << " and Die 2: " << die2 << endl;
	Dice(&die1, &die2);
	cout << "After Ptr. function: Die 1: " << die1 << " and Die 2: " << die2 << endl;

	auto quit = false;
	while (!quit)
	{
		if (money <= 0)
		{
			cout << "No more money left, exiting...." << endl;
			quit = true;
			break;
		}
		cout << "You have " << money << "€ in the bank..." << endl;
		cout << "Get 2 times 6, 2 times 4 or 2 times 2 to win. " << endl;
		cout << "Enter your bet or -1 to leave the game: ";
		cin >> bet;
		if (bet <= money && bet > 0 || bet == -1)
		{
			Dice(&die1, &die2);
			cout << "Die 1: " << die1 << " and Die 2: " << die2 << endl;
			if (die1 == 6 && die2 == 6 || die1 == 4 && die2 == 4 || die1 == 4 && die2 == 4)
			{
				cout << "You won!!!" << endl;
				money += (bet * 2);
			}
			else
			{
				money -= bet;
			}


		}
		if (bet == -1)
		{
			cout << "Exiting...." << endl;
			quit = true;

		}
	}

	return 0;
}

void Dice(int & die1, int & die2)
{
 	die1 = 1 + rand() % ((6 + 1) - 1);
	die2 = 1 + rand() % ((6 + 1) - 1);
}

void Dice(int * die1, int * die2)
{
	*die1 = 1 + rand() % ((6 + 1) - 1);
	*die2 = 1 + rand() % ((6 + 1) - 1);
}
