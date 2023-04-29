#pragma once

#include <iostream>
#include <cmath>
#include "list.hpp"
#include "monom.h"

using namespace std;

class Polynomial
{
private:
	List<Monom> tData;
public:
	Polynomial();                                       // Конструктор по умолчанию		
													
	Polynomial(const List<Monom>&);                     // Конструктор инициализации списком

	Polynomial(const Monom&);                           // Конструктор инициализации мономом

	Polynomial(const Polynomial&);                      // Конструктор копирования

	const Polynomial& operator =(const Polynomial&);    // оператор =

	Polynomial operator +(const Polynomial&) const;     // оператор +

	Polynomial operator *(const Monom&) const;          // Умножение на моном

	Polynomial operator *(double) const;                // оператор * на const

	Polynomial operator -(const Polynomial&) const;     // оператор -

	Polynomial operator *(const Polynomial&) const;     // Оператор *

	void truePolynomial();                              // Удаляет мономы с нулевыми коэффициентами
	                                                    // или складывает мономы с одинаковыми степенями
	void setPolynomial();                               // Ввести полином

	void getPolynomial();                               // Вывести полином на экран
};