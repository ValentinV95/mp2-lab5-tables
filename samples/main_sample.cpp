#include <iostream>
#include <locale.h>
#include <fstream>
#include "polynomial.h"
#include "unordered_table.hpp"
#include "ordered_table.hpp"
#include "hash_table.hpp"

using namespace std;

enum MainMenu
{
	enter = 1, output, operations, deleting,
};

enum OutputMenu
{
	out_all = 1, out_one,
};

enum OperationMenu
{
	A_plus_B = 1, A_minus_B, B_minus_A, A_mult_B, A_mult_Const, B_mult_Const,
};

void shortLine()
{
	cout << "__________________________________________" << endl;
}

void longLine()
{
	cout << "____________________________________________________________________________" << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	UnorderedTable<Polynomial> table1;
	OrderedTable<Polynomial> table2;
	HashTable<Polynomial> table3;
	int choice1 = 0, choice2 = 0, choice3 = 0, exitcode = 1;
	bool logsout = true;
	string name;

	try
	{
		while (exitcode)
		{
			ofstream out("../../src/logs.txt", ofstream::trunc);
			out.close();

			cout << "Выберите действие: " << endl;
			cout << "1) Ввести полином" << endl;
			cout << "2) Вывести полином/ы" << endl;
			cout << "3) Операция над полиномом/ами" << endl;
			cout << "4) Удалить полином из таблицы" << endl;
			cout << "Другие клавиши - выйти " << endl;
			cout << "Ваш выбор: ";
			cin >> choice1;

			shortLine();

			switch (choice1) {
			case enter:
			{
				cout << "Правила пользования: " << endl;
				cout << "1) Сначала вы должны ввести количество мономов в полиноме" << endl;
				cout << "2) Дальше для каждого монома вводится его степень" << endl;
				cout << "3) Введите коэффициент монома" << endl;
				cout << "4) Повторяйте шаги 2) и 3) до тех пор, пока не появится меню выбора операций" << endl;
				cout << "5) Выберите операцию над мономами" << endl;
				cout << "!!!Заметьте: " << endl;
				cout << "   Количество сотен отвечает за степень у 'x'" << endl;
				cout << "   Количество десятков - степень 'y'" << endl;
				cout << "   Количество единиц - степень 'z'" << endl;
				cout << "   Максимальная степень - 999!!!" << endl;
				shortLine();

				Polynomial A;

				A.setPolynomial();

				cout << endl << "Введите название полинома: ";
				cin >> name;

				if (table3.search(name))
				{
					cout << "Полином с таким названием уже есть" << endl;
					cout << "Повторите попытку" << endl;
					logsout = false;
					break;
				}

				Pair<Polynomial> tpair(name, A);

				table1.push(tpair);
				table2.push(tpair);
				table3.push(tpair);

				break;
			}

			case output:
			{
				cout << "Хотите вывести всю таблицу?" << endl;
				cout << "1) Вывести все таблицы по порядку" << endl;
				cout << "2) Вывести полином по названию" << endl;
				cout << "Остальные клавиши - вернуться к первоначальному меню" << endl;
				cout << "Ваш выбор: ";
				cin >> choice2;

				shortLine();

				switch (choice2) {
				case out_all:
				{
					logsout = false;
					cout << "Неупорядочная таблица: " << endl;
					table1.getTable();
					cout << endl <<  "Упорядочная таблица: " << endl;
					table2.getTable();
					cout << endl << "Хэш таблица: " << endl;
					table3.getTable();
					break;
				}

				case out_one:
				{
					cout << "Введите название полинома: ";
					cin >> name;
					cout << "Результат поиска:" << endl;
					cout << "1) В неупорядочной таблице: ";
					if (table1.search(name)) table1.search(name)->getPolynomial();
					else cout << "nullptr" << endl;
					cout << "2) В упорядочной таблице: ";
					if (table2.search(name)) table2.search(name)->getPolynomial();
					else cout << "nullptr" << endl;
					cout << "3) В хэш таблице: ";
					if (table3.search(name)) table3.search(name)->getPolynomial();
					else cout << "nullptr" << endl;
					break;
				}

				default:
				{
					break;
				}}

				break;
			}

			case operations:
			{
				cout << "Введите название полинома A: ";
				cin >> name;

				if (!table3.search(name))
				{
					cout << "Полинома с таким названием нет" << endl;
					cout << "Повторите попытку" << endl;
					logsout = false;
					break;
				}

				Polynomial A = *table3.search(name);
				Polynomial B, C;
				cout << "Полином \"" << name << "\": ";
				A.getPolynomial();
				cout << endl;

				cout << "Выберите операцию: " << endl;
				cout << "1) C = A + B" << endl;
				cout << "2) C = A - B" << endl;
				cout << "3) C = B - A" << endl;
				cout << "4) C = A * B" << endl;
				cout << "5) C = A * const" << endl;
				cout << "6) C = B * const" << endl;
				cout << "Остальные клавиши - вернуться к первоначальному меню" << endl;
				cout << "Ваш выбор: ";
				cin >> choice3;

				if (B_mult_Const < choice3 || choice3 < A_plus_B) break;

				shortLine();

				if (A_plus_B <= choice3 && choice3 < A_mult_Const)
				{
					cout << "Введите название полинома B: ";
					cin >> name;
					
					if (!table3.search(name))
					{
						cout << "Полинома с таким названием нет" << endl;
						cout << "Повторите попытку" << endl;
						logsout = false;
						break;
					}

					B = *table3.search(name);

					cout << "Полином \"" << name << "\": ";
					A.getPolynomial();
					cout << endl;
				}

				while (1)
				{
					cout << "Введите имя для полинома С: ";
					cin >> name;

					if (!table3.search(name)) break;

					cout << "Данное имя уже занято" << endl;
					cout << "Повторите попытку" << endl;
					shortLine();
				}

				switch (choice3) {
				case A_plus_B:
				{
					cout << "Полином C = A + B: ";
					C = A + B;
					C.getPolynomial();
					break;
				}
				
				case A_minus_B:
				{
					cout << "Полином C = A - B: ";
					C = A - B;
					C.getPolynomial();
					break;
				}

				case B_minus_A:
				{
					cout << "Полином C = B - A: ";
					C = B - A;
					C.getPolynomial();
					break;
				}

				case A_mult_B:
				{
					cout << "Полином C = A * B: ";
					C = A * B;
					C.getPolynomial();
					break;
				}

				case A_mult_Const:
				{
					double var;
					cout << "Введите константу: ";
					cin >> var;

					cout << "Полином C = A * const: ";
					C = A * var;
					C.getPolynomial();
					break;
				}

				case B_mult_Const:
				{
					double var;
					cout << "Введите константу: ";
					cin >> var;

					cout << "Полином C = B * const: ";
					C = B * var;
					C.getPolynomial();
					break;
				}

				default:
				{
					break;
				}}

				table1.push(Pair<Polynomial>(name, C));
				table2.push(Pair<Polynomial>(name, C));
				table3.push(Pair<Polynomial>(name, C));

				break;
			}

			case deleting:
			{
				cout << "Введите название полинома: ";
				cin >> name;

				if (!table3.search(name))
				{
					cout << "Полинома с таким названием нет" << endl;
					cout << "Повторите попытку" << endl;
					logsout = false;
					break;
				}

				table1.deleteRow(name);
				table2.deleteRow(name);
				table3.deleteRow(name);

				break;
			}

			default:
			{
				exitcode = 0;
				logsout = false;
				break;
			}
			}

			if (enter <= choice1 && choice1 <= deleting && logsout == true)
			{
				string outputSample = " ";
				ifstream input("../../src/logs.txt");

				shortLine();
				
				cout << "Логи: " << endl;

				if (input.is_open())
				{
					while (getline(input, outputSample))
					{
						cout << outputSample << endl;
					}
				}

				input.close();
			}

			logsout = true;
			shortLine();
		}
	}

	catch (const string msg)
	{
		cout << endl;
		shortLine();
		cout << msg << endl;
		shortLine();
	}
}