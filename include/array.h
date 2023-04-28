#pragma once
#include <exception>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../polinom/include/polinom.h"

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
		std::cout << "LOG: Non sorting table construct" << std::endl;
	}

	std::pair<std::string, T> operator[](int i)
	{
		return this->structure[i];
	}
	/*----------------------------------взаимодействия-с-таблицей--------------------------------------------*/
	void Add(std::string key, T value)
	{
		if (std::get<std::string>(Search(key)) != "0")
			throw std::exception("this name already using");
		structure.insert(structure.end(), std::pair<std::string, T>(key, value));
		int log_count_plusplus = structure.size();
		std::cout << "LOG: polinom  ";
		value.show();
		std::cout << " with name '" << key << "' added in sort table" << std::endl;
		std::cout << "LOG: made " << log_count_plusplus << " transition in array(++)" << std::endl;
	}

	std::pair<std::string, T> Search(std::string current_key)
	{
		for (int i = 0; i < structure.size(); i++)
		{
			if (std::get<std::string>(structure[i]) == current_key)
			{
				std::cout << "LOG: polinom ";
				std::get<T>(structure[i]).show();
				std::cout << "with name " << std::get<std::string>(structure[i]) << "found" << std::endl;
				std::cout << "LOG: made " << i << " transition in array(++)" << std::endl;
				return structure[i];
			}
		}
		std::cout << "LOG: This key not in table" << std::endl;
		std::cout << "LOG: made " << structure.size() << " transition in array(++)" << std::endl;
		return std::pair<std::string, T>("0", Polinoms("0"));
	}

	void Extract(std::string current_key)
	{
		int i = 0;
		bool flag_empty = true;
		for (auto it = structure.begin(); it != structure.end(); it++)
		{
			if (std::get<std::string>(structure[i]) == current_key)
			{
				structure.erase(it);
				flag_empty = false;
				std::cout << "LOG: row delete\nLOG: made " << i << " transition in array(++)" << std::endl;
				break;
			}
			i++;
		}
		if (flag_empty)
		{
			std::cout << "This key not in table";
			std::cout << "LOG: made " << i << " transition in array(++)" << std::endl;
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
		std::cout << "| " << std::setw(20) << std::left << std::get<std::string>(t) << "| ";
		std::get<T>(t).show();
		std::cout << "\n";
		std::cout << std::string(60, '-') << std::endl;
	}

	~non_sort_table() { }
};