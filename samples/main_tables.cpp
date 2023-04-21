#include "unordered_table.h"
#include "ordered_table.h"
#include "hash_table.h"
#include "polynom.h"
#include "logger.h"

using std::cin;
using std::cout;
using std::endl;

Logger logs;

bool fill(Polynom& poly) // return false if the polynomial could not be filled in
{
	int num;
	cout << "\nEnter the number of monomials in the polynomial: ";
	cin >> num;
	if (num < 1)
	{
		logs.error("Non-positive number of monomials");
		return false;
	}
	cout << "\nFilling the polynomial" << endl;
	double coefficient;
	int degree;

	for (int i = 0; i < num; i++)
	{
		cout << "\nEnter the coefficient: ";
		cin >> coefficient;
		cout << endl << "Enter the degree: ";
		cin >> degree;
		try
		{
			poly.add_monom(coefficient, degree);
		}
		catch (const exception& except)
		{
			logs.error(except.what());
			return false;
		}
	}
	return true;
}

void insert_into_tables(Polynom& pol, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\nEnter name of the polynomial: ";
	cin >> name;
	try
	{
		uT.insert(name, pol);
		logs.success("new polynomial has been inserted in the unordered table");
		logs.counter("comparisons", uT.get_operations_number());
		oT.insert(name, pol);
		logs.success("new polynomial has been inserted in the ordered table");
		logs.counter("comparisons", oT.get_operations_number());
		hT.insert(name, pol);
		logs.success("new polynomial has been inserted in the hash table");
		logs.counter("probings", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		logs.warning(except.what());
	}
}

void remove_from_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\n\nEnter name of the polynomial: ";
	cin >> name;
	try
	{
		uT.remove(name);
		logs.success("the polynomial has been removed from the unordered table");
		logs.counter("comparisons", uT.get_operations_number());
		oT.remove(name);
		logs.success("the polynomial has been removed from the ordered table");
		logs.counter("comparisons", oT.get_operations_number());
		hT.remove(name);
		logs.success("the polynomial has been removed from the hash table");
		logs.counter("probings", hT.get_operations_number());
	}
	catch (const exception& except)
	{
		logs.warning(except.what());
	}
}

Polynom* find_in_tables(UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	string name = "";
	cout << "\n\nEnter name of the polynomial: ";
	cin >> name;
	if (uT.find(name) != nullptr)
	{
		logs.success("the polynomial has been found in the unordered table");
		logs.counter("comparisons", uT.get_operations_number());
	}
	if (oT.find(name) != nullptr)
	{
		logs.success("the polynomial has been found in the ordered table");
		logs.counter("comparisons", oT.get_operations_number());
	}
	if (hT.find(name) != nullptr)
	{
		logs.success("the polynomial has been found in the hash table");
		logs.counter("probings", hT.get_operations_number());
		return hT.find(name);
	}
	logs.warning("key was not found");
	return nullptr;
}

void insert_result(Polynom& _res, UnorderedTable<Polynom>& uT, OrderedTable<Polynom>& oT, HashTable<Polynom>& hT)
{
	int select;
	cout << "\n\n1 - insert result" << endl;
	cout << "2 - do not insert result" << endl;
	cout << "Enter: ";
	cin >> select;
	if (select == 1) // insert allowed
	{
		insert_into_tables(_res, uT, oT, hT);
	}
	else if (select != 2)
	{
		logs.warning("invalid number");
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
	int select;
	cout << "\n\nSelect an operation:\n" << endl;
	cout << "1 - addition" << endl;
	cout << "2 - subtraction" << endl;
	cout << "3 - multiplication" << endl;
	cout << "4 - multiplication by a number" << endl;
	cout << "\nOperation number: ";
	cin >> select;

	switch (select)
	{
	case ADD_POLYNOMIALS:
	{
		cout << "\nChoose two polynomials:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			logs.error("no polynomial found");
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			logs.error("no polynomial found");
			break;
		}
		Polynom res = *pol1 + *pol2;
		cout << "\n\nResult: ";
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
			logs.error("no polynomial found");
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			logs.error("no polynomial found");
			break;
		}
		Polynom res = *pol1 - *pol2;
		cout << "\n\nResult: ";
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
			logs.error("no polynomial found");
			break;
		}
		Polynom* pol2 = find_in_tables(uT, oT, hT);
		if (pol2 == nullptr)
		{
			logs.error("no polynomial found");
			break;
		}
		try
		{
			Polynom res = (*pol1) * (*pol2);
			cout << "\n\nResult: ";
			res.show();
			insert_result(res, uT, oT, hT);
		}
		catch (const exception& except)
		{
			logs.error(except.what());
		}
		break;
	}
	case MULTIPLY_POLYNOMIAL_BY_NUMBER:
	{
		cout << "\nChoose polynomial:" << endl;
		Polynom* pol1 = find_in_tables(uT, oT, hT);
		if (pol1 == nullptr)
		{
			logs.error("no polynomial found");
			break;
		}
		double number;
		cout << "\nEnter the number: ";
		cin >> number;

		Polynom res = *pol1 * number;
		cout << "\n\nResult: ";
		res.show();
		insert_result(res, uT, oT, hT);
		break;
	}
	default:
	{
		logs.error("invalid operation number");
		break;
	}
	}
	cout << endl;
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
	cout << " 2) The limit of the number of polynomials in tables is 1000 pieces" << endl;
	cout << " 3) Operations with polynomials are performed only with polynomials inserted into tables" << endl;
	cout << " 4) Incorrect input while working with tables can lead to loss of table data and termination of the program" << endl;

	UnorderedTable<Polynom> unorderedT(1000);
	OrderedTable<Polynom> orderedT;
	HashTable<Polynom> hashT(1000);

	enum tables_operations {
		INSERT_POLYNOMIAL = 1,
		REMOVE_POLYNOMIAL,
		FIND_POLYNOMIAL_BY_NAME,
		PERFORM_POLYNOMIAL_OPERATIONS,
		EXIT
	};

	int select;
	while (true)
	{
		cout << endl << "1 - insert new polynomial into the table" << endl;
		cout << "2 - remove polynomial from the table" << endl;
		cout << "3 - find polynomial by name" << endl;
		cout << "4 - perform polynomial operations" << endl;
		cout << "5 - exit" << endl;
		cout << "Enter: ";
		cin >> select;
		if (select == EXIT) break;
		else
		{
			switch (select)
			{
			case INSERT_POLYNOMIAL:
			{
				Polynom pol;
				if (!fill(pol)) return 1;
				insert_into_tables(pol, unorderedT, orderedT, hashT);
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
				else
				{
					logs.error("no polynomial found");
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
				logs.error("invalid operation number");
				return 1;
			}
			}
		}
	}

	return 0;
}