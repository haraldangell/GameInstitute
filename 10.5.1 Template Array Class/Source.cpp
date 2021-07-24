#include "TempArray.h"
#include <iostream>

using namespace std;

template<class T>
void PrintFloatArray(TempArray<T>& fa)
{
	cout << "{ ";
	for (int i = 0; i < fa.size(); ++i)
		cout << fa[i] << " ";
	cout << "}" << endl << endl;
}



int main()
{

	TempArray<float> A(3);
	A.resize(4);
	A[0] = 1.0f;
	A[1] = 2.0f;
	A[2] = 3.0f;
	A[3] = 4.0f;
	cout << "Printing A: ";
	PrintFloatArray(A);

	TempArray<float> B(A);
	cout << "Printing B: ";
	PrintFloatArray(B);

	TempArray<float> C = B = A;
	cout << "Printing C: ";
	PrintFloatArray(C);
	A = A = A = A;
	cout << "Printing A: ";
	PrintFloatArray(A);

	return 0;
}