// mmatrix.h

/*
	MMatrix class.
	This class provides matrix arithmetical operations. It has Matrix_container as the parent class, 
	and uses it as a container for the matrix;

	constructors:
	MMatrix(void)
		Default constructor loads a zero numerical matrix.
	and just the same as in the parent class;

	methods:

	void loadZero(const T &defval);
		fills the matrix with the default value specified by the parameter 'defval' 
	void loadZero();
		fills the matrix with zero;

	void loadIdentity(const T &oneval, const T &zeroval);
		fills the matrix with an identity matrix where ones are specified by 'oneval' and zeros by 'zeroval'
	void loadIdentity();
		fills the matrix with an identity matrix where ones are numerical 1 and zeros are 0;

	static const MMatrix<T, RC, RC>& identity()
		returns a referense to a const object filled with an identity numerical matrix (RCxRC).
		An example of the usage:
			const Matrix2f ident1 = Matrix2f::identity();
			vector1 = vector1*ident1*vector2;

	static const MMatrix& zero()
		returns a referense to a const object filled with a zero numerical matrix (RCxRC).

	overloaded operators:
		all operators implemented in the parent container class could be used with MMatrix.
		
	operator*(const MMatrix<T,C,RC> &inmatrix)
		performs multiplication between two matricies. Retruns result in a new object
		L = A*B; matrix A (R,C), matrix B (C, RC); output matrix L (R, RC)

	typedefs:

	Vector2f - (1x2) float matrix
	Vector3f - (1x3) float matrix
	Matrix2f - (2x2) float matrix
	Matrix3f - (3x3) float matrix

*/
#pragma once

#include <iostream>
#include "matrix_container.h"

template<class T, int R, int C>	//n rows, m columns
class MMatrix : public Matrix_container<T,R,C>
{
private:
	//nothing yet hear

public:

	MMatrix(void){ loadZero(); }
	MMatrix(const T(&initarray)[R*C]): Matrix_container<T,R,C>(initarray){};
	MMatrix(const MMatrix &initmatrix): Matrix_container<T,R,C>(initmatrix){};

	void loadZero();
	void loadZero(const T &defval);

	void loadIdentity();
	void loadIdentity(const T &oneval, const T &zeroval);

	static const MMatrix& identity()
	{

		static MMatrix<T,R,C> _ident;
		static bool _identloaded = false;

		if(!_identloaded)
		{
			_ident.loadIdentity();
			_identloaded = true;
		}
		return _ident;

	}
	static const MMatrix& zero()
	{
		static MMatrix<T,R,C> _zero;
		static bool _zeroloaded = false;

		if(!_zeroloaded)
		{
			_zero.loadZero();
			_zeroloaded = true;
		}
		return _zero;
	}

	//transpose()

	//overloaded operators
	
	template <int RC>
	MMatrix<T,R,RC> operator*(const MMatrix<T, C, RC> &inmatrix);

};

template <class T, int R, int C> template <int RC>
MMatrix<T,R,RC> MMatrix<T,R,C>::operator* (const MMatrix<T,C,RC> &inmatrix)
{
	MMatrix<T,R,RC> multmatrix; //init a matrix
	multmatrix.loadZero();

	//L = A*B; matrix A (R,C), matrix B (C, RC); output matrix L (R, RC)
	//inmatrix.output();

	for (int r=0; r<C; r++)
		for (int i=0; i<R; i++) 
			for(int j=0; j<RC; j++)
				multmatrix(i,j) += (*this)(i,r)*inmatrix(r,j);

	return multmatrix;
}

template<class T, int R, int C>
void MMatrix<T,R,C>::loadZero(const T& defval)
{
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			(*this)(i,j) = defval;
}

template<class T, int R, int C>
void MMatrix<T,R,C>::loadZero()
{
	loadZero(0);
}

template<class T, int R, int C>
void MMatrix<T,R,C>::loadIdentity(const T &oneval, const T &zeroval)
{
	assert(R==C);
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			if(i == j)
				(*this)(i,j) = oneval;
			else
				(*this)(i,j) = zeroval;
}

template<class T, int R, int C>
void MMatrix<T,R,C>::loadIdentity()
{
	assert(R==C);
	loadIdentity(1,0);
}

//typedefs
typedef MMatrix<float,1,2> Vector2f;
typedef MMatrix<float,1,3> Vector3f;
typedef MMatrix<float,2,2> Matrix2f;
typedef MMatrix<float,3,3> Matrix3f;
