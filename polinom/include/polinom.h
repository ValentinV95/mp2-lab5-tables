#pragma once

#include "list.h"

using namespace std;

struct Monom
{
	double coeff;
	int deg;
	void init(double a, int b);
	Monom operator+(const Monom& a);
	Monom operator*(const Monom& m);
	bool operator!=(Monom a);
	bool operator==(const Monom& a) const;
	bool operator>=(Monom a);
	bool operator>(Monom a);
	bool operator<(Monom a);
	friend ostream& operator<<(ostream& out, const Monom& m);
};

class Polinom
{
private:
	List<Monom> P;
public:
	Polinom();
	~Polinom();
	Polinom(const Polinom& A);
	void init(Monom M);
	void Input();
	void Print();
	void Delete_Similar();
	int Highest_Degree();
	bool operator==(const Polinom& A) const;
	Polinom& operator=(const Polinom& A);
	Polinom operator+(const Polinom& A);
	Polinom operator*(double q);
	Polinom operator-(Polinom& A);
	Polinom operator*(Polinom& A);
	friend ostream& operator<<(ostream& out, const Polinom& p);
	void Delete_element();
};