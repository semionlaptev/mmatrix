#pragma once

/*

	matrix_rotation_matrix
		Stores rotation matrix. Angle(or angles for 3d) is specified thru the constructor or by function setAngle.

	constructors:
		template matrix_rotation_matrix<T, 2>
			matrix_rotation_matrix(T angle) 
				creates a matrix that will rotate 2d vector by the value of 'angle' ;
		template matrix_rotation_matrix<T, 3>
			matrix_rotation_matrix(T X, T Y, T Z);
				creates a matrix that will rotate 3d vector by the values of X,Y,Z; 
			matrix_rotation_matrix(const T(&inarr)[3])
			The angles are set by the input array
	methods:
		template matrix_rotation_matrix<T, 2>
			setAngle(angle)
		template matrix_rotation_matrix<T, 3>
			setAngle(X,Y,Z)
				sets the angles of the rotation;
	typedefs:

		typedef matrix_rotation_matrix<float,2> RotMatrix2f;
		typedef matrix_rotation_matrix<float,3> RotMatrix3f;
		typedef matrix_rotation_matrix<double,2> RotMatrix2d;
		typedef matrix_rotation_matrix<double,3> RotMatrix3d;

*/

#include "mmatrix.h"
#include "math.h"

template<class T, int RC> class matrix_rotation_matrix;

//rotation in 2d
template<class T> 
class matrix_rotation_matrix<T, 2>:
	public MMatrix<T,2,2>
{
private:
	T angle_;

public:
	matrix_rotation_matrix();
	matrix_rotation_matrix(const MMatrix &inparent):MMatrix(inparent){}; //to inherit overloaded operators
	matrix_rotation_matrix(T angle);
	void setAngle(T angle);

};

template<class T> 
matrix_rotation_matrix<T,2>::matrix_rotation_matrix()
{
	loadIdentity();
}

template<class T> 
matrix_rotation_matrix<T,2>::matrix_rotation_matrix(T angle):
	angle_(angle)
{
	setAngle(angle);
}

template<class T> 
void matrix_rotation_matrix<T,2>::setAngle(T angle)
{
	const T rotatematrix[] = {
		cos(angle), -sin(angle),
		sin(angle),	cos(angle)
	};

	copy(rotatematrix);
}

//rotation in 3d
template<class T> 
class matrix_rotation_matrix<T, 3> :
	public MMatrix<T,3,3>
{

private:
	T xAngle_, yAngle_, zAngle_;
public:

	matrix_rotation_matrix();
	//template<class U>
	matrix_rotation_matrix(const T(&inarr)[3])
	{
		setAngle(inarr[0], inarr[1], inarr[2]);	
	}

	matrix_rotation_matrix(const MMatrix &inparent):MMatrix(inparent){};
	matrix_rotation_matrix(T X, T Y, T Z);
	void setAngle(T X, T Y, T Z);

};

template<class T> 
matrix_rotation_matrix<T,3>::matrix_rotation_matrix()
{
	loadIdentity();
}

template<class T> 
matrix_rotation_matrix<T, 3>::matrix_rotation_matrix(T X, T Y, T Z)
	:xAngle_(X), yAngle_(Y), zAngle_(Z)
{
	setAngle(xAngle_, yAngle_, zAngle_);
}

template<class T> 
void matrix_rotation_matrix<T, 3>::setAngle(T X, T Y, T Z)
{
	//some angles checks?
	const T rotatematrix[] = {
		cos(Y)*cos(Z),	-cos(X)*sin(Z)+sin(X)*sin(Y)*cos(Z),	sin(X)*sin(Y) + cos(X)*sin(Y)*cos(Z),
		cos(Y)*sin(Z),	cos(X)*cos(Z)+sin(X)*sin(Y)*sin(Z),		-sin(X)*cos(Z) + cos(X)*sin(Y)*sin(Z),
		-sin(Y),		sin(X)*cos(Y),							cos(X)*cos(Y)
	};
	copy(rotatematrix);
}

//typedefs

typedef matrix_rotation_matrix<float,2> RotMatrix2f;
typedef matrix_rotation_matrix<float,3> RotMatrix3f;
typedef matrix_rotation_matrix<double,2> RotMatrix2d;
typedef matrix_rotation_matrix<double,3> RotMatrix3d;