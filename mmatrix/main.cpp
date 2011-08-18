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

	const int ini[] = {
		1,2,3,
		4,5,6,
		7,8,9
	};


	/*
	MMatrix<float,3,3> m1(in);
	MMatrix<float,3,3> m2(in);

	MMatrix<int,3,3> m3(ini);

	RotMatrix3f r1(0,0,0);
	m2.copy(m1);

	v2.copy(v1);
	
	cout<<endl;

	cout<<"MMatrix<float> = MMatrix<float>"<<endl;
	m1 = m2;
	cout<<endl;
	cout<<"MMatrix<float> = MMatrix<int>"<<endl;
	m1 = m3;
	cout<<endl;
	cout<<"MMatrix<int> = RotMatrix<float>"<<endl;
	m3 = r1;*/

	matrix_3dvector<float> v1(1,0,0);
	matrix_3dvector<int> v2(1,2,0);

	cout<<endl;
	
	v2.output();

	system("pause");

	return 0;
}
