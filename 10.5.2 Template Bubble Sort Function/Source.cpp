#include <iostream>
#include <string>
using namespace std;

template<class T>
void BubbleSort(T data[], int n)
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

template<class T>
void Print(T array, int size, string str)
{
	cout << str;
	for (auto i = 0; i < size; i++)
	{
		if (i == (size - 1 ))
			cout << array[i];
		else
			cout << array[i] << ", ";
	}
	cout << endl;
}


int main()
{

	int array[] = { 5, -3, 2, 1, 7, -9, 4, -5, 6, -12 };
	auto size = sizeof(array) / sizeof(int);
	Print(array, size, "Unsorted List = ");
	BubbleSort(array, size);
	Print(array, size, "Sorted List = ");

	string str[3] = { "adfas", "uiop", "gsdr" };

	Print(str, 3, "Unsorted List = ");
	BubbleSort(str, 3);
	Print(str, 3, "Sorted List = ");

	return 0;
}