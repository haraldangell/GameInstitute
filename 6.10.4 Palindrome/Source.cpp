#include<iostream>
#include<string>
#include <algorithm> 
using namespace std;
/*
Dictionary.com defines a palindrome as follows: “A word, phrase, verse, or sentence that reads the same
backward or forward. For example: A man, a plan, a canal, Panama!” For our purposes, we will
generalize and say that a palindrome can be any string that reads the same backwards or forwards and
does not have to form a real word or sentence. Thus, some simpler examples may be:
“abcdedcba”
“C++C”
“ProgrammingnimmargorP”
Write a program that does the following:
1. Asks the user to enter up to a line of text and store it in a string s.
2. Tests if the string s is a palindrome.
3. If s is a palindrome then output “s is a palindrome” else output “s is not a palindrome.”
Your program output should look like this:

Enter a string: Hello, World!
Hello, World! is not a palindrome
Press any key to continue
Another sample output:
Enter a string: abcdedcba
abcdedcba is a palindrome
Press any key to continue

*/

int main()
{
	while (true)
	{
		string s = "";
		bool t = true;
		cout << "Enter a string: ";
		getline(cin, s);
	
		for (unsigned int i = 0, j = s.size() - 1; i < s.size(); ++i, j--)
			if (s[i] == s[j])
			{
				t = false;
				break;
			}
		cout << endl;
		if(!t)
			cout << s << " is  a palindrome" << endl;
		else
			cout << s << " is not a palindrome" << endl;
	}


	return 0;
}