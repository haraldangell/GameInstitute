#include<iostream>

/*

Let x[n] = x[0],...,x[n-1] be an array of given integers to sort.
Let SubArrayEnd be an integer to store the last index of the working subarray.
Let nextEnd be an integer used to help compute the end of the next pass’ subarray.
Initialize SubArrayEnd = n – 1.
While SubArrayEnd > 0, do the following:
1. Initialize nextEnd = 0;
2. For j = 0 to SubArrayEnd - 1, do the following:
a. If x[j] > x[j+1] then
i. swap x[j] and x[j+1].
ii. nextEnd = j;
b. Increment j.
3. SubArrayEnd = nextEnd.


Enter ten unsorted integers...
[0] = 5
[1] = -3
[2] = 2
[3] = 1
[4] = 7
[5] = -9
[6] = 4
[7] = -5
[8] = 6
[9] = -12
Unsorted List = 5, -3, 2, 1, 7, -9, 4, -5, 6, -12,
Sorting...
Sorted List = -12, -9, -5, -3, 1, 2, 4, 5, 6, 7,
*/
using namespace std;



void BubbleSort(int data[], int n);

int main()
{

	int array[] = { 5, -3, 2, 1, 7, -9, 4, -5, 6, -12 };
	auto size = sizeof(array) / sizeof(int);
	cout << "Unsorted List = ";
	for (auto i = 0; i < size; i++)
	{
		if (i == 9)
			cout << array[i] << endl;
		else
			cout << array[i] << ", ";
	}
	BubbleSort(array, size);
	cout << "Sorted List = ";
	for (auto i = 0; i < size; i++)
	{
		if (i == 9)
			cout << array[i] << endl;
		else
			cout << array[i] << ", ";
	}
	cout << endl;
	return 0;
}

void BubbleSort(int data[], int n)
{
	cout << "Sorting..." << endl;
	auto SubArrayEnd = n - 1;
	while (SubArrayEnd > 0)
	{
		auto nextEnd = 0;
		for (auto j = 0; j < SubArrayEnd; ++j)
		{
			if (data[j] > data[j + 1])
				swap(data[j], data[j + 1]);
			nextEnd = j;
		}
		SubArrayEnd = nextEnd;
	}

}
