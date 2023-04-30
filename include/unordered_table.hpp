#pragma once

#include <iostream>
#include "pair.hpp"
#include "logger.h"

static LogTable unorderedTable("if");

template<class TData>
class UnorderedTable
{
private:
	Pair<TData>* tData;                                    // Массив пар
	int max_size;                                          // Количество выделенной памяти
	int index;                                             // Индекс последнего

public:
	UnorderedTable();                                      // Конструктор по умолчанию
	~UnorderedTable();                                     // Деструктор
	TData* search(const std::string&) const;               // Поиск
	void push(const Pair<TData>&);                         // Вставка
	void deleteRow(const std::string&);                    // Удаление
	int size() const;                                      // Количество элементов в таблице в данный момент
	void getTable();                                       // Вывод таблицы

};

template<class TData>
UnorderedTable<TData>::UnorderedTable() : index(-1), max_size(200)
{
	this->tData = new Pair<TData>[this->max_size];
}

template<class TData>
UnorderedTable<TData>::~UnorderedTable()
{
	delete[] this->tData;
	this->tData = nullptr;
}

template<class TData>
TData* UnorderedTable<TData>::search(const std::string& key) const
{
	for (int i = 0; i <= index; i++, ++unorderedTable)
		if (tData[i].key == key)
		{
			unorderedTable.Logmsg("UnorderedTable::search()");
			return &tData[i].data;
		}

	unorderedTable.Logmsg("UnorderedTable::search()");
	return nullptr;
}

template<class TData>
void UnorderedTable<TData>::push(const Pair<TData>& var)
{
	if (this->search(var.key) == nullptr)
	{
		if ((index + 1) == max_size) throw std::out_of_range("Table is full");

		this->tData[++this->index] = var;
	}

	unorderedTable.Logmsg("UnorderedTable::push()");
}

template<class TData>
void UnorderedTable<TData>::deleteRow(const std::string& key)
{
	for (int i = 0; i <= this->index; i++, ++unorderedTable)
	{
		if (this->tData[i].key == key)
		{
			this->tData[i] = this->tData[this->index--];
			break;
		}
	}

	unorderedTable.Logmsg("UnorderedTable::deleteRow()");
}

template<class TData>
int UnorderedTable<TData>::size() const
{
	return this->index + 1;
}

template<class TData>
void UnorderedTable<TData>::getTable()
{
	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "_";

	std::cout << std::endl << "|Ключ";

	for (size_t i = 0; i < 20; i++)
		std::cout << " ";

	std::cout << "| Значение" << std::endl;

	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "_";

	std::cout << std::endl;

	for (int i = 0; i <= this->index; i++)
		this->tData[i].getPair();
}