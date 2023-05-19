#pragma once

#include "../polinom/include/polinom_functions.h"



template<typename T> class unordered_table
{
public:
	pair<string, T>* vec;

	int size;

	int numbers;
	string secret_info;

	int get_numbers()
	{	
		return numbers;
	}



	unordered_table()
	{
		vec = nullptr;
		size = 0;
	}

	void set_size(int tmp_size)
	{
		size = tmp_size; 
		vec = new pair<string, T>[size];
		T tmp;
		for (int i = 0; i < size; i++)
		{
			vec[i].first = "no!";
			vec[i].second = tmp; //������� �� ��������� 0
		}

	}

	unordered_table(int tmp_size)
	{
		size = tmp_size;
		vec = new pair<string, T>[size];
		T tmp;
		for (int i = 0; i < size; i++)
		{
			vec[i].first = "no!";
			vec[i].second = tmp; //������� �� ��������� 0
		}

	}




	int find(string tmp)
	{
		numbers = 0;
		for (int count = 0; count < size; count++)
		{
			numbers++;

			if (vec[count].first == tmp)
			{
				return count;
			}
		}
		return -1;
	}





	void show()
	{
		cout << endl << endl << "������ ��� ����� �������� �������" << endl;
		cout << " �������� ���� �����:" << endl << endl;
		cout << " 1) ��� ������� �������" << endl;
		cout << " 2) ������ � ����������" << endl << endl << endl;
		cout << " �����: ";

		int choice = 0;
		cin >> choice;

		system("cls");

		int j = 1;
		for (int i = 0; i < size; i++)
		{
			if (choice == 1)
			{
				cout << " " << i + 1 << "]  ����: " << vec[i].first << "        ";
				show_polinom(vec[i].second);
			}
			if (choice == 2 && vec[i].first != "no!")
			{
				cout << " " << j << "]  ����: " << vec[i].first << "        ";
				show_polinom(vec[i].second);
				j++;
			}


		}


	}





	void insert(string tmp_key, polinom tmp_pol)
	{
		int i;
		numbers=0;

		for (i = 0; i < size; i++)
		{
			numbers++;
			if (vec[i].first == "no!") break;

		}
		if (i == size)
		{
			int vibor;
			cout << endl << endl << " � ������� ��� �����. ����� �������� ����, �������� ��� ������� �����-�� ������� � ������� �� �����" << endl << endl;
			cout << " 1) �������� ����" << endl;
			cout << " 2) �������� ������� � �������" << endl;
			cout << " 3) ������� ������� � �������" << endl;
			cout << endl << endl << endl << " �����: ";
			cin >> vibor;
			numbers++;
			if (vibor == 2)
			{
				string tmp_str;

				show();
				numbers++;
				while (true)
				{
					numbers++;
					cout << endl << endl << "������� ����. �� �������� ���� ������� �� �����" << endl << endl;
					cout << " ����: ";
					cin >> tmp_str;
					numbers++;
					if (find(tmp_str) == -1)
					{
						cout << endl << "������ ����� ���" << endl;
					}
					else
					{
						vec[find(tmp_str)].second = tmp_pol;
						break;
					}
				}


			}
			numbers++;
			if (vibor == 3)
			{
				delete_table();
				insert(tmp_key, tmp_pol);
			}
		}
		else
		{
			vec[i].first = tmp_key;
			vec[i].second = tmp_pol;
		}
	}






	void delete_table()
	{
		system("cls");
		string tmp_str2;

		T pol;
		
		while (true)
		{
			cout << endl << endl << "������� ���� ���������� ��������: ";
			cin >> tmp_str2;
			numbers++;
			if (find(tmp_str2) == -1)
			{
				cout << endl << "������ ����� ���" << endl;
			}
			else
			{
				vec[find(tmp_str2)].second = pol;
				vec[find(tmp_str2)].first = "no!";

				break;
			}
		}
	}










	void input()
	{
		cout << endl << "���� ��������:" << endl << endl;

		cout << "������� ���������� ������� � ��������:  ";
		int n = amount_of_monoms();

		polinom A = create_polinom(n);

		cout << endl << endl << endl << endl;
		system("pause");
		cout << endl;

		show_polinom(A);

		cout << endl << endl;

		cout << " ���������� ���� ���������� ���� ��� ������� �������� (������ ������ - ��������� ��������� �����). ";
		cout << endl << " ���� �����: ";
		string tmp;
		int iter = 0;

		while (true)
		{
			cin >> tmp;
			if (tmp == "no!")
			{
				break;
			}
			iter = find(tmp);
			if (iter == -1)
			{
				secret_info = tmp;
				insert(tmp, A);
				break;
			}
			else
			{
				cout << endl << endl << " ������ ���� �� ��������. ���������� �����" << endl << endl;
				cout << endl << "���� �����:    ";
			}

		}


	}







};





