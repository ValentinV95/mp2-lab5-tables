#include <iostream>
#include <cmath>
#include <string>
#include <exception>
#include <vector>
#include <windows.h>

using std::fabs;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::invalid_argument;
using std::out_of_range;
using std::pair;
using std::make_pair;
using std::vector;
using std::enable_if_t;





struct Monom {

	double k;
	int xyz;

	Monom* next;
};

struct Polinom {

	Monom* head = nullptr;

	void push(double nk, int nxyz);
	Polinom& operator=(Polinom second);
	Polinom operator+(Polinom second);
	Polinom operator-(Polinom second);
	Polinom operator*(double cont);
	Polinom operator*(Polinom second);
	void show_polinom();
	double solve(double x, double y, double z);
	void string_to_polinom(string polim);
	std::ostream& operator<< (std::ostream& out);
	~Polinom();
};

double string_to_double(string s);