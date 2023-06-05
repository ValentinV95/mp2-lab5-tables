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

        bool operator==(const Monom& other) const; // ��������� �������
        bool operator!=(const Monom& other) const; // ��������� �������
    };

    List<Monom> polynom;

public:

    void add_monom(double coef, size_t deg); // ���������� ������� �� ����������

    size_t psize() const; // �������� ������ �������� (���������� �������)

    Polynom operator+(const Polynom& other); // �������� ���������
    Polynom operator*(const Polynom& other); // ��������� �����������
    Polynom operator*(const double& coef) const; // ��������� ��������� �� �����
    Polynom operator-(const Polynom& other); // ��������� �����������

    bool operator==(const Polynom& other) const; // ��������� ��������� ��� ������
    bool operator!=(const Polynom& other) const; // ��������� ��������� ��� ������

    void show(); // ����� ���������
};