#include<iostream>
#include <string>
/* 

{1, 4, 5, 6, 9, 14, 21, 23, 28, 31, 35, 42, 46, 50, 53, 57, 62, 63, 65, 74, 79, 89,95}

Enter search key (or ‘x’ to exit): 21
21 is in position 6.
Enter search key (or ‘x’ to exit): 50
50 is in position 13.
Enter search key (or ‘x’ to exit): 0
0 not found.
Enter search key (or ‘x’ to exit): x

 TODO  21, 23, 28, 31, 35 not found

*/

using namespace std;

int BinSearch(int data[], int numElements, int searchKey);

int main()
{
	int array[24] = { 1, 4, 5, 6, 9, 14, 21, 23, 28, 31, 35, 42, 46, 50, 53, 57, 62, 63, 65, 74, 79, 89, 95 };
	auto quit = false;
	while (!quit)
	{
		string answer= "";
		auto number = 0;
		auto index = 0;
		cout << "Enter search key (or 'x' to exit): ";
		getline(cin, answer);
		if (answer == "x")
		{
			quit = true;
			cout << "Exiting.." << endl;
		}
		else
			number = atoi(answer.c_str());
		index = BinSearch(array, 23, number);

		if (index != -1)
			cout << number << " is in position " << index << endl;
		else
			cout << number << " not found." << endl;
			
	}

	return 0;
}
int BinSearch(int data[], int numElements, int searchKey)
{
	auto min = 0;
	auto max = numElements -1;
	auto half = numElements / 2;
	auto temp = 0;

	while (half != -1 && searchKey != data[half])
	{
		if (searchKey > data[half])	min = half + 1;
		else max = half - 1;
		half = (max - min >= 0 ? (max - min) / 2 + min : -1);
	}

	return half;
}