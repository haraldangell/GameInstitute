#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>

using namespace std;
void RandomArrayFill(vector<int> & vec);

int main()
{
	srand(time(0));
	auto size = 0;
	vector<int> array;
	cout << "Enter the size of an array to create : ";
	cin >> size;
	array.resize(size);
	RandomArrayFill(array);
	cout << "Array = {";
	for (auto i = 0; i < size; ++i)
		if (i == size - 1)
			cout << array[i];
		else
			cout << array[i] << ", ";
	cout << "}" << endl;


	return 0;
}

void RandomArrayFill(vector<int> & vec)
{
	for (auto i = 0; i < vec.size(); ++i)
		vec[i] = rand() % 100;
}
