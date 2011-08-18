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
				const Matrix2f ident1(Matrix2f::identity())
				vector1 = vector1*ident1*vector2;

		static const MMatrix& zero()
			returns a referense to a const object filled with a zero numerical matrix (RCxRC).

	overloaded operators:
		*all operators implemented in the parent container class could be used with MMatrix.
		
		operator*(const MMatrix<T,C,RC> &inmatrix)
			performs multiplication between two matricies. Retruns result in a new object
			L = A*B; matrix A (R,C), matrix B (C, RC); output matrix L (R, RC)
		operator-(), operator-= 
		operator+,operator+=
			Arithmetic operators for Matrices and numerical (scalar) values	
		operator==

		
	typedefs:

		Matrix2f - (2x2) float matrix
		Matrix3f - (3x3) float matrix
		Matrix2d - doble
		Matrix3d
		Matrix2i - integer
		Matrix3i

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

	MMatrix(void){ 
		#ifdef _DEBUG_
			cout<<"MMatrix default constructor called. Filling with zero metrix."<<endl;
		#endif
		loadZero();
	}
	MMatrix(const T(&initarray)[R*C]): Matrix_container<T,R,C>(initarray){
		#ifdef _DEBUG_
			cout<<"MMatrix array constrctor called. Proxying to the Base class array constr."<<endl;
		#endif
	};
	MMatrix(const MMatrix &initmatrix): Matrix_container<T,R,C>(initmatrix){
		#ifdef _DEBUG_
			cout<<"MMatrix copy constrctor called. Proxying to the Base class copy constr."<<endl;
		#endif
	};

	void loadZero();
	void loadZero(const T &defval);

	void loadIdentity();
	void loadIdentity(const T &oneval, const T &zeroval);

	static const MMatrix& identity();
	static const MMatrix& zero();

	//transpose()

	//overloaded operators
	
	//can be used with a matrix of any other data type that has arithmetical operations
	
	template<class U>
	MMatrix& operator=(const Matrix_container<U,R,C> &inmatrix);

	bool operator==(const MMatrix<T,R,C> &inmatrix) const;
	
	template <class U, int UC>
	MMatrix<T,R,UC> operator*(const MMatrix<U, C, UC> &inmatrix);

	template <class U, int UC>
	void operator*=(const MMatrix<U, C, UC> &inmatrix);
		
	// multiplicaton by a scalar

	MMatrix<T,R,C> operator*(const T &inscalar);
	void operator*=(const T &inscalar);

	//a matrix plus a matrix
	template <class U>
	MMatrix<T,R,C> operator+(const MMatrix<U,R,C> &inmatrix);
	template <class U>
	void operator+=(const MMatrix<U,R,C> &inmatrix);

	//a matrix minus a matrix
	template <class U>
	MMatrix<T,R,C> operator-(const MMatrix<U,R,C> &inmatrix);
	template <class U>
	void operator-=(const MMatrix<U,R,C> &inmatrix);

	//a matrix plus a scalar
	MMatrix<T,R,C> operator+(const T &inscalar);
	void operator+=(const T &inscalar);

	//a matrix minus a scalar
	MMatrix<T,R,C> operator-(const T &inscalar);
	void operator-=(const T &inscalar);

};

template <class T, int R, int C> template <class U>
MMatrix<T,R,C>& MMatrix<T,R,C>::operator=(const Matrix_container<U,R,C> &inmatrix)
{
	#ifdef _DEBUG_
		cout<<"MMatrix: template assignment operator=(Matrix_container<U,R,C>) called."<<endl<<"Proxying to Matrix_container::operator=() "<<endl;
	#endif

	Matrix_container::operator=(inmatrix);
	return *this;
}

//multiplication by a matrix
template <class T, int R, int C> template <class U, int UC>
MMatrix<T,R,UC> MMatrix<T,R,C>::operator* (const MMatrix<U,C,UC> &inmatrix)
{
	MMatrix<T,R,UC> multmatrix; //init the result matrix
	multmatrix.loadZero();

	//L = A*B; matrix A (R,C), matrix B (C, RC); output matrix L (R, RC)

	for (int r=0; r<C; r++)
		for (int i=0; i<R; i++) 
			for(int j=0; j<UC; j++)
				multmatrix(i,j) += (*this)(i,r)*(T)inmatrix(r,j);

	return multmatrix;
}
template <class T, int R, int C> template <class U, int UC>
void MMatrix<T,R,C>::operator*= (const MMatrix<U,C,UC> &inmatrix)
{
	(*this) = (*this)*inmatrix;
}

//multiplication by a scalar
template <class T, int R, int C> 
MMatrix<T,R,C> MMatrix<T,R,C>::operator* (const T &inscalar)
{
	MMatrix<T,R,C> multmatrix; //init the result matrix
	multmatrix.loadZero();

	for (int i=0; i<R; i++) 
		for(int j=0; j<C; j++)
			multmatrix(i,j) = (*this)(i,j)*(T)inscalar;

	return multmatrix;
}
template <class T, int R, int C> 
void MMatrix<T,R,C>::operator*=(const T &inscalar)
{
	(*this) = (*this)*inscalar;
}

//a matrix plus a scalar
template <class T, int R, int C>
MMatrix<T,R,C> MMatrix<T,R,C>::operator+ (const T &inscalar)
{
	MMatrix<T,R,C> multmatrix; //init the result matrix
	multmatrix.loadZero();

	for (int i=0; i<R; i++) 
		for(int j=0; j<C; j++)
			multmatrix(i,j) = (*this)(i,j)+(T)inscalar;

	return multmatrix;
}
template <class T, int R, int C>
void MMatrix<T,R,C>::operator+=(const T &inscalar)
{
	(*this) = (*this)+inscalar;
}

//a matrix minus a scalar
template <class T, int R, int C>
MMatrix<T,R,C> MMatrix<T,R,C>::operator- (const T &inscalar)
{
	MMatrix<T,R,C> multmatrix; //init the result matrix
	multmatrix.loadZero();

	for (int i=0; i<R; i++) 
		for(int j=0; j<C; j++)
			multmatrix(i,j) = (*this)(i,j)-(T)inscalar;

	return multmatrix;
}
template <class T, int R, int C>
void MMatrix<T,R,C>::operator-=(const T &inscalar)
{
	(*this) = (*this)-inscalar;
}

//operations between matrices
template<class T, int R, int C> template <class U>
MMatrix<T,R,C> MMatrix<T,R,C>::operator+(const MMatrix<U,R,C> &inmatrix)
{
	MMatrix<T,R,C> outmatrix;

	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			outmatrix(i,j) = (*this)(i,j)+(T)inmatrix(i,j);
	return outmatrix;
}
template<class T, int R, int C> template <class U>
MMatrix<T,R,C> MMatrix<T,R,C>::operator-(const MMatrix<U,R,C> &inmatrix)
{
	MMatrix<T,R,C> outmatrix;

	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			outmatrix(i,j) = (*this)(i,j)-(T)inmatrix(i,j);
	return outmatrix;
}
template<class T, int R, int C> template <class U>
void MMatrix<T,R,C>::operator+=(const MMatrix<U,R,C> &inmatrix)
{
	(*this) = (*this) + inmatrix;
}
template<class T, int R, int C> template <class U>
void MMatrix<T,R,C>::operator-=(const MMatrix<U,R,C> &inmatrix)
{
	(*this) = (*this) - inmatrix; //beter go another way but im to lazy for it
}
//equality operator
template<class T, int R, int C>
bool MMatrix<T,R,C>::operator==(const MMatrix<T,R,C> &inmatrix) const
{
	bool identical = true;
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			if((*this)(i,j)!=inmatrix(i,j))
			{
				identical = false;
				break;
			}
	return identical;
}

//load some of the default matrices
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
template<class T, int R, int C>
const MMatrix<T,R,C>& MMatrix<T,R,C>::identity()
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
template<class T, int R, int C>
const MMatrix<T,R,C>& MMatrix<T,R,C>::zero()
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

/*template<class T, int R, int C>
const MMatrix<float,3,3>& MMatrix<T,R,C>::rotMatrix(float x, float y, float z)
{
	return (*this);
}*/

//typedefs
typedef MMatrix<float,1,2> Vector2f;
typedef MMatrix<float,2,2> Matrix2f;
typedef MMatrix<float,3,3> Matrix3f;

typedef MMatrix<double,1,2> Vector2d;
typedef MMatrix<double,2,2> Matrix2d;
typedef MMatrix<double,3,3> Matrix3d;

typedef MMatrix<int,1,2> Vector2i;
typedef MMatrix<int,2,2> Matrix2i;
typedef MMatrix<int,3,3> Matrix3i;
