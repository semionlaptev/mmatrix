#pragma once
/*
	Matrix_container class.
		This class represents a container that stores a 2d matrix in a linear array.
	The template sets the type of the stored data(T) and size of the matrix(R,C).

	Uses some code and approaches from a matrix class by Gaspard Petit http://www-etud.iro.umontreal.ca/~petitg/

	constructors:
	
		Matrix_container(void);
			does nothing. In this case the array contains uninitialized values 
			and can cause troubles if you forget to fill the matrix manualy;
		Matrix_container(const T(&initarray)[R*C]);
			copies values from the input constant array into the matrix. The input array must be R*C length.
		Matrix_container(const Matrix_container &copymatrix);
			Copy constructor that copies values from the input matrix;

	public methods:
	
		void output() - prints the matrix to a console;
		void copy(const T(&initarray)[R*C]) - copies values from 'inarray' to 'matrix'. Input array must be R*C length;
		void copy(const Matrix_container &inmatrix) - copies the matrix from the input object. 
			The input matrix must be the same size and have the same internal data type.
	
	overloaded operators:
	
		operator=
			overloads assignment operator that copies a matrix from the right object to the left. 
			Returns a reference to itself object, so you can use it as a = b = c;
		operator(int)
			...
		operator(int,int)
			usage: m(r,c). accesses an matrix element in r'th row and c'th columns. 
				Returns a reference to this element, so you can change its value;

		--deleted--
		//operator[]
		//	usage: m[r][c] - the same functionality, but try to avoid using this, 
		//	because it doesn't check r and c parametres. 
		//	Overloaded operator [] returns a pointer to the first element from r'th row so 
		//	m[r][c] works as *((m[r])+c);
*/

#include <iostream>
#include <assert.h>

template<class T, int R, int C> class Matrix_container
{
private:
	
	T matrix[R*C];
	unsigned int length() const;

public:
	
	//constructors

	Matrix_container(void);
	Matrix_container(const T(&initarray)[R*C]);
	Matrix_container(const Matrix_container &copymatrix);

	//~Matrix_container();

	//methods

	void output() const;
	void copy(const T(&copyarray)[R*C]);

	template <class U>
	void copy(const Matrix_container<U,R,C> &obj);

	//overloaded operators
	//assigment
	Matrix_container &operator=(const Matrix_container &obj);
	template <class U>
	Matrix_container &operator=(const Matrix_container<U,R,C> &obj);

	T& operator()(unsigned int rowindex, unsigned int colindex);	//for changing internal matrix
	const T& operator()(unsigned int rowindex, unsigned int colindex) const;
	T& operator()(unsigned int index);	//for changing internal matrix
	const T& operator()(unsigned int index) const;

	T* operator[](unsigned int index);	//for changing internal matrix
	const T* operator[](unsigned int index) const;

};

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container()
{
	#ifdef _DEBUG_
		cout<<"Matrix_container default constructor called"<<endl;
	#endif
}

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container(const T(&initarray)[R*C])
{
	#ifdef _DEBUG_
		cout<<"Matrix_container array constructor called"<<endl;
	#endif
	copy(initarray);
}

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container(const Matrix_container<T,R,C> &obj)
{
	#ifdef _DEBUG_
		cout<<"Matrix_container copy constructor called"<<endl;
	#endif
	copy(obj);
}

template<class T, int R, int C> 
unsigned int Matrix_container<T,R,C>::length() const
{
	return R*C;
}

template<class T, int R, int C> 
void Matrix_container<T,R,C>::output() const
{
	for (int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{
			std::cout<<matrix[j+i*R]<<" ";
		}
		std::cout<<std::endl;
	}
}

template<class T, int R, int C> 
void Matrix_container<T,R,C>::copy(const T(&copyarray)[R*C])
{
	memcpy(matrix, &copyarray, length()*sizeof(T));
}

template<class T, int R, int C> template <class U>
void Matrix_container<T,R,C>::copy(const Matrix_container<U,R,C> &obj)
{
	for(int i=0;i<R;i++)
		for(int j=0;j<C;j++)
			(*this)(i,j) = (T)obj(i,j);
}

template<class T, int R, int C> 
Matrix_container<T,R,C> &Matrix_container<T,R,C>::operator=(const Matrix_container &obj)
{
	#ifdef _DEBUG_
		cout<<"Matrix_container selftype operator=(Matrix_container) called."<<endl;
	#endif

	if(this != &obj)
		copy(obj);
	return *this; 
}

template<class T, int R, int C> template <class U>
Matrix_container<T,R,C> &Matrix_container<T,R,C>::operator=(const Matrix_container<U, R, C> &obj)
{
	#ifdef _DEBUG_
		cout<<"Matrix_container template operator=(Matrix_container<U,R,C>) called."<<endl;
	#endif

	copy(obj);
	return *this; 
}

template<class T, int R, int C> 
T& Matrix_container<T,R,C>::operator()(unsigned int rowindex, unsigned int colindex)
{
	assert(rowindex>=0 && rowindex < R && colindex>=0 && colindex < C);
	return matrix[colindex+rowindex*R];
}

template<class T, int R, int C>
const T& Matrix_container<T,R,C>::operator()(unsigned int rowindex, unsigned int colindex) const
{
	assert(rowindex>=0 && rowindex < R && colindex>=0 && colindex < C);
	return matrix[colindex+rowindex*R];
}

//
template<class T, int R, int C> 
T& Matrix_container<T,R,C>::operator()(unsigned int index)
{
	assert(index>=0 && index < length());
	return matrix[index];
}

template<class T, int R, int C>
const T& Matrix_container<T,R,C>::operator()(unsigned int index) const
{
	assert(index>=0 && index < length());
	return matrix[index];
}
//

/*template<class T, int R, int C> 
T* Matrix_container<T,R,C>::operator[](unsigned int index)
{
	//impossible to check ranges in this implementation
	return &matrix[index*C];
}

template<class T, int R, int C> 
const T* Matrix_container<T,R,C>::operator[](unsigned int index) const
{
	//impossible to check ranges in this implementation
	return &matrix[index*C];
}*/
