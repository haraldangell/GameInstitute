#include<iostream>
#include<string>

/*
Write a program that does the following:
1. Ask the user to enter up to a line of text and store it in a string s.
2. Transform each alphabetical character in s into its uppercase form. If a character is not analphabetical character—do not modify it.
3. Output the uppercase string to the console window.


Your program output should look like this:
Enter a string: Hello, World!
Uppercase string = HELLO, WORLD!
Press any key to continue

*/
using namespace std;
char ToUpperCase(char input);
char ToLowerCase(char input);

int main()
{
	while (true)
	{
		string s = "";
		cout << "Enter a string: ";
		getline(cin, s);
		cout  << "Uppercase string = ";
		for (auto i = 0; i < s.size(); ++i)
			cout << ToUpperCase(s[i]);
		cout << endl;
		cout << "Lowercase string = ";
		for (auto i = 0; i < s.size(); ++i)
			cout << ToLowerCase(s[i]);
		cout << endl;
		cout << "String not changed = ";
		for (auto i = 0; i < s.size(); ++i)
			cout << s[i];
		cout << endl;

		cout << "Std Uppercase string = ";
		for (auto i = 0; i < s.size(); ++i)
			cout << (char)toupper(s[i]);
		cout << endl;
		cout << "Std Lowercase string = ";
		for (auto i = 0; i < s.size(); ++i)
			cout << (char)tolower(s[i]);

		cout << endl;
	}


	return 0;
}
char ToUpperCase(char input)
{
	if (input >= 'a' && input <= 'z')
		return input - 32;
	return input;
}
char ToLowerCase(char input)
{
	if (input >= 'A' && input <= 'Z')
		return input + 32;
	return input;
}