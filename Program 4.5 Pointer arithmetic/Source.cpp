#include<iostream>
using namespace std;


int main()
{
	short arrayName[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

	short * firstPtr = arrayName;

	cout << "Style 1 Addition operation. " << endl;
	for (auto i = 0; i < 8; ++i)
		cout << *(firstPtr + i) << " ";
	cout << endl;
	cout << "Style 2: Increment operator." << endl;
	for (auto i = 0; i < 8; ++i)
	{
		cout << *firstPtr << " ";
		++firstPtr;
	}
	cout << endl;


	return 0;
}