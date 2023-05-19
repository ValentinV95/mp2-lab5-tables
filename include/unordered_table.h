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
			vec[i].second = tmp; //полином по умолчанию 0
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
			vec[i].second = tmp; //полином по умолчанию 0
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
		cout << endl << endl << "Сейчас Вам будет показана таблица" << endl;
		cout << " Выберите себе стиль:" << endl << endl;
		cout << " 1) Вся таблица целиком" << endl;
		cout << " 2) Только с полиномами" << endl << endl << endl;
		cout << " Выбор: ";

		int choice = 0;
		cin >> choice;

		system("cls");

		int j = 1;
		for (int i = 0; i < size; i++)
		{
			if (choice == 1)
			{
				cout << " " << i + 1 << "]  Ключ: " << vec[i].first << "        ";
				show_polinom(vec[i].second);
			}
			if (choice == 2 && vec[i].first != "no!")
			{
				cout << " " << j << "]  Ключ: " << vec[i].first << "        ";
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
			cout << endl << endl << " В таблице нет места. Можно отменить ввод, заменить или удалить какой-то элемент в таблице по ключу" << endl << endl;
			cout << " 1) Отменить ввод" << endl;
			cout << " 2) заменить элемент в таблице" << endl;
			cout << " 3) Удалить элемент в таблице" << endl;
			cout << endl << endl << endl << " Выбор: ";
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
					cout << endl << endl << "Введите ключ. Вы замените этот полином на новый" << endl << endl;
					cout << " Ключ: ";
					cin >> tmp_str;
					numbers++;
					if (find(tmp_str) == -1)
					{
						cout << endl << "Такого ключа нет" << endl;
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
			cout << endl << endl << "Введите ключ удаляемого полинома: ";
			cin >> tmp_str2;
			numbers++;
			if (find(tmp_str2) == -1)
			{
				cout << endl << "Такого ключа нет" << endl;
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
		cout << endl << "Ввод полинома:" << endl << endl;

		cout << "Введите количество мономов в полиноме:  ";
		int n = amount_of_monoms();

		polinom A = create_polinom(n);

		cout << endl << endl << endl << endl;
		system("pause");
		cout << endl;

		show_polinom(A);

		cout << endl << endl;

		cout << " Придумайте свой уникальный ключ для данного полинома (первый символ - латинская маленькая буква). ";
		cout << endl << " Ввод ключа: ";
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
				cout << endl << endl << " Данный ключ не подходит. Попробуйте снова" << endl << endl;
				cout << endl << "Ввод ключа:    ";
			}

		}


	}







};





