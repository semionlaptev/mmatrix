#include <iostream>
#include <time.h>
#include <math.h>

#include "windows.h"
#include "mmatrix.h"
//#include "test.h"

using namespace std;

#define PI (3.141592653589793f)
#define ANGLE PI

int main()
{

    const float yvector[] = {0,1,0};

	//rotate around x axis
	const float xrotmatrix[] = {
		1,		0,			0,
		0, cos(ANGLE), -sin(ANGLE),
		0, sin(ANGLE), cos(ANGLE)
	};

	Vector3f vector1(yvector);
	Matrix3f rotmatrix(xrotmatrix);

	//vector1.output();
	
	cout<<*((vector1[0])+1);
	vector1 = vector1*rotmatrix;
	//vector1.output();

	system("pause");

	return 0;
}
