#include <iostream>
#include <time.h>
#include <math.h>

#include "windows.h"
#include "mmatrix.h"
#include "matrix_3dvector.h"
#include "matrix_rotation_matrix.h"
//#include "test.h"

using namespace std;

#define PI (3.141592653589793f)
#define ANGLE PI

int main()
{
	//Vector3f vect1(1,2,3);

	const float in[] = {
		1,2,3,
		4,5,6,
		7,8,9
	};

	RotMatrix3f rot(PI/2,0,0);
	
	Matrix3f v1(in);
	Matrix3f v2(in);

	RotMatrix3f rot1(PI/2,0,0);

	v2(8) = 3;
	v2.output();

	if(v1 == v2)
		v1.output();
	else
		cout<<"not";

	system("pause");

	return 0;
}
