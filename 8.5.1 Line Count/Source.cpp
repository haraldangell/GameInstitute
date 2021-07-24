#include <iostream>
#include <fstream>
#include <string>
/*
Enter a text file: C:/Data/file.txt
C:/Data/file.txt contained 478 lines.
*/

using namespace std;


int main()
{
	//ofstream outFile("test.txt");
	//if (outFile)
	//{
	//	for (int i = 0; i < 50; ++i)
	//		outFile << "Testing " << i << "lines" << endl;

	//	outFile.close();
	//}


	string str = "";
	cout << "Enter a text file: ";
	getline(cin, str);
	int counter = 0;
	ifstream inFile(str);
	if (inFile)
	{
		while (!inFile.eof())
		{
			string data;
			getline(inFile, data);
			counter++;

		}
		inFile.close();
		cout << str << " contained " << counter << " lines" << endl;
	}
	else
		cout << "Didn't load the file!!!" << endl;


	return 0;
}