#include "UtilFunctions.h"


//////////////////////////////////////////
template<class T> T* CreateArray1( int n )
{
	T *a = new T[n];
	return a;
};


//////////////////////////////////////////
template<class T> T** CreateArray2( int n1, int n2 )
{
	T** a = new T*[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{
		a[i1] = new T[n2];
	}

	return a;
}

//////////////////////////////////////////
template<class T> T*** CreateArray3( int n1, int n2, int n3 )
{
	T*** a = new T**[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{
		a[i1] = new T*[n2];

		for (int i2 = 0; i2 < n2; i2++)
		{
			a[i1][i2] = new T[n3];
		}
	}

	return a;
}

//////////////////////////////////////////
template<class T> T**   CreateCustomArray2 ( int n1, int *n2 )
{
	T** a = new T*[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{
		a[i1] = new T[n2[i1]];
	}

	return a;
}

/////////////////////////////
// PtrAllocating functions //
/////////////////////////////

//////////////////////////////////////////
template<class T> T** CreatePtrArray1( int n )
{
	T **a = new T*[n];
	return a;
};

//////////////////////////////////////////
template<class T> T*** CreatePtrArray2( int n1, int n2 )
{
	T ***a = new T**[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{

		a[i1] = new T*[n2];

	}

	return a;
};


//////////////////////////////////////////
template<class T> T**** CreatePtrArray3( int n1, int n2, int n3 )
{
	T ****a = new T***[n1];

	for (int i1 = 0; i1 < n1; i1++)
	{

		a[i1] = new T**[n2];

		for (int i2 = 0; i2 < n2; i2++)
		{
			a[i1][i2] = new T*[n3];

		}
	}
	return a;
};


// explicit instantiations
// template class Foo<int>;
// template class Foo<float>;


//template class CreateArray1   	<double>;
//template class CreateArray2   	<double>;
//template class CreateArray2   	<double>;
//template class CreateCustomArray2<double>;
//template class CreatePtrArray1 	<double>;
//template class CreatePtrArray2 	<double>;
//template class CreatePtrArray2 	<double>;

void InstantiateFuncs()
{

	int val[2] = {1,2};

	CreateArray1   	<double>(1);
	CreateArray2   	<double>(1,2);
	CreateArray3   	<double>(1,2,3);
	CreateCustomArray2<double>(1,val);
	CreatePtrArray1 	<double>(1);
	CreatePtrArray2 	<double>(1,2);
	CreatePtrArray3 	<double>(1,2,3);

	CreateArray1   	<TVectorD>(1);
	CreateArray2   	<TVectorD>(1,2);
	CreateArray3   	<TVectorD>(1,2,3);
	CreateCustomArray2<TVectorD>(1,val);
	CreatePtrArray1 	<TVectorD>(1);
	CreatePtrArray2 	<TVectorD>(1,2);
	CreatePtrArray3 	<TVectorD>(1,2,3);
}
