#include "monom.h"

// Monom
Monom::Monom() : degree(0), coef(0.0)
{}

Monom::Monom(int var, double dvar) : degree(var), coef(dvar)
{
	if (degree < 0 || degree > 999)
	{
		string error = "\"Monom::Monom\": min monom degree is 0 and max one is 999";
		error += ", \n but it's ";
		error += to_string(degree);
		throw error;
	};
}

Monom::Monom(double dvar) : degree(0), coef(dvar)
{}

Monom::Monom(const Monom& other)
{
	this->degree = other.degree;
	this->coef = other.coef;
}

const Monom& Monom::operator =(const Monom& other)
{
	this->degree = other.degree;
	this->coef = other.coef;

	return *this;
}

Monom Monom::operator +(const Monom& other) const
{
	if (this->degree != other.degree)
	{
		string error = "\"Monom::operator+\": you can add two monoms only with equal degree,\n";
		error += "but first monom has " + to_string(this->degree) + "degree and second one has ";
		error += to_string(other.degree);
		throw error;
	}

	Monom third(*this);
	third.coef += other.coef;
	return third;
}

Monom& Monom::operator +=(const Monom& other)
{
	if (this->degree != other.degree)
	{
		string error = "\"Monom::operator+\": you can add two monoms only with equal degree,\n";
		error += "but first monom has " + to_string(this->degree) + "degree and second one has ";
		error += to_string(other.degree);
		throw error;
	}

	this->coef += other.coef;
	return *this;
}

Monom Monom::operator -(const Monom& other) const
{
	if (this->degree != other.degree)
	{
		string error = "\"Monom::operator-\": you can subtract two monoms only with equal degree,\n";
		error += "but first monom has " + to_string(this->degree) + "degree and second one has ";
		error += to_string(other.degree);
		throw error;
	}

	Monom third(*this);
	third.coef -= other.coef;
	return third;
}

Monom Monom::operator *(const Monom& other) const
{
	int x, y, z, xo, yo, zo;

	x = (this->degree / 100) % 10;
	y = (this->degree / 10) % 10;
	z = this->degree % 10;
	xo = (other.degree / 100) % 10;
	yo = (other.degree / 10) % 10;
	zo = other.degree % 10;
	int px = x + xo, py = y + yo, pz = z + zo;

	if (px > 9 || py > 9 || pz > 9)
	{
		string error = "\"Monom::operator*\": max monom degree by variable is 9,\n";
		error += "but if ";
		error += this->stringMonom();
		error += " * ";
		error += other.stringMonom();
		error += " : ";
		if (px > 9) error += "x degree = " + to_string(px) + "; ";
		if (py > 9) error += "y degree = " + to_string(py) + "; ";
		if (pz > 9) error += "z degree = " + to_string(pz) + ";";
		throw error;
	}

	Monom third(*this);
	third.degree += other.degree;
	third.coef *= other.coef;
	return third;
}

Monom& Monom::operator *=(const Monom& other)
{
	int x, y, z, xo, yo, zo;

	x = (this->degree / 100) % 10;
	y = (this->degree / 10) % 10;
	z = this->degree % 10;
	xo = (other.degree / 100) % 10;
	yo = (other.degree / 10) % 10;
	zo = other.degree % 10;
	int px = x + xo, py = y + yo, pz = z + zo;

	if (px > 9 || py > 9 || pz > 9)
	{
		string error = "\"Monom::operator*=\": max monom degree by variable is 9,\n";
		error += "but if ";
		error += this->stringMonom();
		error += " * ";
		error += other.stringMonom();
		error += " : ";
		if (px > 9) error += "x degree = " + to_string(px) + "; ";
		if (py > 9) error += "y degree = " + to_string(py) + "; ";
		if (pz > 9) error += "z degree = " + to_string(pz) + ";";
		throw error;
	}

	this->degree += other.degree;
	this->coef *= other.coef;
	return *this;
}

Monom& Monom::operator *=(double temp)
{
	this->coef *= temp;
	return *this;
}

bool Monom::operator <(const Monom& other) const
{
	if (this->degree == other.degree) return this->coef < other.coef;
	return this->degree < other.degree;
}

bool Monom::operator <=(const Monom& other) const
{
	if (this->degree == other.degree) return this->coef <= other.coef;
	return this->degree <= other.degree;
}

bool Monom::operator >(const Monom& other) const
{
	if (this->degree == other.degree) return this->coef > other.coef;
	return this->degree > other.degree;
}

bool Monom::operator >=(const Monom& other) const
{
	if (this->degree == other.degree) return this->coef >= other.coef;
	return this->degree >= other.degree;
}

bool Monom::operator ==(const Monom& other) const
{
	if (this->degree == other.degree) return this->coef == other.coef;
	return false;
}

bool Monom::operator !=(const Monom& other) const
{
	return !(*this == other);
}

string Monom::stringMonom() const
{
	int x, y, z;
	string result = "";

	x = (this->degree / 100) % 10;
	y = (this->degree / 10) % 10;
	z = this->degree % 10;

	if (this->degree == 0 || this->coef != 1.0) result += to_string(this->coef);

	if (x)
	{
		result += "x";
		if (x != 1) result += "^" + to_string(x);
	}

	if (y)
	{
		result += "y";
		if (y != 1) result += "^" + to_string(y);
	}

	if (z)
	{
		result += "z";
		if (z != 1) result += "^" + to_string(z);
	}

	return result;
}