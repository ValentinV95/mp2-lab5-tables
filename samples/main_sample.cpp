#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>

#include "AvlTree.h"
#include "unorderedTable.h"
#include "hashTable.h"
#include "polinom.h"


avlTree<std::string, PolynomList> avl_table;
unorderedTable<std::string, PolynomList> unord_table(10);
hashTable<std::string, PolynomList> hash_table(10);


double convert(std::string part)
{
	double num = 0;
	int pow = 0;
	for (int i = part.size() - 1; i >= 0; i--, pow++)
	{
		num += (part[i] - '0') * std::pow(10.0, pow);
	}
	return num;
}

double ConvertNumber(std::string lexem)
{
	if (lexem.size() == 0)
	{
		std::string s = "incorrect number form!";
		throw (s);
	}
	if (lexem[0] == '-')
		return -1. * ConvertNumber(lexem.substr(1, lexem.size()));
	if (lexem[0] == '+')
		return ConvertNumber(lexem.substr(1, lexem.size()));
	if (std::count(lexem.begin(), lexem.end(), '.') > 1 ||
		std::count(lexem.begin(), lexem.end(), 'E') > 1 ||
		(std::count(lexem.begin(), lexem.end(), '+') +
			std::count(lexem.begin(), lexem.end(), '-') +
			std::count(lexem.begin(), lexem.end(), '~') > 1))
	{

		std::string s = "incorrect number form!";
		throw (s);
	}

	int point_index = lexem.find('.');
	int e_index = lexem.find('E');

	double sign = 1.;

	double number = 0.;

	std::string part_before_point;
	std::string part_after_point;
	std::string part_before_e;
	std::string part_after_e;

	if (e_index == std::string::npos)
	{
		if (point_index == std::string::npos)
		{
			number = convert(lexem);
		}
		else
		{
			part_before_point = lexem.substr(0, point_index);
			part_after_point = lexem.substr(point_index + 1, lexem.size());
			if (part_before_point.size() == 0 && part_after_point.size() == 0)
			{
				std::string s = "incorrect number form!";
				throw (s);
			}
			int pow = -1 * part_after_point.size();
			number = convert(part_before_point) + std::pow(10, pow) * convert(part_after_point);
		}
	}
	else
	{
		if (point_index == std::string::npos) // only E
		{
			double sign = 1.;
			part_before_e = lexem.substr(0, e_index);
			if (e_index != lexem.size() - 1 && (lexem[e_index + 1] == '+' || lexem[e_index + 1] == '-'))
			{
				if (lexem[e_index + 1] == '-')
					sign = -1.;
				part_after_e = lexem.substr(e_index + 2, lexem.size());
			}
			else
				part_after_e = lexem.substr(e_index + 1, lexem.size());
			if (part_after_e.size() == 0 || part_before_e.size() == 0)
			{
				std::string s = "incorrect number form!";
				throw (s);
			}
			double pow = sign * convert(part_after_e);
			number = convert(part_before_e) * std::pow(10, pow);
		}
		else
		{
			part_before_e = lexem.substr(0, e_index);
			part_after_e = "1" + lexem.substr(e_index, lexem.size());
			number = ConvertNumber(part_before_e) * ConvertNumber(part_after_e);
		}
	}
	return number;
}



monom str_to_monom(const std::string& str)
{
	double k = 0; int degree = 0;
	int index = 0; 
	int k1 = 0; int k2 = 0;
	int d1 = 0; int d2 = 0;

	for (; index < str.length() && str[index] == ' '; index++){}
	k1 = index;
	for (; index < str.length() && str[index] != ' '; index++) {}
	k2 = index - k1;
	
	if (index == str.length())
		throw std::exception("incorrect monom");
	for (; index < str.length() && str[index] == ' '; index++) {}
	d1 = index;
	for (; index < str.length() && str[index] != ' '; index++) {}
	d2 = index - d1;
	
	k = ConvertNumber(str.substr(k1, k2));
	degree = ConvertNumber(str.substr(d1, d2));

	monom m(k, degree);
	return m;
}



void add(PolynomList result)
{
	std::string polynom_name;

	std::cout << "\nenter the name of the polynomial to record the result: ";
	std::cin >> polynom_name;

	try
	{
		unord_table.addElement(polynom_name, result);
		avl_table.insert(polynom_name, result);
		hash_table.addElement(polynom_name, result);
		std::cout << "the polynomial " << polynom_name << " has been added";
	}
	catch (const std::exception& ex) {}
	unord_table.getElement(polynom_name) = result;
	avl_table.getElement(polynom_name) = result;
	hash_table.getElement(polynom_name) = result;
	std::cout << "the polynomial " << result << " has been added to " << polynom_name;
}

void PolynomOperations()
{
	std::string pool[6];

	pool[0] = "add monom";
	pool[1] = "add a polynomial from a string";
	pool[2] = "operation +";
	pool[3] = "operation -";
	pool[4] = "operation *";
	pool[5] = "close";

	bool stop = false;
	int pos = 0, i = 0, choose;
	std::string polynom_name = "";
	std::string polynom_name_2 = "";

	double monom_k;
	int monom_degree;
	PolynomList result; monom m;
	int index = 0; int k1 = 0, k2 = 0;

	system("cls");

	do
	{
		i = 0;

		for (; i < pos; i++)
			std::cout << pool[i] << '\n';
		std::cout << "->  " << pool[pos] << '\n';
		for (i = pos + 1; i < 6; i++)
			std::cout << pool[i] << '\n';
		std::cout << "\n\tPolynomial :\n";
		unord_table.showTable();

		choose = _getch();


		if (choose == 72 && pos > 0)
			pos--;
		if (choose == 80 && pos < 5)
			pos++;
		if (choose == 13)
			switch (pos)
			{
			case(0):
				std::cout << "\nenter the name of the polynomial : ";
				std::cin >> polynom_name;
				std::cout << "enter a monomial as a coefficient and a degree separated by a space (for example 1.2 345): ";
				std::cin >> monom_k;
				std::cin >> monom_degree;

				try
				{
					unord_table.getElement(polynom_name).add(monom_k, monom_degree);
					avl_table.getElement(polynom_name).add(monom_k, monom_degree);
					hash_table.getElement(polynom_name).add(monom_k, monom_degree);
					std::cout << "a monome was added to the polynomial " << polynom_name;
				}
				catch (const std::exception& ex)
				{
					std::cout << "there is no such polynomial or incorrect entry!";
				}
				_getch();

				break;
			case(1):
				std::cout << "\nenter the name of the polynomial : ";
				std::cin >> polynom_name;
				try
				{
					unord_table.addElement(polynom_name, result);
					avl_table.insert(polynom_name, result);
					hash_table.addElement(polynom_name, result);
					std::cout << "the polynomial " << polynom_name << " has been created";
				}
				catch (const std::exception& ex) {}

				std::cin.ignore();
				std::cout << "\nenter monomials as polynomials separated by a space (for example 1.2 345 + -1E3 321): ";
				std::getline(std::cin, polynom_name_2);
				polynom_name_2 += "  ";

				index = 0; k1 = 0;
				while (true)
				{
					k1 = 0; k2 = 0;
					for (index = 0; index < polynom_name_2.length() && polynom_name_2[index] != '+'; index++)
						if (polynom_name_2[index] != ' ')
							k2++;
					if (k2 == 0)
						break;
					k1 = index-1;
					try
					{
						m = str_to_monom(polynom_name_2.substr(0, k1));
						unord_table.getElement(polynom_name).add(m);
						avl_table.getElement(polynom_name).add(m);
						hash_table.getElement(polynom_name).add(m);
						if (k1+2 < polynom_name_2.length())
							polynom_name_2 = polynom_name_2.substr(index +1);
						else
						{
							std::cout << "a polynomial was added to the polynomial " << polynom_name;
							break;
						}
					}
					catch (const std::exception&ex)
					{
						std::cout << "the polynomial was entered incorrectly and not fully added" << ex.what();
						break;
					}
				}
				_getch();
				break;
			case(2):
				std::cout << "\nenter the name of the polynomial(the left operand) : ";
				std::cin >> polynom_name;

				std::cout << "enter the name of the polynomial(the right operand) : ";
				std::cin >> polynom_name_2;

				try
				{
					result = unord_table.getElement(polynom_name) + unord_table.getElement(polynom_name_2);
					add(result);
				}
				catch (const std::exception& ex)
				{
					std::cout << "there is no such polynomial or incorrect entry!";
				}
				_getch();
				break;

			case(3):
				std::cout << "\nenter the name of the polynomial(the left operand) : ";
				std::cin >> polynom_name;

				std::cout << "enter the name of the polynomial(the right operand) : ";
				std::cin >> polynom_name_2;

				try
				{
					result = unord_table.getElement(polynom_name) - unord_table.getElement(polynom_name_2);
					add(result);
				}
				catch (const std::exception& ex)
				{
					std::cout << "there is no such polynomial or incorrect entry!";
				}
				_getch();
				break;
			case(4):
				std::cout << "\nenter the name of the polynomial(the left operand) : ";
				std::cin >> polynom_name;

				std::cout << "enter the name of the polynomial(the right operand) : ";
				std::cin >> polynom_name_2;

				try
				{
					result = unord_table.getElement(polynom_name) * unord_table.getElement(polynom_name_2);
					add(result);
				}
				catch (const std::exception& ex)
				{
					std::cout << "there is no such polynomial or incorrect entry or degree overflow!";
				}
				_getch();
				break;
			case(5):
				stop = true;
				system("cls");
				break;
			}
		system("cls");
	} while (!stop);
}


int mainMenu()
{

	PolynomList p;

	std::string pool[5];
	pool[0] = "create a polynomial";
	pool[1] = "delete a polynomial";
	pool[2] = "operations on a polynomial";
	pool[3] = "show logs";
	pool[4] = "exit";

	bool stop = false;
	int pos = 0, i = 0, choose;
	std::string polynom_name = "";

	do
	{
		i = 0;
		
		for (; i < pos; i++)
			std::cout << pool[i] << '\n';
		std::cout << "->  " << pool[pos] << '\n';
		for (i = pos + 1; i < 5; i++)
			std::cout << pool[i] << '\n';
		std::cout << "\n\tPolynomial :\n";
		unord_table.showTable();
		
		choose = _getch();

		if (choose == 72 && pos > 0)
			pos--;
		if (choose == 80 && pos < 4)
			pos++;
		if (choose == 13)
			switch (pos)
			{
			case(0):
				std::cout << "\nenter the name of the polynomial : ";
				std::cin >> polynom_name;
				try
				{
					unord_table.addElement(polynom_name, p);
					avl_table.insert(polynom_name, p);
					hash_table.addElement(polynom_name, p);
					std::cout << "the polynomial " << polynom_name << " has been created";
				}
				catch (const std::exception& ex)
				{
					std::cout << "there is no such polynomial!";
				}
				_getch();

				break;
			case(1):
				std::cout << "\nenter the name of the polynomial : ";
				std::cin >> polynom_name;
				try
				{
					unord_table.deleteElement(polynom_name);
					avl_table.delElem(polynom_name);
					hash_table.delElement(polynom_name);
					std::cout << "the polynomial " << polynom_name << " has been deleted";
				}
				catch (const std::exception& ex)
				{
					std::cout << "such a polynomial has already been created!";
				}
				_getch();
				break;
			case(2):
				PolynomOperations();
				break;
			case(3):
				std::cout << "ordered table (avl-tree) : ";
				avl_table.getLog();

				std::cout << "unordered table : ";
				unord_table.getLog();

				std::cout << "hash table : ";
				hash_table.getLog();

				_getch();
				break;
			case(4):
				stop = true;
				system("cls");
				break;
			}
		system("cls");
	} while (!stop);
}


int main()
{
	std::cout << "working with tables of different types for 10 elements"<<
		"\npress any key to get started";
	_getch();
	mainMenu();
}
