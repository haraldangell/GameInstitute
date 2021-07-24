#include <iostream>
#include <string>
#include "Table.hpp"

using namespace std;
template <class T>
void Print(Table<T>& table, int a, int b)
{
	for (auto i = 0; i < a; ++i)
	{
		for (auto y = 0; y < b; ++y)
		{
			cout << table(i, y) << " ";
		}
		cout << endl;
	}
}
int main()
{

	int a = 2;
	int b = 3;
	int ta[2][3] = { { -5, 2, 8 },{ 1, 0, 0 } };
	int tb[2][3] = { { 1, 0, 2 },{ 0, 3, -6 } };
	Table<int> tableOne(a, b);
	tableOne(0, 0) = -5;
	tableOne(0, 1) = 2;
	tableOne(0, 2) = 8;
	tableOne(1, 0) = 1;
	tableOne(1, 1) = 0;
	tableOne(1, 2) = 0;
	Table<int> tableTwo(a,b);
	tableTwo(0, 0) = 1;
	tableTwo(0, 1) = 0;
	tableTwo(0, 2) = 2;
	tableTwo(1, 0) = 0;
	tableTwo(1, 1) = 3;
	tableTwo(1, 2) = -6;
	Table<int> tableTree(a, b);
	tableTree(0, 0) = tableOne(0, 0) + tableTwo(0, 0);
	for (auto i = 0; i < a; ++i)
	{
		for (auto y = 0; y < b; ++y)
		{
			 tableTree(i, y) = tableOne(i, y) + tableTwo(i, y);
		}

	}
	cout << "A = " << endl;
	Print(tableOne, a, b);
	cout << endl << "B = " << endl;
	Print(tableTwo, a, b);
	cout << endl << "A + B = " << endl;
	Print(tableTree, a, b);

	cout << endl;
}