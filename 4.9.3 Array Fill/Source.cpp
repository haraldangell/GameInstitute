#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>

using namespace std;

void RandomArrayFill(int* array, int size);


int main()
{
	srand(time(0));
	auto size = 0;
	cout << "Enter the size of an array to create : ";
	cin >> size;
	int *array = new int[size];
	RandomArrayFill(array, size);
	cout << "Array = {";
	for(auto i = 0; i < size; ++i)
		if (i == size-1)
			cout << array[i];
		else
			cout << array[i] << ", ";
	cout << "}" << endl;
	delete[] array;
	array = nullptr;

	return 0;
}

void RandomArrayFill(int * array, int size)
{
	for(auto i = 0; i < size; ++i)
		array[i] =  rand() % 100;
	cout << "Creating array and filling it with random numbers..." << endl;
}


