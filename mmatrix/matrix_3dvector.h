/*
	Class that represents 3d vector (x,y,z);
	constructors:
		default
			loads identity matrix
		matrix_3dvector(x,y,z)
			creates x,y,z vector
	
	methods:
		set(x,y,z)
			sets x,y,z values
		x(), y(), z() 
			returns x, y or z value
		vectorLength
			returns the length of the vector

	typedefs:
		typedef matrix_3dvector<float> Vector3f;
		typedef matrix_3dvector<double> Vector3d;
		typedef matrix_3dvector<int> Vector3i;
*/

#pragma once

#include "mmatrix.h"
#include <math.h>

template<class T>
class matrix_3dvector:
	public MMatrix<T,1,3>
{

public:

	matrix_3dvector(void)
	{
		#ifdef _DEBUG_
			cout<<"matrix_3dvector default constructor called."<<endl;
		#endif
	}

	matrix_3dvector(const MMatrix &inparent):MMatrix(inparent){
		#ifdef _DEBUG_
			cout<<"matrix_3dvector array constructor called. Proxying to the MMatrix constr."<<endl;
		#endif
	}

	void set(const T &x, const T &y, const T &z);

	matrix_3dvector(const T &x, const T &y, const T &z);

	const T& x() const { return (*this)(0); };
	const T& y() const{ return (*this)(1); };
	const T& z() const{ return (*this)(2); };
	float vectorLength() {return sqrt((x()-y())^2+(x()-z())^2+(y()-z()^2)) } //haven't checked it yet

	template<class U>
	matrix_3dvector& operator=(const MMatrix<U,1,3> &rhs);

};

template<class T> matrix_3dvector<T>::matrix_3dvector(const T &x, const T &y, const T &z)
{
	
	#ifdef _DEBUG_
		cout<<"matrix_3dvector parameter constructor called."<<endl;
	#endif

	set(x,y,z);
}

template<class T> template<class U>
matrix_3dvector<T>& matrix_3dvector<T>::operator=(const MMatrix<U,1,3> &rhs)
{
	#ifdef _DEBUG_
		cout<<"matrix_3dvector temaplte operator=(MMatrix<U,1,3>) called."<<endl<<"Proxying to MMatrix::operator=()"<<endl;
	#endif
	MMatrix::operator=(rhs);
	return (*this);
}

template<class T> void matrix_3dvector<T>::set(const T &x, const T &y, const T &z)
{
	const T initarray[] = {x,y,z};
	copy(initarray);
}

typedef matrix_3dvector<float> Vector3f;
typedef matrix_3dvector<double> Vector3d;
typedef matrix_3dvector<int> Vector3i;
