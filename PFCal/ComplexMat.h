#pragma once
#include "PFCalConstants.h"
class CComplexMat
{
protected:
	int m_max;	//the real dimension
public:
	double Y[Y_MAT_DIM][Y_MAT_DIM][2];
	CComplexMat();
	int Dim();
	void Initialize();
	double GetReal(int x, int y);
	double GetImg(int x, int y);
	double AddReal(int x, int y, double num);
	double AddImg(int x, int y, double num);
	bool Add(int x, int y, double real, double img);
	double SetReal(int x, int y, double num);
	double SetImg(int x, int y, double num);
	double InverseReal(double x, double y);	//get real part of 1/(x+jy)
	double InverseImg(double x, double y);
	
	~CComplexMat();
};

