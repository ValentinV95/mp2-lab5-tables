#pragma once


#include "../include/polinom.h"




int amount_of_monoms()
{
	int nm;
	cin >> nm;
	if (nm < 0) throw exception("Отрицательное число мономов в полиноме");
	else if (nm == 0)
	{
		while (true)
		{
			system("cls");
			cout << endl << endl << " Ваш полином это 0" << endl << endl << " Вы уверены в своём выборе?";
			cout << endl << " (1) Да \n (2) Нет \n\n\n > ";
			int choice = 0;
			cin >> choice;
			if (choice == 1) return 0;
			else if (choice == 2)
			{
				cout << endl << endl << "количество мономов в полиноме: ";
				return amount_of_monoms();
			}

		}

	}
	return nm;
}


int cr_degree(int p_dbl)
{
	int tmp;
	cin >> tmp;
	if (p_dbl != 0 && (tmp < 0 || tmp>99)) throw exception("Нарушение правил: Степень вне диапазона  0 - 99");
	return tmp;
}

void show_monom(double tmp_dbl, int tmp_xyz)
{
	if (tmp_dbl == 0) cout << "0";
	else
	{
		if (tmp_xyz == 0) cout << tmp_dbl;  // 0

		else if (((tmp_xyz - tmp_xyz % 10000) / 10000) && ((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && (tmp_xyz % 100)) //  x  y  z
		{
			cout << tmp_dbl << "*x^" << (tmp_xyz - tmp_xyz % 10000) / 10000 << "y^" << (tmp_xyz % 10000 - tmp_xyz % 100) / 100 << "z^" << tmp_xyz % 100;
		}

		else if (((tmp_xyz - tmp_xyz % 10000) / 10000) && ((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && !(tmp_xyz % 100))//  x  y
		{
			cout << tmp_dbl << "*x^" << (tmp_xyz - tmp_xyz % 10000) / 10000 << "y^" << (tmp_xyz % 10000 - tmp_xyz % 100) / 100;
		}

		else if (((tmp_xyz - tmp_xyz % 10000) / 10000) && !((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && (tmp_xyz % 100))//  x  z
		{
			cout << tmp_dbl << "*x^" << (tmp_xyz - tmp_xyz % 10000) / 10000 << "z^" << tmp_xyz % 100;
		}

		else if (!((tmp_xyz - tmp_xyz % 10000) / 10000) && ((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && (tmp_xyz % 100))//  y  z
		{
			cout << tmp_dbl << "y^" << (tmp_xyz % 10000 - tmp_xyz % 100) / 100 << "z^" << tmp_xyz % 100;
		}

		else if (((tmp_xyz - tmp_xyz % 10000) / 10000) && !((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && !(tmp_xyz % 100))//  x
		{
			cout << tmp_dbl << "*x^" << (tmp_xyz - tmp_xyz % 10000) / 10000;
		}

		else if (!((tmp_xyz - tmp_xyz % 10000) / 10000) && ((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && !(tmp_xyz % 100))//  y
		{
			cout << tmp_dbl << "y^" << (tmp_xyz % 10000 - tmp_xyz % 100) / 100;
		}

		else if (!((tmp_xyz - tmp_xyz % 10000) / 10000) && !((tmp_xyz % 10000 - tmp_xyz % 100) / 100) && (tmp_xyz % 100))// z
		{
			cout << tmp_dbl << "z^" << tmp_xyz % 100;
		}

	}
}


polinom create_polinom(int Nmon)
{

	system("cls");

	polinom P;
	double p_dbl = 0.0;
	int xyz = -1;

	int tmp_degree = 0;

	for (int i = 0; i < Nmon; i++)
	{
		cout << endl << "Создаём " << i + 1 << "-й моном из " << Nmon << "  (" << i + 1 << "/" << Nmon << ")" << endl;

		cout << "\n Введите коэффициент :  ";
		cin >> p_dbl;

		cout << "\n Введите степени переменных в мономе (от 0 до 99) :";
		cout << "\nx^";
		xyz = cr_degree(p_dbl) * 10000;

		cout << "\ny^";
		xyz += cr_degree(p_dbl) * 100;

		cout << "\nz^";
		xyz += cr_degree(p_dbl);

		cout << endl << i + 1 << "-й моном:   ";
		show_monom(p_dbl, xyz);
		cout << endl << endl;

		P.push(p_dbl, xyz);
	}

	return P;
}

void show_polinom(polinom P)
{

	cout << "Полином :    ";
	for (monom* m_it = P.head; m_it != nullptr; m_it = m_it->next)
	{
		show_monom(m_it->data, m_it->xyz);
		if (m_it->next != nullptr) cout << " + ";
	}

	if (P.head == nullptr)
	{
		cout << " 0 ";
	}

	cout << endl << endl;
}


void calculate(polinom P)
{

	double dbl1, dbl2, dbl3;

	double resultat = 0;

	system("cls");
	cout << endl << "Введите значения переменных:" << endl;
	cout << " x: "; cin >> dbl1; cout << endl;
	cout << " y: "; cin >> dbl2; cout << endl;
	cout << " z: "; cin >> dbl3; cout << endl;


	for (auto m_it = P.head; m_it != nullptr; m_it = m_it->next)
	{
		if (m_it->data != 0)
		{
			resultat += m_it->data * pow(dbl1, ((m_it->xyz) - (m_it->xyz) % 10000) / 10000) * pow(dbl2, ((m_it->xyz) % 10000 - (m_it->xyz) % 100) / 100) * pow(dbl3, (m_it->xyz) % 100);
		}
	}


	cout << endl << endl << "Полином равен:  " << resultat << endl << endl;

	system("pause");
}

