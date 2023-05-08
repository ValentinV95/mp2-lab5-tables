#pragma once
#include <math.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include  "list.h"

#define MaxPow 9
#define uint unsigned int
#define DELIMITER '.'

//Может иметь степень положительную и не превышающую 9
class Monom
{
	unsigned short int xyzPow;
	double a;

	double GetNum(std::string num);
	double StrToNum(std::string str);
public:
	Monom();

	Monom(double a, uint xPow, uint yPow, uint zPow);

	//Ожидаемый формат: a*x^xPow*y^yPow*z^zPow
	//xPow,yPow,zPow - просто числа
	Monom(std::string monomStr);

	//1 - больше/равно 0, 0 - меньше 0
	bool GetSign();

	float GetA();

	int GetPow();

	bool IsPowEqual(const Monom& m);

	std::string toString() const;

	Monom operator + (const Monom& other) const;

	Monom operator - (const Monom& other) const;

	Monom operator * (const Monom& other);

	Monom operator * (double a);

	bool operator > (const Monom& other) const;

	bool operator < (const Monom& other) const;

	bool operator == (const Monom& other) const;

	friend std::ostream& operator << (std::ostream& ostr, const Monom& m);
};

class Polynom
{
	TSortedList<Monom> monoms;
public:
	Polynom();

	Polynom(std::string str);

	Polynom(const Polynom& p);

	std::string toString() const;

	void Append(Monom m);

	void Push_Back(Monom m);

	Monom At(int ind);

	Polynom operator + (const Polynom& other) const;

	Polynom operator - (const Polynom& other) const;

	Polynom operator * (double a) const;

	Polynom operator * (const Monom& m) const;

	Polynom operator * (const Polynom& other) const;

	Polynom operator = (const Polynom& other);

	bool operator == (const Polynom& other) const;

	friend std::ostream& operator << (std::ostream& ostr, const Polynom& p);

	friend std::istream& operator >> (std::istream& istr, Polynom& p);
};