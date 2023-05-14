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
		numbers++;
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
		cout << endl << endl << "Сейчас Вам будет показана таблица" << endl;
		cout << " Выберите себе стиль:" << endl << endl;
		cout << " 1) Вся таблица целиком" << endl;
		cout << " 2) Только с полиномами" << endl << endl << endl;
		cout << " Выбор: ";

		int choice = 0;
		cin >> choice;

		system("cls");

		if (choice == 1)
		{
			for (int i = 0; i < 99; i++)
			{
				cout << " " << i + 1 << "]  Ключ: " << vec[i].first << "        ";
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
					cout << " " << j << "]  Ключ: " << vec[i].first << "        ";
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
			cout << endl << endl << "Введите ключ удаляемого полинома: ";
			cin >> tmp_str2;
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

	void insert(string tmp_key, T tmp_T)
	{
		int i = 0;
		i = h(tmp_key);

		numbers=0;
		numbers++;

		while (true)
		{
			numbers++;
			if (vec[i].first != "no!")
			{
				all_collision++;
				i = (i + 26) % 99;  // %99 т.к. массив из 99 элементов 
				numbers++;
				if (i == h(tmp_key))
				{
					cout << endl << "   [!] Внимание [!]" << endl << " Ваш ключ не подходит (мест нет). К сожалению ваш ключ либо вылетает из таблицы либо вы заменяете значение полинома в уже записанном ключе" << endl << endl;
					cout << " 1) Не заменять " << endl;
					cout << " 2) Заменить" << endl << endl << endl << endl;
					cout << " Выбор: ";
					int choice = 0;
					cin >> choice;
					numbers++;
					if (choice == 1)
					{
						end_collision++;
						break;
					}
					numbers++;
					if (choice == 2)
					{
						cout << endl << endl << "Вам будет предоставлена таблица. Запомните нужный вам ключ.";
						show();
						cout << endl << endl << "Введите ключ, чтобы заменить полином. Если передумали, то введите 'no!'." << endl << endl << " Ключ: ";
						string  old_key;
						cin >> old_key;
						numbers++;
						if (old_key == "no!")
						{
							end_collision++;
							break;
						}



						int k = find(old_key);
						numbers++;
						if (k >= 0)
						{
							vec[k].second = tmp_T;
						}
						numbers++;
						if (k == -1)
						{
							cout << endl << endl << "Ключ не нашёлся" << endl << endl;
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




void show_how_1()
{
	cout << endl << endl;

	cout << "             ____________________________________________________________________ " << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            | Ввод ключа: какие символы использовать и как они влияют на таблицу |" << endl;
	cout << "            |____________________________________________________________________|" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  Первый символ ключа всегда должен быть буквой из латинского       |" << endl;
	cout << "            |  алфавита, чтобы хэш-функция распределила полином в таблице.       |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  В Хэш-функции используется первый символ ключа ( string ).        |" << endl;
	cout << "            |  Хэш-функция как бы определяет местоположение буквы в алфавите.    |" << endl;
	cout << "            |  Т.к. букв в алфавите 26 то Хэш-функция возвращает остаток от      |" << endl;
	cout << "            |  деления на 26. H(x) = x % 26. В случае коллизии: +26              |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  Второй и последующие символы могут быть любыми.                   |" << endl;
	cout << "            |____________________________________________________________________|" << endl;
	cout << endl << endl;
}


void show_how_2()
{
	cout << endl << endl;

	cout << "             ____________________________________________________________________ " << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            | Небольшой совет: перед операциями с полиномами стоит посмотреть    |" << endl;
	cout << "            | таблицу, чтобы найти нужные полиномы и их ключи                    |" << endl;
	cout << "            |                                                                    |" << endl;
	cout << "            |  По умолчанию таблица не будет стоять.                             |" << endl;
	cout << "            |____________________________________________________________________|" << endl;

	cout << endl << endl;
}







