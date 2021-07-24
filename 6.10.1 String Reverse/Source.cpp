#include<iostream>
#include<string>
//For the following exercises you can use c-strings or std::string or a combination of both.

/*
Write a program that does the following:
1. Ask the user to enter up to a line of text and store it in a string s.
2. Reverse the string s.
3. Output the reversed string to the console window.
Your program output should look like this:
Enter a string: Hello, World!
Reversed string = !dlroW

*/

using namespace std;


int main()
{
	string input = "";
	cout << "Enter a string: ";
	getline(cin, input);
	//cin >> input;
	cout << "Reversed string = ";
	for (int i = input.size(); i >= 0; i--)
		cout << input[i];

	cout << endl;
	return 0;
}