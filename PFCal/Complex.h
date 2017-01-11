
#pragma once
#include <iostream>

class Complex
{
public:
	Complex(const Complex &z);
	Complex(double x = 0.0, double y = 0.0);
	~Complex();
	double real() const { return dat[0]; }
	double imag() const { return dat[1]; }
	void set(double x, double y) { dat[0] = x; dat[1] = y; }
	Complex conjugate() const;
	Complex operator +(const Complex &other) const;
	Complex operator +(const double &other) const;
	Complex operator -(const Complex &other) const;
	Complex operator -(const double &other) const;
	Complex operator *(const Complex &other) const;
	Complex operator *(const double &other) const;
	Complex operator /(const Complex &other) const;
	Complex operator /(const double &other) const;

	void operator +=(const Complex &other);
	void operator +=(const double &other);
	void operator -=(const Complex &other);
	void operator -=(const double &other);
	void operator *=(const Complex &other);
	void operator *=(const double &other);
	void operator /=(const Complex &other);
	void operator /=(const double &other);
	Complex& operator =(const Complex &other);
	Complex& operator =(const double &other);
	double dat[2];
private:
	friend std::ostream& operator << (std::ostream&, const Complex & z);
	friend Complex operator -(const Complex &other);
};

