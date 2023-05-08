#pragma once
#include <exception>
#include <vector>
#include <iomanip>
#include <string>
#include <string.h>
#include "Logger.hpp"

using namespace std;
template<class KeyType, typename DataType>
class THashTable
{
	enum CellState { free, full, deleted };
	struct Cell
	{
		KeyType key;
		DataType data;
		CellState state;

		Cell() :state(free) {};
		Cell(KeyType key, DataType data) :key(key), data(data), state(full) {};
	};

	//От ключа берется остаток от деления на m1 и m2 гарантировать полный обход таблицы
	size_t m1;//Это число выбирается как ближайшее простое число большее size
	size_t m2;//Немного меньше m1 (на единицу)

	size_t size, freeCellCount;
	std::vector<Cell> table;

	template<class KeyType>
	size_t h2(const KeyType& key) { return 0; };

	template<class KeyType>
	size_t h1(const KeyType& key) { return 0; };

	template<class KeyType>
	size_t h(const KeyType& key, size_t i) { return 0; };

	template<>
	size_t h2<string>(const string& key)
	{
		size_t sum = 0, tmp = 0;

		for (int i = 0; i < key.size(); i++)
		{
			tmp = ((i + 1) * (size_t)key[i]) % m2;
			sum = (sum + tmp) % m2;
		}

		return 1 + sum;
	}

	template<>
	size_t h1<string>(const string& key)
	{
		size_t sum = 0, tmp = 0;

		for (int i = 0; i < key.size(); i++)
		{
			tmp = ((i + 1) * (size_t)key[i]) % m1;
			sum = (sum + tmp) % m1;
		}

		return sum;
	}

	template<>
	size_t h<string>(const string& key, size_t i)
	{
		return (h1(key) + i * h2(key)) % m1;
	}

	size_t nearestSimpleNumber(size_t start)
	{
		bool isEven = true;

		for (int i = 2; i * i <= start; i++)
			if (start % i == 0)
				isEven = false;

		while (!isEven)
		{
			start++;
			isEven = true;
			for (int i = 2; i * i <= start; i++)
				if (start % i == 0)
					isEven = false;
		}

		return start;
	}
public:
	THashTable(size_t size)
	{
		this->size = size;
		m1 = nearestSimpleNumber(size);
		m2 = m1 - 1;

		table.resize(m1);
		freeCellCount = m1;
	}

	//Найти
	DataType find(const KeyType& key)
	{
		size_t i = 0;
		while (table[h(key, i)].state == full && table[h(key, i)].key != key && table[h(key, i)].state != free)
			i++;
		
		if (table[h(key, i)].state == full)
		{
			Logger::log(CONTEXT(), "HashTable : The number of tests in the search - " + to_string(i+1), Info);
			return table[h(key, i)].data;
		}
		else
		{
			throw std::invalid_argument("Key was not found");
		}
	}

	//Добавить
	void insert(KeyType key, DataType data)
	{
		if (freeCellCount == 0)
			throw std::exception("There is no free cell for a new element, table is full");

		size_t i = 0;
		while (table[h(key, i)].state != free && table[h(key, i)].state != deleted)
		{
			if (table[h(key, i)].key == key)
				throw std::invalid_argument("Such key olready exists in table");

			i++;
		}

		Logger::log(CONTEXT(), "HashTable : The number of tests in the insert - " + to_string(i+1), Info);

		table[h(key, i)] = Cell(key, data);
		freeCellCount--;
	}

	//Удалить
	void remove(const KeyType& key)
	{
		size_t i = 0;
		while (table[h(key, i)].state == full && table[h(key, i)].key != key && table[h(key, i)].state != free)
			i++;

		Logger::log(CONTEXT(), "HashTable : The number of tests in the remove - " + to_string(i+1), Info);

		if (table[h(key, i)].state != free)
		{
			table[h(key, i)].state = deleted;
			freeCellCount++;
		}
	}

	bool isEmpty() const { return freeCellCount == size; }

	void show() const noexcept
	{
		cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << std::setw(5) <<"Ind" << std::setw(5) << "| " << std::setw(12) << "KEY" << std::setw(12) << "| " << setw(34) << "VALUE" << setw(34) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------|" << endl;

		for (int i = 0; i < table.size(); i++)
		{
			if (table[i].state == full)
			{
				cout << std::left << "|" << std::setw(8) << to_string(i) << "| " << std::setw(22) << table[i].key << "| " << setw(67) << table[i].data << std::right << "|" << endl;
				cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
			}
		}
	}
};
