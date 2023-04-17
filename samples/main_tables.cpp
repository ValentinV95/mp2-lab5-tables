#include <iostream>
#include "TRbTreeTable.hpp"
#include "TTable.hpp"
#include "THashTable.hpp"
#include "Logger.hpp"
#include "polinom.h"

using namespace std;

Polynom finde(string name, THashTable<string, Polynom> &hashTbl,TRbTreeTable<string, Polynom> &treeTbl,TTable<string, Polynom> &simpleTbl)
{
	try
	{
		treeTbl.find(name);
		simpleTbl.find(name);
		Polynom poly = hashTbl.find(name);

		Logger::log(CONTEXT(), "Polynom " + name + " was found successfully in all tables", Info);
		return poly;
	}
	catch (const std::exception& exc)
	{
		Logger::log(CONTEXT(), "Polynom " + name + " was not found successfully" + "\n[Exception message]\n" + exc.what(), Error);
		throw;
	}
}

void remove(string name, THashTable<string, Polynom>& hashTbl, TRbTreeTable<string, Polynom>& treeTbl, TTable<string, Polynom>& simpleTbl)
{
	treeTbl.remove(name);
	simpleTbl.remove(name);
	hashTbl.remove(name);

	Logger::log(CONTEXT(), "Polynom " + name + " was deleted successfully from all tables", Info);
}

void insert(string name,Polynom poly, THashTable<string, Polynom>& hashTbl, TRbTreeTable<string, Polynom>& treeTbl, TTable<string, Polynom>& simpleTbl)
{
	try
	{
		hashTbl.insert(name,poly);
		simpleTbl.insert(name, poly);
		treeTbl.insert(name, poly);

		Logger::log(CONTEXT(), "Polynom " + poly.toString() + " as " + name + " was insert successfully in all tables", Info);
	}
	catch (const std::exception& exc)
	{
		Logger::log(CONTEXT(), "While insert polynom " + poly.toString() + " as " + name + " something went wrong" + "\n[Exception message]\n" + exc.what(), Error);
		throw;
	}
}

void showInfo()
{
	cout << "--------------------------INFO--------------------------" << endl;
	cout << "Полином:" << endl;
	cout << "\tВ качестве имен переменных в полиноме используются x,y,z" << endl;
	cout << "\tОбщий вид монома в полиноме: а*x^X*y^Y*z^Z" << endl;
	cout << "\tГде:" << endl
		<< "\t --a - вещественное число, может быть записано в эспоненциальной" << endl
		<< "\t   форме, в качестве разделителя целой и дробной части выступает ','" << endl
		<< "\t --Коэффицент а опускать нельзя" << endl
		<< "\t --X,Y и Z - числа от 0 до 9" << endl
		<< "\t --Ввод одинаковых мономов недопускается" << endl
		<< "\t --Не обязательно что бы моном содержал все переменные " << endl
		<< "\t --Порядок следования переменных неважен" << endl
		<< "\t --Доступные операции: +, -, *"
		<< endl;
	cout << "Таблицы:" << endl;
	cout << "\tОперации:" << endl
		<< "\t--Удалить полином из таблицы введите delete" << endl
		<< "\t--Добавить полином в таблицу введите insert" << endl
		<< "\t--Просмотреть содержимое таблиц введите show" << endl
		<< "\t--Чтобы найти полином по имени введите finde" << endl;
	cout << "--Что бы совершить арефметическую операцию над плиномами" << endl
		<< "нужно ввести имя первого полинома, операцию, имя второго полинома без пробелов" << endl;
	cout << "--Можно сохранить полином, полученный в результате арифметической операции," << endl
		<< "как полином с новым именем или под именем первого введеного полинома" << endl;
	cout << "--Имя полинома может содержать только буквы a-z,A-Z и цифры от 0 до 1," << endl
		<< "  иные символы могут привести к некорректной работе программы" << endl;
	cout << "--Для завершения программы введите end" << endl;
	cout << "--------------------------------------------------------" << endl;
}

void main()
{
	Logger::log(CONTEXT(),"Program started",Info);

	setlocale(LC_ALL, "Russian");

	showInfo();

	THashTable<string, Polynom> hashTbl(10000);
	TRbTreeTable<string, Polynom> treeTbl;
	TTable<string, Polynom> simpleTbl;

	string command;
	bool end = false;

	while (!end)
	{
		cout << endl << "Введите команду: ";
		cin >> command;

		try
		{
			if (command.find('+') != std::string::npos || command.find('-') != std::string::npos || command.find('*') != std::string::npos)
			{
				if (!hashTbl.isEmpty())
				{
					int operationPos;

					command.find('+') != std::string::npos ? operationPos = command.find('+') :
						command.find('-') != std::string::npos ? operationPos = command.find('-') :
						operationPos = command.find('*');

					string name1 = command.substr(0, operationPos);
					string name2 = command.substr(operationPos + 1, command.size());
					char operation = command[operationPos];

					Polynom poly1, poly2,poly3;

					poly1 = finde(name1,hashTbl,treeTbl,simpleTbl);
					poly2 = finde(name2, hashTbl, treeTbl, simpleTbl);

					try
					{
						switch (operation)
						{
						case('+'):
							poly3=poly1 + poly2;
							Logger::log(CONTEXT(), "Polynom " + poly1.toString() + " and " + poly2.toString() + " was added successfully. Result - " + poly3.toString(), Info);
							break;
						case('-'):
							poly3 = poly1 - poly2;
							Logger::log(CONTEXT(), "Polynom " + poly1.toString() + " and " + poly2.toString() + " was subtracted successfully. Result - " + poly3.toString(), Info);
							break;
						case('*'):
							poly3 = poly1 * poly2;
							Logger::log(CONTEXT(), "Polynom " + poly1.toString() + " and " + poly2.toString() + " was multiplied successfully. Result - " + poly3.toString(), Info);
							break;
						}

						cout << poly3 << endl;

						cout << "\tХотите сохранить результат? yes/no : ";
						cin >> command;

						if (command == "yes")
						{
							cout << "\n\tВведите имя для полинома ";
							cin>>name1;
							
							remove(name1, hashTbl, treeTbl, simpleTbl);
							insert(name1, poly3, hashTbl, treeTbl, simpleTbl);
						}
					}
					catch (const std::exception& exc)
					{
						Logger::log(CONTEXT(), "Operation " + to_string(operation) + " with polynom " + poly1.toString() + " and " + poly2.toString() + " was not successfully" + "\nException message:\n" + exc.what(), Error);
						throw;
					}
				}
				else
				{
					Logger::log(CONTEXT(), "The user tried to perform operations with empty tables", Info);
					cout << "Таблицы не содержат ни одного полинома." << endl
						<< "Для выполнения арифметических операций таблицы должны" << endl
						<< "содержать хотябы один полином" << endl;
				}
			}
			else if (command == "insert")
			{
				string name, polinom;
				cout << "\tВведите имя полинома: ";
				cin >> name;
				Logger::log(CONTEXT(), "User enter the polynom name " + name, Info);
				cout << "\tВведите полином: ";
				cin >> polinom;
				Logger::log(CONTEXT(), "User enter the polynom " + polinom, Info);

				insert(name,Polynom(polinom), hashTbl, treeTbl, simpleTbl);
				cout <<endl <<"Полином был успешно добавоен!" << endl;
			}
			else if (command == "delete")
			{
				string name;
				cout << "\tВведите имя полинома: ";
				cin >> name;

				remove(name, hashTbl, treeTbl, simpleTbl);
				cout << endl << "Полином был успешно удален!" << endl;
			}
			else if (command == "show")
			{
				cout << "НЕУПОРЯДОЧЕННАЯ ТАБЛИЦА: " << endl;
				simpleTbl.show();
				cout << endl;
				Logger::log(CONTEXT(), "Simple table was shown for user", Info);

				cout << "ХЭШ-ТАБЛИЦА: " << endl;
				hashTbl.show();
				cout << endl;
				Logger::log(CONTEXT(), "Hash table was shown for user", Info);

				cout << "КРАСНО-ЧЕРНОЕ ДЕРЕВО: " << endl;
				treeTbl.show();
				cout << endl;
				Logger::log(CONTEXT(), "RB tree table was shown for user", Info);
			}
			else if (command=="finde")
			{
				string name;
				cout << "\tВведите имя полинома: ";
				cin >> name;
				Logger::log(CONTEXT(), "User serching polynome named " + name, Info);

				cout << "\tPolynom named as " <<name <<" is - " << finde(name, hashTbl, treeTbl, simpleTbl) << endl;
			}
			else if (command == "end")
			{
				end = true;
				Logger::log(CONTEXT(), "User applicaton work was ended", Info);
			}
			else
			{
				cout << "Неизвестная команда попробуйте еще раз" << endl;
				Logger::log(CONTEXT(), "Uncnown command was entered by user", Info);
			}
		}
		catch (const std::exception& exc)
		{
			Logger::log(CONTEXT(), exc.what(), Error);
			cout << endl;
			cout << "Произошла ошибка: "<<endl << exc.what();
			cout << endl;
		}
	}
}