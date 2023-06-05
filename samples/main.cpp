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

bool fill(Polynom& poly) // вернуть false, если полином не может быть заполнен
{
	int num;
	cout << "\nВведите количество одночленов в многочлене: ";
	input(num);
	if (num < 1)
	{
		LOG_ERROR("Неположительное количество мономов");
		return false;
	}
	cout << "\nЗаполнение многочлена" << endl;
	double coefficient;
	int degree;

	for (int i = 0; i < num; i++)
	{
		cout << "\nВведите коэффициент: ";
		input(coefficient);
		cout << endl << "Введите степень: ";
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
	cout << "\nВведите имя многочлена: ";
	std::getline(cin, name);
	try
	{
		uT.insert(name, pol);
		LOG_SUCCESS("новый многочлен был вставлен в ненумерованную таблицу");
		LOG_COUNTER("сравнение", uT.get_operations_number());
		oT.insert(name, pol);
		LOG_SUCCESS("новый многочлен был вставлен в ненумерованную таблицу");
		LOG_COUNTER("сравнение", oT.get_operations_number());
		hT.insert(name, pol);
		LOG_SUCCESS("новый многочлен был вставлен в ненумерованную таблицу");
		LOG_COUNTER("зондирование", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOG_WARNING(except.what());
	}
}

void remove_from_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nВведите имя полинома: ";
	std::getline(cin, name);
	try
	{
		uT.remove(name);
		LOG_SUCCESS("многочлен был удален из неупорядоченной таблицы");
		LOG_COUNTER("сравнение", uT.get_operations_number());
		oT.remove(name);
		LOG_SUCCESS("многочлен был удален из неупорядоченной таблицы");
		LOG_COUNTER("сравнение", oT.get_operations_number());
		hT.remove(name);
		LOG_SUCCESS("многочлен был удален из неупорядоченной таблицы");
		LOG_COUNTER("зондирование", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOG_WARNING("полином не найден...");
	}
}

Polynom* find_in_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nВведите имя полинома: ";
	std::getline(cin, name);
	Polynom* pol_uT = uT.find(name);
	Polynom* pol_oT = oT.find(name);
	Polynom* pol_hT = hT.find(name);
	char counter_found = 0;
	if (pol_uT != nullptr)
	{
		LOG_SUCCESS("многочлен найден в неупорядоченной таблице");
		LOG_COUNTER("сравнение", uT.get_operations_number());
		counter_found++;
	}
	if (pol_oT != nullptr)
	{
		LOG_SUCCESS("многочлен найден в упорядоченной таблице");
		LOG_COUNTER("сравнение", oT.get_operations_number());
		counter_found++;
	}
	if (pol_hT != nullptr)
	{
		LOG_SUCCESS("многочлен найден в хеш-таблице");
		LOG_COUNTER("зондирование", hT.get_operations_number());
		counter_found++;
	}
	if (counter_found == 3)
	{
		if ((*pol_uT) == (*pol_oT) && (*pol_hT) == (*pol_uT) && (*pol_hT) == (*pol_oT))
		{
			LOG_SUCCESS("многочлены, найденные в разных таблицах, одинаковы");
			return pol_hT;
		}
	}
	LOG_WARNING("многочлен не найден");
	return nullptr;
}

void insert_result(Polynom& _res, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	short select;
	cout << "\n\n1 - вставить результат" << endl;
	cout << "2 - не вставлять результат" << endl;
	cout << "Ввод: ";
	input(select);
	if (select == 1) // insert allowed
	{
		insert_into_tables(_res, uT, oT, hT);
	}
	else if (select != 2)
	{
		LOG_ERROR("неверный номер - результат не был вставлен");
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
	cout << "\nВыберите операцию:\n" << endl;
	cout << "1 - добавление" << endl;
	cout << "2 - вычитание" << endl;
	cout << "3 - умножение" << endl;
	cout << "4 - умножение на число" << endl;
	cout << "\nНомер операции: ";
	input(select);

	switch (select)
	{
	case ADD_POLYNOMIALS:
	{
		cout << "\nВыберите два полинома:" << endl;
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
		cout << "\nРезультат: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case SUBTRACT_POLYNOMIALS:
	{
		cout << "\nВыберите 2 полинома:" << endl;
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
		cout << "\nРезультат: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case MULTIPLY_POLYNOMIALS:
	{
		cout << "\nВыберите 2 полинома:" << endl;
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
			cout << "\nРезультат: ";
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
		cout << "\nВыберите полином:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		double number;
		cout << "\nВведите число: ";
		input(number);

		Polynom res = *pol1 * number;
		cout << "\nРезультат: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	default:
	{
		LOG_ERROR("неверный номер операции");
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
		cout << "\n1 - Вставить новый многочлен в таблицу" << endl;
		cout << "2 - Удалить многочлен из таблицы" << endl;
		cout << "3 - Найти многочлен по имени" << endl;
		cout << "4 - Выполнять полиномиальные операции" << endl;
		cout << "5 - Выход" << endl;
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
					cout << "Полином: ";
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
				LOG_ERROR("неверный номер операции");
				break;
			}
			}
		}
	}
	return 0;
}