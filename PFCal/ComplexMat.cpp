#include "stdafx.h"
#include "ComplexMat.h"


CComplexMat::CComplexMat():
	m_max(0)
{
	memset(Y, 0, sizeof(Y));
}


CComplexMat::~CComplexMat()
{
}

void CComplexMat::Initialize() {
	memset(Y, 0, sizeof(Y));
}

int CComplexMat::Dim() {
	return m_max;
}

double CComplexMat::GetImg(int x, int y) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][1];
}
double CComplexMat::GetReal(int x, int y) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][0];
}

double CComplexMat::AddImg(int x, int y, double num) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	Y[x][y][1] += num;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][1];
}
double CComplexMat::AddReal(int x, int y, double num) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	Y[x][y][0] += num;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][0];
}

bool CComplexMat::Add(int x, int y, double real, double img) {
	AddReal(x, y, real);
	AddImg(x, y, img);
	return true;
}

double CComplexMat::SetImg(int x, int y, double num) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	Y[x][y][1] = num;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][1];
}
double CComplexMat::SetReal(int x, int y, double num) {
	x--; y--;
	if (x >= Y_MAT_DIM || y >= Y_MAT_DIM)
		return -1;
	Y[x][y][0] = num;
	if (x > m_max) m_max = x;
	if (y > m_max) m_max = y;
	return Y[x][y][0];
}

double CComplexMat::InverseReal(double x, double y) {
	return (x / (x*x + y*y));
}

double CComplexMat::InverseImg(double x, double y) {
	return (-1 * y / (x*x + y*y));
}
