// double hashing
#pragma once
#include <vector>
#include <iostream>
#include "../polinom/include/polinom.h"
#include <Windows.h>
#define GREEN 10
#define WHITE 7

template <typename T>
class HashTable {
private:
	std::vector<std::pair<std::string, T>> structure;
	size_t size;
public:
	HashTable()
	{
		this->size = 8;
		this->structure.resize(size);
	}

	HashTable(const size_t user_size) // size table > user_size && size table = 2^n
	{
		if (user_size < 0)
			throw std::exception("ERROR: negative length");
		int tmp = log2(user_size);
		this->size = pow(2, tmp + 1);
		this->structure.resize(size);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | CONSTRUCT:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " Hash table construct" << std::endl;
	}

	int HashFunction1(std::string key)
	{
		int id = int(key[0] + key[1]);

		return id % size;
	}

	int HashFunction2(std::string key)
	{
		int id = int(key[0] + key[1]);
		int i = id % size;

		return i + ((i % 2) - 1);
	}

	int doubleHashFunction(std::string key, int i)
	{
		return (HashFunction1(key) + i * HashFunction2(key)) % size;
	}

	void insert(std::string key, T data, int& log_count)
	{
		for (int i = 0; i < size; i++)
		{
			if (std::get<std::string>(structure[doubleHashFunction(key, i)]) == "\0")
			{
				structure[doubleHashFunction(key, i)] = std::make_pair(key, data);
				log_count = i;
				break;
			}
		}
	}

	/*----------------------------------взаимодействия-с-таблицей--------------------------------------------*/
	void Add(std::string key, T value)
	{
		if (std::get<std::string>(Search(key)) != "0")
			throw std::exception("this name already using");
		int log_collision = 0;
		insert(key, value, log_collision);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | ADD:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " polinom ";
		value.show();
		std::cout << " with name '" << key << "' added in hash table" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | COMPLEXITY:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " made " << log_collision << " collision" << std::endl;
	}

	std::pair<std::string, T> Search(std::string current_key)
	{
		int log_collision = 0;
		for (int i = 0; i < size; i++)
		{
			if (std::get<std::string>(structure[doubleHashFunction(current_key, i)]) == current_key)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | SEARCH:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " polinom ";
				std::get<T>(structure[i]).show();
				std::cout << "with name " << std::get<std::string>(structure[i]) << "found" << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | COMPLEXITY:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " made " << i << " collision" << std::endl;
				return structure[doubleHashFunction(current_key, i)];
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | SEARCH:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " This key not in table" << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
		std::cout << "LOG | SEARCH:";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		std::cout << " made " << structure.size() << " transition in array(++)" << std::endl;
		return std::pair<std::string, T>("0", Polinoms("0"));
	}

	void Extract(std::string current_key)
	{
		int i = 0;
		bool flag_empty = true;
		for (int i = 0; i < size; i++)
		{
			if (std::get<std::string>(structure[doubleHashFunction(current_key, i)]) == current_key)
			{
				structure[doubleHashFunction(current_key, i)] = std::make_pair("\0", T("0"));
				flag_empty = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | DELETE:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " row delete" << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
				std::cout << "LOG | COMPLEXITY:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
				std::cout << " made " << i << " collision" << std::endl;
			}
		}
		if (flag_empty)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			std::cout << "LOG | SEARCH:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			std::cout << "This key not in table" << std::endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GREEN);
			std::cout << "LOG | COMPLEXITY:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			std::cout << " made " << i << " collision" << std::endl;
		}
	}
	/*-------------------------------------------------------------------------------------------------------*/

	void show()
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(22) << std::left << "| NAME" << "| POLINOM" << std::endl;
		for (int i = 0; i < structure.size(); i++)
		{
			if (std::get<std::string>(structure[i]) != "\0")
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

	~HashTable() {}
};