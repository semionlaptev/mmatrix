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

	typedefs:
		typedef matrix_3dvector<float> Vector3f;
		typedef matrix_3dvector<double> Vector3d;
		typedef matrix_3dvector<int> Vector3i;
*/

#pragma once

#include "mmatrix.h"

template<class T>
class matrix_3dvector:
	public MMatrix<T,1,3>
{

public:

	matrix_3dvector(void)
	{
		loadZero();
	}

	matrix_3dvector(const MMatrix &inparent):MMatrix(inparent){}

	void set(const T &x, const T &y, const T &z);
	matrix_3dvector(const T &x, const T &y, const T &z);

	const T& x() const { return (*this)(0); };
	const T& y() const{ return (*this)(1); };
	const T& z() const{ return (*this)(2); };

};

template<class T> matrix_3dvector<T>::matrix_3dvector(const T &x, const T &y, const T &z)
{
	set(x,y,z);
}

template<class T> void matrix_3dvector<T>::set(const T &x, const T &y, const T &z)
{
	const T initarray[] = {x,y,z};
	copy(initarray);
}

typedef matrix_3dvector<float> Vector3f;
typedef matrix_3dvector<double> Vector3d;
typedef matrix_3dvector<int> Vector3i;
