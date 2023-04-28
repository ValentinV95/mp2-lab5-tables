
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include "../include/array.h"
#include "../polinom/src/polinom.cpp"
#include "../polinom/include/polinom.h"
#include "../include/AVL_Tree.h"
#include "../include/hash-table.h"

void run_insert(const std::string& com, non_sort_table<Polinoms>& A, Sorting_table<Polinoms>& B, HashTable<Polinoms>& C)
{
	if (com[6] == '[')
	{
		std::string key;
		int i = 7;
		for (; i < com.size(); i++)
		{
			if (com[i] == ']')
				break;
			else
				key += com[i];
		}
		i++;
		std::string polinom;
		if (com[i] == '[') //insert[][]
		{
			i++;
			
			for (; i < com.size(); i++)
			{
				if (com[i] == ']')
					break;
				else
					polinom += com[i];
			}

			A.Add(key, Polinoms(polinom));
			B.Add(key, Polinoms(polinom));
			C.Add(key, Polinoms(polinom));
		}
		else if (com[i] == '+' || com[i] == '-' || com[i] == '*') //insert[]+[]
		{
			char id_op = com[i];
			i++;
			if (com[i] == '[')
			{
				i++;
				std::string polinom1;
				for (; i < com.size(); i++)
				{
					if (com[i] == ']')
						break;
					else
						polinom1 += com[i];
				}

				if (id_op == '+')
				{
					A.Add(key, Polinoms(polinom) + Polinoms(polinom1));
					B.Add(key, Polinoms(polinom) + Polinoms(polinom1));
					C.Add(key, Polinoms(polinom) + Polinoms(polinom1));
				}
				else if (id_op == '-')
				{
					A.Add(key, Polinoms(polinom) + (Polinoms(polinom1) * (-1)));
					B.Add(key, Polinoms(polinom) + (Polinoms(polinom1) * (-1)));
					C.Add(key, Polinoms(polinom) + (Polinoms(polinom1) * (-1)));
				}
				else
				{
					A.Add(key, Polinoms(polinom) * Polinoms(polinom1));
					B.Add(key, Polinoms(polinom) * Polinoms(polinom1));
					C.Add(key, Polinoms(polinom) * Polinoms(polinom1));
				}	
			}
			else
			{
				if (com[i] >= '0' && com[i] <= '9') //insert[]*a
				{
					std::string num;
					while (i < com.size())
						num += com[i];

					A.Add(key, Polinoms(polinom) * convert(num));
					B.Add(key, Polinoms(polinom) * convert(num));
					C.Add(key, Polinoms(polinom) * convert(num));
				}
				else
					std::cout << "error: no correct command" << std::endl;
			}	
		}
		else
			std::cout << "error: no correct command" << std::endl;
	}
	else
	{
		std::cout << "error: no correct command" << std::endl;
	}
}

void run_extract(const std::string& com, non_sort_table<Polinoms>& A, Sorting_table<Polinoms>& B, HashTable<Polinoms>& C)
{
	if (com[4] == '[')
	{
		std::string key;
		for (int i = 5; i < com.size(); i++)
		{
			if (com[i] == ']')
			{
				A.Extract(key);
				B.Extract(key);
				C.Extract(key);
			}
			else
				key += com[i];
		}
	}
	else
	{
		std::cout << "error: no correct command" << std::endl;
	}
}

void run_show(const std::string& com, non_sort_table<Polinoms>& A, Sorting_table<Polinoms>& B, HashTable<Polinoms>& C)
{
	if (com.size() == 4)
	{
		int choose;
		std::cout << "from which structure to show the table?\n1 - non_sort_table\n2 - sorting table\n3 - hash table" << std::endl;
		std::cin >> choose;
		if (choose == 1)
			A.show();
		else if (choose == 2)
			B.show();
		else if (choose == 3)
			C.show();
		else
			std::cout << "error: no correct choose" << std::endl;
	}
	else
	{
		if (com[4] == '[')
		{
			std::string key;
			for (int i = 5; i < com.size(); i++)
			{
				key += com[i];
				if (com[i] == ']')
				{
					int c;
					std::cout << "from which structure to show the table?\n1 - non_sort_table\n2 - sorting table\n3 - hash table" << std::endl;
					std::cin >> c;
					if (c == 1)
						A.show(A.Search(key));
					else if (c == 2)
						B.show(B.Search(key));
					else if (c == 3)
						C.show(C.Search(key));
					else
						std::cout << "error: no correct choose" << std::endl;
				}
				else
					key += com[i];
			}
		}
		else
		{
			std::cout << "error: no correct command" << std::endl;
		}
	}
}

void Parse_command(const std::string& com, non_sort_table<Polinoms>& A, Sorting_table<Polinoms>& B, HashTable<Polinoms>& C)
{
	if (com.size() > 6 && com[0] == 'i' && com[1] == 'n' && com[2] == 's' && com[3] == 'e' && com[4] == 'r' && com[5] == 't') //insert
	{
		run_insert(com, A, B, C);
	}
	else if (com.size() > 7 && com[0] == 'e' && com[1] == 'x' && com[2] == 't' && com[3] == 'r' && com[4] == 'a' && com[5] == 'c' && com[6] == 't')
	{
		run_extract(com, A, B, C);
	}
	else if (com.size() >= 4 && com[0] == 's' && com[1] == 'h' && com[2] == 'o' && com[3] == 'w')
	{
		run_show(com, A, B, C);
	}
	else if (com.size() >= 4 && com[0] == 'e' && com[1] == 'x' && com[2] == 'i' && com[3] == 't')
	{
		exit(0);
	}
	else
	{
		std::cout << "Bad command. Please try again" << std::endl;
	}
}

int main()
{
	int size;
	std::cout << std::setw(60) << "3 TYPE TABLE WITH POLINOMS" << std::endl;
	std::cout << "Select the table size (number of rows):" << std::endl;
	std::cin >> size;
	non_sort_table<Polinoms> A(size);
	Sorting_table<Polinoms> B;
	HashTable<Polinoms> C(size);
	Sleep(1000);
	while (true)
	{
		system("cls");
		std::string command;
		std::cout << std::setw(60) << "3 TYPE TABLE WITH POLINOMS" << std::endl;
		std::cout << "RULES: 1) dont use: space, name - ONLY letters and numbers \n2) Name is less than 21 characters" << std::endl;
		std::cout << "Enter your request using this commands:\n1.1) insert[name][polinom] - insert new polinom in table\n1.2) insert[name]!operation![name] - insert polinom as sum or multiplication\n1.3) insert[name]!operation!!number! - insert polinom as multiplication with number" << std::endl;
		std::cout << "EXAMPLE:\ninsert[abc][123xyz]\ninsert[abc]+[def]\ninsert[abc]*4" << std::endl;
		std::cout << "2) extract[name] - delete polinom in table" << std::endl;
		std::cout << "EXAMPLE:\nextract[abc]" << std::endl;
		std::cout << "3.1) show[name] - show polinom in table\n3.2) show - show all table" << std::endl;
		std::cout << "EXAMPLE:\nshow[abc]\nshow" << std::endl;
		std::cout << "4) exit - exit in programm and finished" << std::endl;
		std::cout << "/> ";
		std::cin >> command;
		try
		{
			Parse_command(command, A, B, C);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		system("pause");
	}
}