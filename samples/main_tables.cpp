#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <locale.h>
#include "../include/array.h"
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
		if ((i+1) < com.size() && com[i] == '[' && com[i + 1] != '[') //insert[][]
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
		else if ((i + 1) < com.size() && com[i] == '[' && com[i + 1] == '[') //insert[][[]!operator![]]
		{
			i += 2;
			std::string name_polinom1;
			std::string name_polinom2;
			char id_op;
			while (i < com.size() && com[i] != ']')
			{
				name_polinom1 += com[i];
				i++;
			}
			i++;
			if (i < com.size() && (com[i] == '+' || com[i] == '*' || com[i] == '-'))
			{
				id_op = com[i];
				i++;
				if (i < com.size() && com[i] == '[')
				{
					i++;
					while (i < com.size() && com[i] != ']')
					{
						name_polinom2 += com[i];
						i++;
					}

					if (id_op == '+')
					{
						Polinoms New_polinom = A.Search(name_polinom1).second + A.Search(name_polinom2).second;
						A.Add(key, New_polinom);
						B.Add(key, New_polinom);
						C.Add(key, New_polinom);
					}
					else if (id_op == '*')
					{
						Polinoms New_polinom = A.Search(name_polinom1).second * A.Search(name_polinom2).second;
						A.Add(key, New_polinom);
						B.Add(key, New_polinom);
						C.Add(key, New_polinom);
					}
					else if (id_op == '-')
					{
						Polinoms New_polinom = A.Search(name_polinom1).second + ((A.Search(name_polinom2).second) * (-1));
						A.Add(key, New_polinom);
						B.Add(key, New_polinom);
						C.Add(key, New_polinom);
					}
					else
						std::cout << "what????error" << std::endl;
				}
				else if (i < com.size() && com[i] >= '0' && com[i] <= '9')
				{
					std::string num;
					while (i < com.size() && com[i] == ']')
					{
						num += com[i];
						i++;
					}
					double koef = convert(num);

					if (id_op == '*')
					{
						A.Add(key, Polinoms(name_polinom1) * koef);
						B.Add(key, Polinoms(name_polinom1) * koef);
						C.Add(key, Polinoms(name_polinom1) * koef);
					}
					else
					{
						std::cout << "error: no correct command" << std::endl;
					}
				}
				else
				{
					std::cout << "error: no correct command" << std::endl;
				}
			}
			else
				std::cout << "error: no correct command" << std::endl;
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
	if (com[7] == '[')
	{
		std::string key;
		for (int i = 8; i < com.size(); i++)
		{
			if (com[i] == ']')
			{
				A.Extract(key);
				B.Extract(key);
				C.Extract(key);
				break;
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
	else if (com[4] == '[')
	{
		std::string key;
		for (size_t i = 5; com[i] != ']' && i < com.size(); i++)
		{
			key += com[i];
		}
		std::cout << "Unsorting Table:" << std::endl;
		A.show(A.Search(key));
		std::cout << "\nSort Table:" << std::endl;
		B.show(B.Search(key));
		std::cout << "\nHash Table:" << std::endl;
		C.show(C.Search(key));
	}
	else
	{
		std::cout << "error: no correct command" << std::endl;
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
	setlocale(LC_ALL, "Rus");
	int size;
	std::cout << std::setw(60) << "3 TYPE TABLE WITH POLINOMS" << std::endl;
	std::cout << "Select the table size (number of rows):" << std::endl;
	std::cin >> size;
	non_sort_table<Polinoms> A(size);
	Sorting_table<Polinoms> B;
	HashTable<Polinoms> C(size);
	system("pause");
	while (true)
	{
		system("cls");
		std::string command;
		std::cout << std::setw(60) << "3 TYPE TABLE WITH POLINOMS" << std::endl;
		std::cout << "RULES: 1) dont use: space, name - ONLY letters and numbers \n2) Name is less than 21 characters" << std::endl;
		std::cout << "Enter your request using this commands:\n1.1) insert[name][polinom] - insert new polinom in table\n1.2) insert[new_name][[name]!operation![name]] - insert polinom as sum or multiplication\n1.3) insert[new_name][[name]!operation!!number!] - insert polinom as multiplication with number" << std::endl;
		std::cout << "EXAMPLE:\ninsert[abc][123xyz]\ninsert[name][[abc]+[def]]\ninsert[name][[abc]*4]" << std::endl;
		std::cout << "2) extract[name] - delete polinom in table" << std::endl;
		std::cout << "EXAMPLE:\nextract[abc]" << std::endl;
		std::cout << "3) show - show all table, show[name] - show row" << std::endl;
		std::cout << "EXAMPLE:\nshow\nshow[abc]" << std::endl;
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