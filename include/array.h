#pragma once
#include <exception>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../polinom/include/polinom.h"
#include <Windows.h>
#define GREEN 10
#define WHITE 7

template<typename T>
class non_sort_table {
private:
    std::vector<std::pair<std::string, T>> structure;
	int size;
public:
	non_sort_table()
	{
		this->size = 1;
	}

	non_sort_table(std::string key, T value)
	{
		this->size = 1;
		structure.insert(structure.end(), std::pair<std::string, T>(key, value));
	}

	non_sort_table(int size)
	{
		if (size <= 0)
			throw std::exception("ERROR: negative length");
		this->size = size;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | CONSTRUCT:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " Non sorting table construct" << std::endl;
	}

	std::pair<std::string, T> operator[](int i)
	{
		return this->structure[i];
	}
	/*----------------------------------взаимодействия-с-таблицей--------------------------------------------*/
	void Add(std::string key, T value)
	{
		if (Search(key).first != "0")
			throw std::exception("this name already using");
		structure.insert(structure.end(), std::pair<std::string, T>(key, value));
		int log_count_plusplus = structure.size();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | ADD:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " polinom ";
		value.show();
		std::cout << " with name '" << key << "' added in unsorting table" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | COMPLEXITY:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " made " << log_count_plusplus << " transition in array(++)" << std::endl;
	}

	std::pair<std::string, T> Search(std::string current_key)
	{
		for (int i = 0; i < structure.size(); i++)
		{
			if (structure[i].first == current_key)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | SEARCH:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " polinom ";
				structure[i].second.show();
				std::cout << "with name " << structure[i].first << "found" << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | COMPLEXITY:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " made " << i << " transition in array(++)" << std::endl;
				return structure[i];
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | SEARCH:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " This key not in table" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | COMPLEXITY:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " made " << structure.size() << " transition in array(++)" << std::endl;
		return std::pair<std::string, T>("0", Polinoms("0"));
	}

	void Extract(std::string current_key)
	{
		int i = 0;
		bool flag_empty = true;
		for (auto it = structure.begin(); it != structure.end(); it++)
		{
			if (structure[i].first == current_key)
			{
				structure.erase(it);
				flag_empty = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | DELETE:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " row delete" << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | COMPLEXITY:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " made " << i << " transition in array(++)" << std::endl;
				break;
			}
			i++;
		}
		if (flag_empty)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			std::cout << "LOG | SEARCH:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			std::cout << " This key not in table";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			std::cout << "LOG | COMPLEXITY:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			std::cout << " made " << i << " transition in array(++)" << std::endl;
		}
	}
	/*-------------------------------------------------------------------------------------------------------*/

	void show()
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(22) << std::left << "| NAME" << "| POLINOM" << std::endl;
		for (int i = 0; i < structure.size(); i++)
		{
			show(structure[i]);
		}
	}

	void show(std::pair<std::string, T> t)
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << "| " << std::setw(20) << std::left << t.first << "| ";
		t.second.show();
		std::cout << "\n";
		std::cout << std::string(60, '-') << std::endl;
	}

	~non_sort_table() { }
};