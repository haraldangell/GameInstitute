#include<iostream>


using namespace std;


int main()
{
	auto vertical = 0;
	auto horisontal = 0;

	auto quit = false;

	while (!quit)
	{
		char answer = 'a';
		cout << "Current Position = (" << horisontal << ", " << vertical << ") " << endl;
		cout << "Move(N)orth, (E)ast, (S)outh, (W)est(Q)uit ?";
		cin >> answer;
		switch (answer)
		{
		case 'N':
		case 'n':
			++vertical;
			break;
		case 'E':
		case 'e':
			++horisontal;
			break;
		case 'S':
		case 's':
			--vertical;
			break;
		case 'W':
		case 'w':
			--horisontal;
			break;
		case 'Q':
		case 'q':
			quit = true;
			break;
		}
	}
	cout << "Exiting...";

	return 0;
}