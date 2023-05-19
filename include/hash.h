#pragma once

#include "../polinom/include/polinom_functions.h"



int all_collision = 0;
int end_collision = 0;





int h(string tmp_key)
{
	if (tmp_key[0] < 97 || tmp_key[0]>123)
	{
		throw exception("Bad key");
	}
	char a = tmp_key[0] - 97;
	int res = int(a) % 26;
	return res;
}






template<class T> class Hash
{
public:

	pair<string, T> vec[99];



	int numbers;


	int get_numbers()
	{
		return numbers;
	}




	Hash()
	{

		for (int i = 0; i < 99; i++)
		{
			string key = "no!";
			T a;
			vec[i].first = key;
			vec[i].second = a;

		}

	}


	int find(string tmp)
	{
		int i = h(tmp);
		numbers=0;
		for (int count = 0; count < 99; count++)
		{
			numbers++;
			if (vec[i].first != tmp)
			{
				i = (i + 26) % 99;
			}
			else if (vec[i].first == tmp)
			{
				return i;
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

		if (choice == 1)
		{
			for (int i = 0; i < 99; i++)
			{
				cout << " " << i + 1 << "]  ����: " << vec[i].first << "        ";
				show_polinom(vec[i].second);
				cout << endl;
			}
		}
		else if (choice == 2)
		{

			int j = 1;
			for (int i = 0; i < 99; i++)
			{
				if (vec[i].first != "no!")
				{
					cout << " " << j << "]  ����: " << vec[i].first << "        ";
					show_polinom(vec[i].second);
					cout << endl;
					j++;
				}
			}
		}
		else
		{
			throw exception("Bad input");
		}
	}

	void delete_table()
	{
		system("cls");
		string tmp_str2;

		T pol;

		numbers=0;
		numbers++;
		while (true)
		{
			numbers++;
			cout << endl << endl << "������� ���� ���������� ��������: ";
			cin >> tmp_str2;
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

	void insert(string tmp_key, T tmp_T)
	{
		int i = 0;
		i = h(tmp_key);

		numbers=0;
		while (true)
		{
			
			if (vec[i].first != "no!")
			{
				numbers++;
				all_collision++;
				i = (i + 26) % 99;  // %99 �.�. ������ �� 99 ��������� 
				numbers++;
				if (i == h(tmp_key))
				{
					numbers++;
					cout << endl << "   [!] �������� [!]" << endl << " ��� ���� �� �������� (���� ���). � ��������� ��� ���� ���� �������� �� ������� ���� �� ��������� �������� �������� � ��� ���������� �����" << endl << endl;
					cout << " 1) �� �������� " << endl;
					cout << " 2) ��������" << endl << endl << endl << endl;
					cout << " �����: ";
					int choice = 0;
					cin >> choice;
					
					if (choice == 1)
					{
						numbers++;
						end_collision++;
						break;
					}
					
					if (choice == 2)
					{
						numbers++;
						cout << endl << endl << "��� ����� ������������� �������. ��������� ������ ��� ����.";
						show();
						cout << endl << endl << "������� ����, ����� �������� �������. ���� ����������, �� ������� 'no!'." << endl << endl << " ����: ";
						string  old_key;
						cin >> old_key;
						numbers++;
						if (old_key == "no!")
						{
							end_collision++;
							break;
						}



						int k = find(old_key);
						
						if (k >= 0)
						{
							vec[k].second = tmp_T;
						}
						
						if (k == -1)
						{
							numbers++;
							cout << endl << endl << "���� �� �������" << endl << endl;
						}

					}

					end_collision++;
					break;
				}
			}
			else
			{
				vec[i].first = tmp_key;
				vec[i].second = tmp_T;
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




void show_how_1()
{
	cout << endl << endl;

	cout << "             ____________________________________________________________________ " << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            | ���� �����: ����� ������� ������������ � ��� ��� ������ �� ������� |" << endl;
	cout << "            |____________________________________________________________________|" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  ������ ������ ����� ������ ������ ���� ������ �� ����������       |" << endl;
	cout << "            |  ��������, ����� ���-������� ������������ ������� � �������.       |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  � ���-������� ������������ ������ ������ ����� ( string ).        |" << endl;
	cout << "            |  ���-������� ��� �� ���������� �������������� ����� � ��������.    |" << endl;
	cout << "            |  �.�. ���� � �������� 26 �� ���-������� ���������� ������� ��      |" << endl;
	cout << "            |  ������� �� 26. H(x) = x % 26. � ������ ��������: +26              |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  ������ � ����������� ������� ����� ���� ������.                   |" << endl;
	cout << "            |____________________________________________________________________|" << endl;
	cout << endl << endl;
}


void show_how_2()
{
	cout << endl << endl;

	cout << "             ____________________________________________________________________ " << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            | ��������� �����: ����� ���������� � ���������� ����� ����������    |" << endl;
	cout << "            | �������, ����� ����� ������ �������� � �� �����                    |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  �� ��������� ������� �� ����� ������.                             |" << endl;
	cout << "            |____________________________________________________________________|" << endl;

	cout << endl << endl;
}







