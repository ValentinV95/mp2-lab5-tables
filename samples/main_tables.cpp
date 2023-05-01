#include <iostream>
#include <string>
#include "unordered_table.h"
#include "ordered_table.h"
#include "hash_table.h"
#include "polynom.h"
#include "logger.h"

#define SIZE 100
#undef max

using std::cin;
using std::cout;
using std::endl;

template<typename type>
void input(type& buffer)
{
	cin >> buffer;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool fill(Polynom& poly) // return false if the polynomial could not be filled in
{
	int num;
	cout << "\nEnter the number of monomials in the polynomial: ";
	input(num);
	if (num < 1)
	{
		LOGS_ERROR("Non-positive number of monomials");
		return false;
	}
	cout << "\nFilling the polynomial" << endl;
	double coefficient;
	int degree;

	for (int i = 0; i < num; i++)
	{
		cout << "\nEnter the coefficient: ";
		input(coefficient);
		cout << endl << "Enter the degree: ";
		input(degree);
		try
		{
			poly.add_monom(coefficient, degree);
		}
		catch (const exception& except)
		{
			LOGS_ERROR(except.what());
			return false;
		}
	}
	return true;
}

void insert_into_tables(Polynom& pol, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nEnter name of the polynomial: ";
	std::getline(cin, name);
	try
	{
		uT.insert(name, pol);
		LOGS_SUCCESS("new polynomial has been inserted in the unordered table");
		LOGS_COUNTER("comparisons", uT.get_operations_number());
		oT.insert(name, pol);
		LOGS_SUCCESS("new polynomial has been inserted in the ordered table");
		LOGS_COUNTER("comparisons", oT.get_operations_number());
		hT.insert(name, pol);
		LOGS_SUCCESS("new polynomial has been inserted in the hash table");
		LOGS_COUNTER("probings", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOGS_WARNING(except.what());
	}
}

void remove_from_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nEnter name of the polynomial: ";
	std::getline(cin, name);
	try
	{
		uT.remove(name);
		LOGS_SUCCESS("the polynomial has been removed from the unordered table");
		LOGS_COUNTER("comparisons", uT.get_operations_number());
		oT.remove(name);
		LOGS_SUCCESS("the polynomial has been removed from the ordered table");
		LOGS_COUNTER("comparisons", oT.get_operations_number());
		hT.remove(name);
		LOGS_SUCCESS("the polynomial has been removed from the hash table");
		LOGS_COUNTER("probings", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		LOGS_WARNING("polynomial was not found");
	}
}

Polynom* find_in_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nEnter name of the polynomial: ";
	std::getline(cin, name);
	Polynom* pol_uT = uT.find(name);
	Polynom* pol_oT = oT.find(name);
	Polynom* pol_hT = hT.find(name);
	char counter_found = 0;
	if (pol_uT != nullptr)
	{
		LOGS_SUCCESS("the polynomial has been found in the unordered table");
		LOGS_COUNTER("comparisons", uT.get_operations_number());
		counter_found++;
	}
	if (pol_oT != nullptr)
	{
		LOGS_SUCCESS("the polynomial has been found in the ordered table");
		LOGS_COUNTER("comparisons", oT.get_operations_number());
		counter_found++;
	}
	if (pol_hT != nullptr)
	{
		LOGS_SUCCESS("the polynomial has been found in the hash table");
		LOGS_COUNTER("probings", hT.get_operations_number());
		counter_found++;
	}
	if (counter_found == 3)
	{
		if ((*pol_uT) == (*pol_oT) && (*pol_hT) == (*pol_uT) && (*pol_hT) == (*pol_oT))
		{
			LOGS_SUCCESS("the polynomials found in different tables are the same");
			return pol_hT;
		}
	}
	LOGS_WARNING("polynomial was not found");
	return nullptr;
}

void insert_result(Polynom& _res, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	short select;
	cout << "\n\n1 - insert result" << endl;
	cout << "2 - do not insert result" << endl;
	cout << "Enter: ";
	input(select);
	if (select == 1) // insert allowed
	{
		insert_into_tables(_res, uT, oT, hT);
	}
	else if (select != 2)
	{
		LOGS_ERROR("invalid number - the result was not inserted");
	}
}

enum polynom_operations {
	ADD_POLYNOMIALS = 1,
	SUBTRACT_POLYNOMIALS,
	MULTIPLY_POLYNOMIALS,
	MULTIPLY_POLYNOMIAL_BY_NUMBER
};
bool perform_operations(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	short select;
	cout << "\nSelect an operation:\n" << endl;
	cout << "1 - addition" << endl;
	cout << "2 - subtraction" << endl;
	cout << "3 - multiplication" << endl;
	cout << "4 - multiplication by a number" << endl;
	cout << "\nOperation number: ";
	input(select);

	switch (select)
	{
	case ADD_POLYNOMIALS:
	{
		cout << "\nChoose two polynomials:" << endl;
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
		cout << "\nResult: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case SUBTRACT_POLYNOMIALS:
	{
		cout << "\nChoose two polynomials:" << endl;
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
		cout << "\nResult: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	case MULTIPLY_POLYNOMIALS:
	{
		cout << "\nChoose two polynomials:" << endl;
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
			cout << "\nResult: ";
			res.show();
			insert_result(res, uT, oT, hT);
		}
		catch (const exception& except)
		{
			LOGS_ERROR(except.what());
		}
		break;
	}
	case MULTIPLY_POLYNOMIAL_BY_NUMBER:
	{
		cout << "\nChoose polynomial:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			break;
		}
		double number;
		cout << "\nEnter the number: ";
		input(number);

		Polynom res = *pol1 * number;
		cout << "\nResult: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	default:
	{
		LOGS_ERROR("invalid operation number");
		return false;
	}
	}
	return true;
}

int main()
{
	cout << "Dear user, for the correct operation of the program ";
	cout << "do NOT enter any weird symbols like commas, pound symbol and others!" << endl;
	cout << "Use decimal separator ONLY as a point for entering real numbers\n" << endl;
	cout << "Monomial representation: { coefficient , degree }" << endl;
	cout << "Degree representation: three-digit number ABC (x^Ay^Bz^C, 0 <= A,B,C <= 9)" << endl;
	cout << "For example: 5x^2y^3z^4 -> { 5 , 234 }" << endl << endl;

	cout << "Instruction for working with tables:" << endl;
	cout << " 1) All rules for entering polynomials remain unchanged" << endl;
	cout << " 2) The limit of the number of polynomials in tables is " << SIZE << " instances" << endl;
	cout << " 3) Operations with polynomials are performed only with polynomials inserted into tables" << endl;

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
		cout << endl << "1 - insert new polynomial into the table" << endl;
		cout << "2 - remove polynomial from the table" << endl;
		cout << "3 - find polynomial by name" << endl;
		cout << "4 - perform polynomial operations" << endl;
		cout << "5 - exit" << endl;
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
					cout << "Polynomial: ";
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
				LOGS_ERROR("invalid operation number");
				break;
			}
			}
		}
	}
	return 0;
}
