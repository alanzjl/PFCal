#include "stdafx.h"
#include "Complex.h"  
#include <math.h>  
#include <iomanip>

Complex::Complex(double x, double y)
{
	dat[0] = x;
	dat[1] = y;
}

Complex::Complex(const Complex &z)
{
	dat[0] = z.dat[0];
	dat[1] = z.dat[1];
}

Complex::~Complex()
{

}

Complex Complex::conjugate() const
{
	Complex z(dat[0], -dat[1]);
	return z;
}

void Complex::operator +=(const Complex &other)
{
	dat[0] += other.dat[0];
	dat[1] += other.dat[1];
}

void Complex::operator +=(const double &other)
{
	dat[0] += other;
}

void Complex::operator -=(const Complex &other)
{
	dat[0] -= other.dat[0];
	dat[1] -= other.dat[1];
}

void Complex::operator -=(const double &other)
{
	dat[0] -= other;
}

void Complex::operator *=(const Complex &other)
{
	double x, y;
	x = (dat[0] * other.dat[0] - dat[1] * other.dat[1]);
	y = (dat[1] * other.dat[0] + dat[0] * other.dat[1]);
	dat[0] = x;
	dat[1] = y;
}

void Complex::operator *=(const double &other)
{
	dat[0] = dat[0] * other;
	dat[1] = dat[1] * other;
}

void Complex::operator /=(const Complex &other)
{
	double x, y;
	double a = other.dat[0] * other.dat[0] + other.dat[1] * other.dat[1];
	x = ((dat[0] * other.dat[0]) + (dat[1] * other.dat[1])) / a;
	y = ((dat[1] * other.dat[0]) - (dat[0] * other.dat[1])) / a;
	dat[0] = x;
	dat[1] = y;
}

void Complex::operator /=(const double &other)
{
	dat[0] = dat[0] / other;
	dat[1] = dat[1] / other;
}

Complex Complex::operator+(const Complex &other)  const
{
	Complex temp(*this);
	temp += other;
	return temp;
}

Complex Complex::operator +(const double &other) const
{
	Complex temp(*this);
	temp += other;
	return temp;
}

Complex Complex::operator -(const Complex &other) const
{
	Complex temp(*this);
	temp -= other;
	return temp;
}

Complex Complex::operator -(const double &other) const
{
	Complex temp(*this);
	temp -= other;
	return temp;
}

Complex operator -(const Complex &other)
{
	Complex temp(-other.real(), -other.imag());
	return temp;
}

Complex Complex::operator *(const Complex &other) const
{
	Complex temp(*this);
	temp *= other;
	return temp;
}

Complex Complex::operator *(const double &other) const
{
	Complex temp(*this);
	temp *= other;
	return temp;
}

Complex Complex::operator /(const Complex &other) const
{
	Complex temp(*this);
	temp /= other;
	return temp;
}

Complex Complex::operator /(const double &other) const
{
	Complex temp(*this);
	temp /= other;
	return temp;
}

Complex& Complex::operator =(const Complex &other)
{
	this->dat[0] = other.dat[0];
	this->dat[1] = other.dat[1];
	return *this;
}

Complex& Complex::operator =(const double &other)
{
	this->dat[0] = other;
	this->dat[1] = 0;
	return *this;
}
std::ostream& operator << (std::ostream& out, const Complex & z)
{
	std::setiosflags(std::ios::left);
	
	if (z.dat[1] >= 0)
	{
		out << std::fixed << std::setw(10) << std::setprecision(6) << z.dat[0] << " + ";
		out << std::setw(10) << std::setprecision(6) << z.dat[1] << "i";
	}
	else
	{
		out << std::fixed << std::setw(10) << std::setprecision(6) << z.dat[0] << " - ";
		out << std::setw(10) << std::setprecision(6) << -z.dat[1] << "i";
	}
	out.unsetf(std::ios::fixed);
	return out;
}