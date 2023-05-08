#include <iostream>
#include "TRbTreeTable.hpp"
#include "TTable.hpp"
#include "THashTable.hpp"
#include "Logger.hpp"
#include "polinom.h"

using namespace std;

Polynom finde(string name, THashTable<string, Polynom>& hashTbl, TRbTreeTable<string, Polynom>& treeTbl, TTable<string, Polynom>& simpleTbl)
{
	treeTbl.find(name);
	simpleTbl.find(name);
	Polynom poly = hashTbl.find(name);

	Logger::log(CONTEXT(), "Polynom " + name + " was found successfully in all tables", Info);
	Logger::log(CONTEXT(), " ", Info);
	return poly;
}

void remove(string name, THashTable<string, Polynom>& hashTbl, TRbTreeTable<string, Polynom>& treeTbl, TTable<string, Polynom>& simpleTbl)
{
	treeTbl.remove(name);
	simpleTbl.remove(name);
	hashTbl.remove(name);

	Logger::log(CONTEXT(), "Polynom " + name + " was deleted successfully from all tables", Info);
	Logger::log(CONTEXT(), " ", Info);
}

void insert(string name, Polynom poly, THashTable<string, Polynom>& hashTbl, TRbTreeTable<string, Polynom>& treeTbl, TTable<string, Polynom>& simpleTbl)
{

	hashTbl.insert(name, poly);
	simpleTbl.insert(name, poly);
	treeTbl.insert(name, poly);

	Logger::log(CONTEXT(), "Polynom " + poly.toString() + " as " + name + " was insert successfully in all tables", Info);
	Logger::log(CONTEXT(), " ", Info);
}

void showInfo()
{
	cout << "--------------------------INFO--------------------------" << endl;
	cout << "�������:" << endl;
	cout << "\t� �������� ���� ���������� � �������� ������������ x,y,z" << endl;
	cout << "\t����� ��� ������ � ��������: �*x^X*y^Y*z^Z" << endl;
	cout << "\t���:" << endl
		<< "\t --a - ������������ �����, ����� ���� �������� � ���������������" << endl
		<< "\t   �����, � �������� ����������� ����� � ������� ����� ��������� ','" << endl
		<< "\t --���������� � �������� ������" << endl
		<< "\t --X,Y � Z - ����� �� 0 �� 9" << endl
		<< "\t --���� ���������� ������� �������������" << endl
		<< "\t --�� ����������� ��� �� ����� �������� ��� ���������� " << endl
		<< "\t --������� ���������� ���������� �������" << endl
		<< "\t --��������� ��������: +, -, *"
		<< endl;
	cout << "�������:" << endl;
	cout << "\t��������:" << endl
		<< "\t--������� ������� �� ������� ������� delete" << endl
		<< "\t--�������� ������� � ������� ������� insert" << endl
		<< "\t--����������� ���������� ������ ������� show" << endl
		<< "\t--����� ����� ������� �� ����� ������� finde" << endl;
	cout << "--��� �� ��������� �������������� �������� ��� ���������" << endl
		<< "����� ������ ��� ������� ��������, ��������, ��� ������� �������� ��� ��������" << endl;
	cout << "--����� ��������� �������, ���������� � ���������� �������������� ��������," << endl
		<< "��� ������� � ����� ������ ��� ��� ������ ������� ��������� ��������" << endl;
	cout << "--��� �������� ����� ��������� ������ ����� a-z,A-Z � ����� �� 0 �� 1," << endl
		<< "  ���� ������� ����� �������� � ������������ ������ ���������" << endl;
	cout << "--��� ���������� ��������� ������� end" << endl;
	cout << "--------------------------------------------------------" << endl;
}

void main()
{
	Logger::log(CONTEXT(), " ", Info);
	Logger::log(CONTEXT(), "Program started", Info);

	setlocale(LC_ALL, "Russian");

	showInfo();

	THashTable<string, Polynom> hashTbl(10000);
	TRbTreeTable<string, Polynom> treeTbl;
	TTable<string, Polynom> simpleTbl;

	string command;
	bool end = false;

	while (!end)
	{
		cout << endl << "������� �������: ";
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

					Polynom poly1, poly2, poly3;

					poly1 = finde(name1, hashTbl, treeTbl, simpleTbl);
					poly2 = finde(name2, hashTbl, treeTbl, simpleTbl);

					switch (operation)
					{
					case('+'):
						poly3 = poly1 + poly2;
						break;
					case('-'):
						poly3 = poly1 - poly2;
						break;
					case('*'):
						poly3 = poly1 * poly2;
						break;
					}

					cout << poly3 << endl;

					cout << "\t������ ��������� ���������? yes/no : ";
					cin >> command;

					if (command == "yes")
					{
						cout << "\n\t������� ��� ��� �������� ";
						cin >> name1;

						remove(name1, hashTbl, treeTbl, simpleTbl);
						insert(name1, poly3, hashTbl, treeTbl, simpleTbl);
					}
				}
				else
				{
					cout << "������� �� �������� �� ������ ��������." << endl
						<< "��� ���������� �������������� �������� ������� ������" << endl
						<< "��������� ������ ���� �������" << endl;
				}
			}
			else if (command == "insert")
			{
				string name, polinom;
				cout << "\t������� ��� ��������: ";
				cin >> name;
				cout << "\t������� �������: ";
				cin >> polinom;

				insert(name, Polynom(polinom), hashTbl, treeTbl, simpleTbl);
				cout << endl << "������� ��� ������� ��������!" << endl;
			}
			else if (command == "delete")
			{
				string name;
				cout << "\t������� ��� ��������: ";
				cin >> name;

				remove(name, hashTbl, treeTbl, simpleTbl);
				cout << endl << "������� ��� ������� ������!" << endl;
			}
			else if (command == "show")
			{
				cout << "��������������� �������: " << endl;
				simpleTbl.show();
				cout << endl;

				cout << "���-�������: " << endl;
				hashTbl.show();
				cout << endl;

				cout << "������-������ ������: " << endl;
				treeTbl.show();
				cout << endl;
			}
			else if (command == "finde")
			{
				string name;
				cout << "\t������� ��� ��������: ";
				cin >> name;

				cout << "\tPolynom named as " << name << " is - " << finde(name, hashTbl, treeTbl, simpleTbl) << endl;
			}
			else if (command == "end")
			{
				end = true;
			}
			else
			{
				cout << "����������� ������� ���������� ��� ���" << endl;
			}
		}
		catch (const std::exception& exc)
		{
			cout << endl;
			cout << "��������� ������: " << endl << exc.what();
			cout << endl;
		}
	}

	Logger::log(CONTEXT(), "Program finished", Info);
	Logger::log(CONTEXT(), " ", Info);
}