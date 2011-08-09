#include <iostream>
#include "windows.h"
#include "mmatrix.h"

using namespace std;

int main()
{
	const float initmatrix[] = {
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	};
	;
	const float xvector[] = {1,0,0};

	MMatrix<float,1,3> vector1(xvector);

	vector1.output();

	system("pause");

	return 0;
}
