#pragma once
#include "../include/monom.h"


class polinom
{
public:
	monom* head = nullptr;
	void push(double data, int xyz);
	void push_start(double data, int xyz);
	void push_between(double data, int xyz, monom* last, monom* next);
	void push_end(double data, int xyz, monom* last);
	void push_add(double data, monom* itis);

	void clear();

	polinom operator+(const polinom& second);

	polinom operator-(polinom second);

	polinom operator*(const polinom& second);

	polinom operator*(const double& var);



};