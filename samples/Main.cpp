#include "../include/HASH_TABLE.h"



int main()
{


	int N,k,aht;
	double scalar;
	cout << "Its programm about work Polinoms with different tables." << endl;
	cout << "First we need to full tables, input number of elements in table : ";
	cin >> N;

	ARRAY<Polinom> Array;
	HASH_TABLE<Polinom, 1> Table(N);
	AWL_TREE<Polinom> Tree;
	string str;
	for (int i = 0; i < N; i++)
	{
		Polinom C;
		cout << "Cin your " << i << " Polinom: " << endl;
		cin >> str;
		C.string_to_polinom(str);
		k = key(C);
		cout << "Your Polinom is: ";
		C << cout << endl << "Key of Polinom: " << k << endl;
		Array.push(make_pair(k, C));
		Table.push(make_pair(k, C));
		Tree.push(make_pair(k, C));
	}
	show_log();

	
	
	Polinom A, B, zero;
	zero.string_to_polinom("0");

	while (true)
	{
		NULL_LOG();
		cout << "What you want to do with your Polinoms?\n\n1)Operation\n2)Search\n3)Del\nstop)stop programm" << endl;
		cin >> str;
		if (str == "1")
		{	
			system("CLS");
			cout << "What you want to do?\n\n1)Polinom A + Polinom B\n2)Polinom A * scalar b\n3)Polinom A * Polinom B\n4)Polinom A - Polinom B\nstop)stop programm" << endl;

			cin >> str;

			if (str == "1")
			{
				cout << "Cin key for Polinom A:";
				cin >> k;
				cout << "Cin key for Polinom B: ";
				cin >> aht;

				if (Array.search(k).first >= 0) A = Array.search(k).second;
				else A = zero;
				if (Array.search(aht).first >= 0) B = Array.search(aht).second;
				else B = zero;
				A = A + B;
				cout << "Array return: ";
				A << cout << endl;

				if (Table.search(k).first >= 0) A = Table.search(k).second;
				else A = zero;
				if (Table.search(aht).first >= 0) B = Table.search(aht).second;
				else B = zero;
				A = A + B;
				cout << "Table return: ";
				A << cout << endl;

				if (Tree.search(k)) A = Tree.search(k)->data.second;
				else A = zero;
				if (Tree.search(aht)) B = Tree.search(aht)->data.second;
				else B = zero;
				A = A + B;
				cout << "Table return: ";
				A << cout << endl;
				show_log();
			}
			else if (str == "2")
			{
				cout << "Cin key for Polinom A:";
				cin >> k;
				cout << "Cin key for scalar b: ";
				cin >> scalar;

				if (Array.search(k).first >= 0) A = Array.search(k).second;
				else A = zero;
				A = A * scalar;
				cout << "Array return: ";
				A << cout << endl;

				if (Table.search(k).first >= 0) A = Table.search(k).second;
				else A = zero;
				A = A * scalar;
				cout << "Table return: ";
				A << cout << endl;

				if (Tree.search(k)) A = Tree.search(k)->data.second;
				else A = zero;
				A = A * scalar;
				cout << "Table return: ";
				A << cout << endl;
				show_log();
			}
			else if (str == "3")
			{
				cout << "Cin key for Polinom A:";
				cin >> k;
				cout << "Cin key for Polinom B: ";
				cin >> aht;

				if (Array.search(k).first >= 0) A = Array.search(k).second;
				else A = zero;
				if (Array.search(aht).first >= 0) B = Array.search(aht).second;
				else B = zero;
				try {
					A = A * B;
				}
				catch (std::exception e)
				{
					cout << e.what() << endl;
				}
				cout << "Array return: ";
				A << cout << endl;

				if (Table.search(k).first >= 0) A = Table.search(k).second;
				else A = zero;
				if (Table.search(aht).first >= 0) B = Table.search(aht).second;
				else B = zero;
				try {
					A = A * B;
				}
				catch (std::exception e)
				{
					cout << e.what() << endl;
				}
				cout << "Table return: ";
				A << cout << endl;

				if (Tree.search(k)) A = Tree.search(k)->data.second;
				else A = zero;
				if (Tree.search(aht)) B = Tree.search(aht)->data.second;
				else B = zero;
				try {
					A = A * B;
				}
				catch (std::exception e)
				{
					cout << e.what() << endl;
				}
				cout << "Table return: ";
				A << cout << endl;
				show_log();
			}
			else if (str == "4")
			{
				cout << "Cin key for Polinom A:";
				cin >> k;
				cout << "Cin key for Polinom B: ";
				cin >> aht;

				if (Array.search(k).first >= 0) A = Array.search(k).second;
				else A = zero;
				if (Array.search(aht).first >= 0) B = Array.search(aht).second;
				else B = zero;
				A = A - B;
				cout << "Array return: ";
				A << cout << endl;

				if (Table.search(k).first >= 0) A = Table.search(k).second;
				else A = zero;
				if (Table.search(aht).first >= 0) B = Table.search(aht).second;
				else B = zero;
				A = A - B;
				cout << "Table return: ";
				A << cout << endl;

				if (Tree.search(k)) A = Tree.search(k)->data.second;
				else A = zero;
				if (Tree.search(aht)) B = Tree.search(aht)->data.second;
				else B = zero;
				A = A - B;
				cout << "Table return: ";
				A << cout << endl;
				show_log();
			}
			else if (str == "stop")
			{
				break;
			}
			cout << "Will back in 15 sec." << endl;
			for (int i = 10; i >= 0; i -= 5)
			{
				Sleep(5000);
				cout << "Will back in " << i << " sec." << endl;
			}
			system("CLS");
		}
		else if (str == "2")
		{
			cout << "Cin key: ";
			cin >> k;
			if (Array.search(k).first != -1)
			{
				cout << "Array found: ";
				Array.search(k).second << cout << endl;
			}
			else cout << "Array didn't found!" << endl;
			if (Table.search(k).first >= 0)
			{
				cout << "Table found: ";
				Table.search(k).second << cout << endl;
			}
			else cout << "Table didn't found!" << endl;
			if (Tree.search(k) != nullptr)
			{
				cout << "Tree found: ";
				Tree.search(k)->data.second << cout << endl;
			}
			else cout << "Tree didn't found!" << endl;
			show_log();
			cout << "Will restart in 15 sec." << endl;
			for (int i = 10; i >= 0; i -= 5)
			{
				Sleep(5000);
				cout << "Will back in " << i << " sec." << endl;
			}
			system("CLS");
		}
		else if (str == "3")
		{
			cout << "Cin key: ";
			cin >> k;
			aht = Array.mas.size();
			Array.del(k);
			if (aht > Array.mas.size()) cout << "Array delete sucess!" << endl;
			else cout << "Array delete not sucess!" << endl;
			aht = Table.real_size;
			Table.del(k);
			if (aht > Table.real_size) cout << "Table delete sucess!" << endl;
			else cout << "Table delete not sucess!" << endl;
			if (Tree.del(k) != nullptr)cout << "Tree delete sucess!" << endl;
			else cout << "Tree delete not sucess!" << endl;
			show_log();
			cout << "Will restart in 15 sec." << endl;
			for (int i = 10; i >= 0; i -= 5)
			{
				Sleep(5000);
				cout << "Will back in " << i << " sec." << endl;
			}
			system("CLS");
		}
		else if (str == "stop")
		{
			break;
		}
		else
		{
			cout << "\nDidn't found this variant, you will restart back in ";
			for (int i = 5; i >= 0; i--)
			{
				Sleep(1000);
				cout << i << " ";
			}

			system("CLS");
		}
	}

}