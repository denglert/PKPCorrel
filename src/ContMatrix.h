#ifndef CONTMATRIX_H
#define CONTMATRIX_H

#include <TMatrix.h>
#include <TH2D.h>
#include <cmath>
#include <iostream>
#include "GraphTools.h"

namespace CM
{

const int nRegions = 3;
const int nCorr[nRegions] = {3, 2, 2};


const int nPt = 14;
const double ptMin = 0.2;
const double ptMax = 1.6;
const double PtBw = 0.1;

const int Indices[nRegions] 	  = {123, 13, 34 };
const int Indices_red[nRegions] = {123, 12, 12 };

const int Corr[nRegions][3] = {
		  								   { 1, 2,  3 },
		 									{ 1, 3, -1 },
		 									{ 3, 4, -1 },
										};

const int nPtBins[nRegions] = {7, 1, 6};

const int PtBins[nRegions][7] = {
		  									{ 0,  1,  2,  3,  4,  5,  6 },
		  									{ 7, -1, -1, -1, -1, -1, -1 },
		  									{ 8,  9, 10, 11, 12, 13, -1 },
										  };


// Functions
void CopyTH2DtoTMatrix( TH2D *th2d_matrix, TMatrix *&tmatrix, int indices );
void CopyTH2DtoTH2D( TH2D *matrix_old, TH2D *&matrix_new, const char matrixname[], int indices );
void normalizeColoumn_TH2D (TH2D *matrix, int colno );
void normalizeMatrix_TH2D (TH2D *matrix );
int GetNdigits( int number );
int GetNthDigit(int number, int n);
void FillIndices( int *indices, int number );

void displayMatrix_TH2D( TH2D *matrix);
void displayMatrix_TMatrix( TMatrix *matrix );

std::string GetTypeLatex (int ID);
void plotContMatrix(TH2D *matrix, int indices, const char figbasename[]);

}

#endif
