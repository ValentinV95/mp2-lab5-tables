#include <iostream>
#include <string>
#include "unorderedtable.h"
#include "orderedtable.h"
#include "hashtable.h"
#include "polynom.h"
#include "logger.h"

#define SIZE 100
#undef max

using std::cin;
using std::cout;
using std::endl;

template <typename type>
void input(type& buffer)
{
	cin >> buffer;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool fill(Polynom& poly) // ������� false, ���� ������� �� ����� ���� ��������
{
	int num;
	cout << "\n������� ���������� ���������� � ����������: ";
	input(num);
	if (num < 1)
	{
		LOG_ERROR("��������������� ���������� �������");
		return false;
	}
	cout << "\n���������� ����������" << endl;
	double coefficient;
	int degree;

	for (int i = 0; i < num; i++)
	{
		cout << "\n������� �����������: ";
		input(coefficient);
		cout << endl << "������� �������: ";
		input(degree);
		try
		{
			poly.add_monom(coefficient, degree);
		}
		catch (const exception& except)
		{
			LOG_ERROR(except.what());
			return false;
		}
	}
	return true;
}

void insert_into_tables(Polynom& pol, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\n������� ��� ����������: ";
	std::getline(cin, name);
	try
	{
		uT.insert(name, pol);
		LOG_SUCCESS("����� ��������� ��� �������� � �������������� �������");
		LOG_COUNTER("���������", uT.get_operations_number());
		oT.insert(name, pol);
		LOG_SUCCESS("����� ��������� ��� �������� � �������������� �������");
		LOG_COUNTER("���������", oT.get_operations_number());
		hT.insert(name, pol);
		LOG_SUCCESS("����� ��������� ��� �������� � �������������� �������");
		LOG_COUNTER("������������", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOG_WARNING(except.what());
	}
}

void remove_from_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\n������� ��� ��������: ";
	std::getline(cin, name);
	try
	{
		uT.remove(name);
		LOG_SUCCESS("��������� ��� ������ �� ��������������� �������");
		LOG_COUNTER("���������", uT.get_operations_number());
		oT.remove(name);
		LOG_SUCCESS("��������� ��� ������ �� ��������������� �������");
		LOG_COUNTER("���������", oT.get_operations_number());
		hT.remove(name);
		LOG_SUCCESS("��������� ��� ������ �� ��������������� �������");
		LOG_COUNTER("������������", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOG_WARNING("������� �� ������...");
	}
}

Polynom* find_in_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\n������� ��� ��������: ";
	std::getline(cin, name);
	Polynom* pol_uT = uT.find(name);
	Polynom* pol_oT = oT.find(name);
	Polynom* pol_hT = hT.find(name);
	char counter_found = 0;
	if (pol_uT != nullptr)
	{
		LOG_SUCCESS("��������� ������ � ��������������� �������");
		LOG_COUNTER("���������", uT.get_operations_number());
		counter_found++;
	}
	if (pol_oT != nullptr)
	{
		LOG_SUCCESS("��������� ������ � ������������� �������");
		LOG_COUNTER("���������", oT.get_operations_number());
		counter_found++;
	}
	if (pol_hT != nullptr)
	{
		LOG_SUCCESS("��������� ������ � ���-�������");
		LOG_COUNTER("������������", hT.get_operations_number());
		counter_found++;
	}
	if (counter_found == 3)
	{
		if ((*pol_uT) == (*pol_oT) && (*pol_hT) == (*pol_uT) && (*pol_hT) == (*pol_oT))
		{
			LOG_SUCCESS("����������, ��������� � ������ ��������, ���������");
			return pol_hT;
		}
	}
	LOG_WARNING("��������� �� ������");
	return nullptr;
}

void insert_result(Polynom& _res, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	short select;
	cout << "\n\n1 - �������� ���������" << endl;
	cout << "2 - �� ��������� ���������" << endl;
	cout << "����: ";
	input(select);
	if (select == 1) // insert allowed
	{
		insert_into_tables(_res, uT, oT, hT);
	}
	else if (select != 2)
	{
		LOG_ERROR("�������� ����� - ��������� �� ��� ��������");
	}
}

enum polynom_operations {
	ADD_POLYNOMIALS = 1,
	SUBTRACT_POLYNOMIALS,
	MULTIPLY_POLYNOMIALS,
	MULTIPLY_POLYNOMIAL_BY_NUMBER
};
void perform_operations(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	short select;
	cout << "\n�������� ��������:\n" << endl;
	cout << "1 - ����������" << endl;
	cout << "2 - ���������" << endl;
	cout << "3 - ���������" << endl;
	cout << "4 - ��������� �� �����" << endl;
	cout << "\n����� ��������: ";
	input(select);

	switch (select)
	{
	case ADD_POLYNOMIALS:
	{
		cout << "\n�������� ��� ��������:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			break;
		}
		Polynom res = *pol1 + *pol2;
		cout << "\n���������: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case SUBTRACT_POLYNOMIALS:
	{
		cout << "\n�������� 2 ��������:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			break;
		}
		Polynom res = *pol1 - *pol2;
		cout << "\n���������: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case MULTIPLY_POLYNOMIALS:
	{
		cout << "\n�������� 2 ��������:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			break;
		}
		try
		{
			Polynom res = (*pol1) * (*pol2);
			cout << "\n���������: ";
			res.show();
			insert_result(res, uT, oT, hT);
		}
		catch (const exception& except)
		{
			LOG_ERROR(except.what());
		}
		break;
	}
	case MULTIPLY_POLYNOMIAL_BY_NUMBER:
	{
		cout << "\n�������� �������:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		double number;
		cout << "\n������� �����: ";
		input(number);

		Polynom res = *pol1 * number;
		cout << "\n���������: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	default:
	{
		LOG_ERROR("�������� ����� ��������");
		break;
	}
	}
}

int main()
{
	UnorderedTable<Polynom> unorderedT(SIZE);
	OrderedTable<Polynom> orderedT;
	HashTable<Polynom> hashT(SIZE);

	enum tables_operations {
		INSERT_POLYNOMIAL = 1,
		REMOVE_POLYNOMIAL,
		FIND_POLYNOMIAL_BY_NAME,
		PERFORM_POLYNOMIAL_OPERATIONS,
		EXIT
	};

	short select;
	while (true)
	{
		cout << "\n1 - �������� ����� ��������� � �������" << endl;
		cout << "2 - ������� ��������� �� �������" << endl;
		cout << "3 - ����� ��������� �� �����" << endl;
		cout << "4 - ��������� �������������� ��������" << endl;
		cout << "5 - �����" << endl;
		cout << "Enter: ";
		input(select);
		if (select == EXIT) break;
		else
		{
			switch (select)
			{
			case INSERT_POLYNOMIAL:
			{
				Polynom pol;
				if (fill(pol))
				{
					insert_into_tables(pol, unorderedT, orderedT, hashT);
				}
				break;
			}
			case REMOVE_POLYNOMIAL:
			{
				remove_from_tables(unorderedT, orderedT, hashT);
				break;
			}
			case FIND_POLYNOMIAL_BY_NAME:
			{
				Polynom* find_pol = find_in_tables(unorderedT, orderedT, hashT);
				if (find_pol != nullptr)
				{
					cout << "�������: ";
					(*find_pol).show();
					cout << endl;
				}
				break;
			}
			case PERFORM_POLYNOMIAL_OPERATIONS:
			{
				perform_operations(unorderedT, orderedT, hashT);
				break;
			}
			default:
			{
				LOG_ERROR("�������� ����� ��������");
				break;
			}
			}
		}
	}
	return 0;
}