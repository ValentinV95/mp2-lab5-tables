#pragma once
#include <utility>
#include <vector>
#include <iomanip>
#include "Logger.hpp"

template<typename KeyType, typename DataType>
class TTable
{
	std::vector<std::pair<KeyType, DataType>> table;
	unsigned int compareCount = 1;
public:
	//Найти
	DataType find(const KeyType& key)
	{
		for (auto iter = table.begin(); iter != table.end(); iter++)
		{
			compareCount++;
			if ((*iter).first == key)
			{
				Logger::log(CONTEXT(), "Table : The number of comparisons in the search - " + to_string(compareCount), Info);
				compareCount = 1;
				return DataType((*iter).second);
			}
		}

		throw std::invalid_argument("Key was not found");
	}

	//Добавить
	void insert(KeyType key, DataType data)
	{
		for (size_t i = 0; i < table.size(); i++)
			if (table[i].first == key)
				throw std::invalid_argument("Such key olready exists in table");

		table.push_back(std::make_pair(key, data));
		Logger::log(CONTEXT(), "Table : The number of operations in the insert - 1", Info);
	}

	//Удалить
	void remove(const KeyType& key)
	{
		bool isRemoved = false;
		for (int i = 0; i < table.size() && !isRemoved; i++)
		{
			compareCount++;
			if (table[i].first == key)
			{
				table[i].first = table[table.size() - 1].first;
				table[i].second = table[table.size() - 1].second;

				table.resize(table.size() - 1);
			}
		}

		Logger::log(CONTEXT(), "Table : The number of comparisons in the remove - " + to_string(compareCount), Info);
		compareCount = 1;
	}

	bool isEmpty() const { return table.size(); }

	void show() const noexcept
	{
		cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
		cout << "|" << std::setw(5) << "Ind" << std::setw(5) << "| " << std::setw(12) << "KEY" << std::setw(12) << "| " << setw(34) << "VALUE" << setw(34) << "|" << endl;
		cout << "|-----------------------------------------------------------------------------------------------------|" << endl;

		for (int i = 0; i < table.size(); i++)
		{
			cout << std::left << "|" << std::setw(8) << to_string(i) << "| " << std::setw(22) << table[i].first << "| " << setw(67) << table[i].second << std::right << "|" << endl;
			cout << "|-----------------------------------------------------------------------------------------------------|" << endl;
		}
	}
};