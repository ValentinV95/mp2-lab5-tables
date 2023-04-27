#pragma once

#include "MList.h"

class Monom
{
private:
    int deg;
    double coef;
public:
    int getDeg() { return deg; }
    double getCoef() { return coef; }
    Monom() : deg(0), coef(0) {};
    Monom(int _deg, double _coef) : deg(_deg), coef(_coef) {};
    friend ostream& operator<<(ostream& ostr, const Monom& _monom)
    {
        ostr << _monom.coef << "x^" << _monom.deg / 100 << "y^" << _monom.deg % 100 / 10 << "z^" << _monom.deg % 10;
        return ostr;
    }
    bool operator<(const Monom& _monom) const
    {
        return deg < _monom.deg;
    }
    bool operator==(const Monom& _monom) const
    {
        return deg == _monom.deg;
    }
    Monom& operator=(const Monom& _monom)
    {
        if (this == &_monom)
            return *this;
        this->deg = _monom.deg;
        this->coef = _monom.coef;
        return *this;
    }
    Monom& operator+(const Monom& _monom)
    {
        Monom res;
        if (this->deg != _monom.deg)
            throw exception("The degree of monoms does not match");
        res.coef = this->coef + _monom.coef;
        res.deg = this->deg;
        return res;
    }
};

class Polinom
{
private:
    List<Monom> polinom;
public:
    Polinom() = default;
    void Set();
    List<Monom>& getPolinom() { return polinom; }
    void Print();
    Polinom operator+(Polinom& other);
    Polinom operator*(double coef);
    Polinom operator-(Polinom& other);
    Polinom operator*(Polinom& other);
    friend ostream& operator<<(ostream& ostr, Polinom& _polinom);
};