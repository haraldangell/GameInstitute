#include<iostream>
/*

*/

using namespace std;

char ToUpperCase(char input);
char ToLowerCase(char input);

int main()
{
	cout << ToUpperCase('a') << ToLowerCase('H');

	string str = "1IMblVWSSbJEImTiW6soTVfxbHNeYMvXDOg6Yy0HvMySM5Jo25CMLEkK6JtkIf5 ";
	for (int i = 0; i < str.size(); ++i)
		cout << ToLowerCase(str[i]);

	return 0;
}

char ToUpperCase(char input)
{
	if (input > 'a' || input < 'z')
		return input - 32;
	return input;
}
char ToLowerCase(char input)
{
	if (input > 'A' || input < 'Z')
		return input + 32;
	return input;
}