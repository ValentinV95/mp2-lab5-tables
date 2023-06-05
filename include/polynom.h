#include <iostream>
#include <cmath>
#include "list.h"
#define eps 0.1e-11

using std::exception;

class Polynom
{
private:

    struct Monom
    {
        double coefficient;
        size_t degree;

        bool operator==(const Monom& other) const; // сравнение мономов
        bool operator!=(const Monom& other) const; // сравнение мономов
    };

    List<Monom> polynom;

public:

    void add_monom(double coef, size_t deg); // добавление мономов по параметрам

    size_t psize() const; // получить размер полинома (количество мономов)

    Polynom operator+(const Polynom& other); // сложение полиномов
    Polynom operator*(const Polynom& other); // умножение многочленов
    Polynom operator*(const double& coef) const; // многочлен умножения на число
    Polynom operator-(const Polynom& other); // вычитание многочленов

    bool operator==(const Polynom& other) const; // сравнение полиномов для тестов
    bool operator!=(const Polynom& other) const; // сравнение полиномов для тестов

    void show(); // вывод полиномов
};