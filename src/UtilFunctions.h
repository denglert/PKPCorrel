#ifndef UTILFUNCTIONS_H
#define UTILFUNCTIONS_H

#include <TVectorD.h>

// Template functions for memory allocation

template<class T> T*    CreateArray1   	 ( int n                  );
template<class T> T**   CreateArray2   	 ( int n1, int n2         );
template<class T> T***  CreateArray3   	 ( int n1, int n2, int n3 );

template<class T> T**   CreateCustomArray2 ( int n1, int *n2 );

template<class T> T**   CreatePtrArray1( int n                  );
template<class T> T***  CreatePtrArray2( int n1, int n2         );
template<class T> T**** CreatePtrArray3( int n1, int n2, int n3 );



#endif
