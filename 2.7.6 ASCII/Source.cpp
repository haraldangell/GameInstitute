#include<iostream>

//Print out all ascii letters 

using namespace std;


int main()
{
	for (int i = 33; i <= 255; i++)
		cout << i << ": " << (char)i << " ";
	cout << endl;
	return 0;
}