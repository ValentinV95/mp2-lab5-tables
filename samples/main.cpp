

#include "../include/UI.h"


int main()
{
	setlocale(LC_ALL, "Russian");



	/*


	//                      Зона тестов Красно-чёрного дерева (Снять коментарий)

	R_B_Tree<polinom> A;

	polinom POL;


	//A.input()            <-  Ввод нового элемента в дерево


	A.insert("a", POL);
	A.insert("b", POL);
	A.insert("c", POL);
	A.insert("d", POL);


	A.insert("e", POL);
	A.insert("f", POL);
	A.insert("g", POL);
	A.insert("h", POL);
	A.insert("i", POL);
	A.insert("j", POL);
	A.insert("k", POL);

	/*
	A.insert("l", 50);
	A.insert("m", 50);
	A.insert("n", 50);
	A.insert("o", 50);
	A.insert("p", 50);
	A.insert("q", 50);
	A.insert("r", 50);
	A.insert("s", 50);
	A.insert("t", 50);
	A.insert("u", 50);
	A.insert("v", 50);
	A.insert("w", 50);
	A.insert("x", 50);
	A.insert("y", 50);
	A.insert("z", 50);
	*/
	/*
	A.remove("a");
	A.remove("b");
	A.remove("c");
	A.remove("d");         //   <--- Удаление элемента из дерева

	//        left->       right->   ->left->right->right
	cout << endl << endl;
	
	cout << "Parent:  key = " << A.Root->right->right->key << "      colour = " << A.show_colour(A.Root->right->right->colour) << endl;
	cout << endl << endl;
	cout << "key = j    colour = " << A.show_colour(A.find("j")->colour) <<"       "; show_polinom(A.find("j")->data);

	system("pause");

	*/




	try
	{

		unordered_table<polinom> UN;
		R_B_Tree<polinom> RB;
		Hash<polinom> H;
		int faith = 0;

		while (true)
		{
			cout << " Выберите тему:" << endl;
			cout << "1) неупорядоченная таблица" << endl;
			cout << "2) Красно-чёрное Дерево" << endl;
			cout << "3) Хэш-таблица" << endl;
			cout << "4) Логгирование" << endl;
			cout << endl << endl;
			cout << endl << endl;
			cout << "0) Завершить программу" << endl;
			cout << endl << endl << "Выбор: ";
			cin >> faith;

			system("cls");

			if (faith == 1) //неупорядоченная таблица
			{
				int size;
				while (true)
				{
					cout << endl << endl << "Введите размер таблицы (изменить его потом уже будет нельзя)" << endl << endl;
					cout << "Размер (больше 0) : ";
					cin >> size;
					if (size <= 0)
					{
						cout << endl << "Размер должен быть больше 0" << endl << endl;
					}
					else
					{
						break;
					}
				}

				cout << endl << endl << endl << endl;
				system("pause");
				cout << endl;

				system("cls");

				UN.set_size(size);

				UNORDERED_TABLE(UN);
			}

			if (faith == 2) // Красно - чёрное Дерево
			{
				RED_BLACK_TREE(RB);
			}

			if (faith == 3) //Хэш-таблица
			{
				HASH_TABLE(H);
			}

			if (faith == 4) //Логгирование
			{
				ALL_IN_ONE();
			}

			if (faith == 0) break;
		}
	}


	catch (const exception error)
	{
		cout << endl << endl << "  <!> ОШИБКА <!>" << endl << " > " << error.what() << endl;
	}



	

}