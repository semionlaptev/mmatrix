#pragma once

/*
	This class represents a container that stores a 2d matrix in a linear array.
	The template sets the type of the stored data(T) and size of the matrix(R,C).

	constructors:
	
	public methods:
	
	void output() - prints the matrix to a console;
	void copy(const T *inarray) - copies values from 'inarray' to 'matrix'. Doesn't check the length of the input array;
	void copy(const Matrix_container &inmatrix) - copies the matrix from the input object. 
		The input matrix must be the same size and have the same internal data type.
	
	overloaded operators:
	
	= - overloads assignment operator that copies a matrix from the right object to the left. 
		Returns a reference to itself object, so you can use it as a = b = c;
	m(r,c) - access an matrix element in r'th row and c'th columns. 
			Returns a reference to this element, so you can change its value;
	m[r][c] - the same functionality, but try to avoid using this, because it doesn't check r and c parametres. 
				Overloaded operator [] returns a pointer to the first element from r'th row so m[r][c] works as (m[r])[c];
*/

#include <iostream>
#include <assert.h>

template<class T, int R, int C> class Matrix_container
{
private:
	
	T matrix[R*C];
	int length();

public:
	
	Matrix_container(void);
	Matrix_container(const T *initarray);
	Matrix_container(const Matrix_container &copymatrix);

	~Matrix_container();

	//methods

	void output();
	void copy(const T *copyarray);
	void copy(const Matrix_container &obj);

	//overloaded operators
	Matrix_container &operator=(const Matrix_container &obj);
	T& operator()(unsigned int rowindex, unsigned int colindex);	

	T* operator[](unsigned int index);
	const T* operator[](unsigned int index) const;
};

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container()
{
	int x = 1;
}

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container(const T *initarray)
{
	copy(initarray);
}

template<class T, int R, int C> 
Matrix_container<T,R,C>::Matrix_container(const Matrix_container<T,R,C> &obj)
{
	copy(obj);
}

template<class T, int R, int C> 
Matrix_container<T,R,C>::~Matrix_container()
{

}

template<class T, int R, int C> 
int Matrix_container<T,R,C>::length()
{
	return R*C;
}

template<class T, int R, int C> 
void Matrix_container<T,R,C>::output()
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
void Matrix_container<T,R,C>::copy(const T *copyarray)
{
	memcpy(matrix, copyarray, length()*sizeof(T));
}

template<class T, int R, int C> 
void Matrix_container<T,R,C>::copy(const Matrix_container &obj)
{
	copy(obj.matrix);
}

template<class T, int R, int C> 
Matrix_container<T,R,C> &Matrix_container<T,R,C>::operator=(const Matrix_container &obj)
{
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
}
