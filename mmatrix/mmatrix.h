// mmatrix.h

/*
	My matrix class.
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

	MMatrix(void){}
	MMatrix(const T *initarray): Matrix_container<T,R,C>(initarray){};
	MMatrix(const MMatrix &initmatrix): Matrix_container<T,R,C>(initmatrix){};

	~MMatrix(){}

	//transpose()

	//overloaded operators

};