#pragma once

#include <iostream>
#include "pair.hpp"
#include "list.hpp"
#include "logger.h"

static LogTable hashTable("hash");

template <class TData>
class HashTable
{
private:
	List<Pair<TData>>* tData;                              // Массив списков пар
	int max_size;                                          // Количество выделенной памяти                
	int tsize;                                             // Количество элементов в данный момент                       

public:
	HashTable();                                           // Конструктор по умолчанию                  
	~HashTable();                                          // Деструктор                    
	int hash(const std::string&);                          // Хэш-функция(остаток от деления)                                                        
	TData* search(const std::string&);                     // Поиск
	void push(const Pair<TData>&);                         // Вставка
	void deleteRow(const std::string&);                    // Удаление                    
	int size() const;                                      // Количество элементов в таблице в данный момент                    
	void getTable();                                       // Вывод таблицы

};

template <class TData>
HashTable<TData>::HashTable() : max_size(200), tsize(0)
{
	tData = new List<Pair<TData>>[max_size]();
}

template <class TData>
HashTable<TData>::~HashTable()
{
	delete[] tData;
	tData = nullptr;
}

template <class TData>
int HashTable<TData>::hash(const std::string& key)
{
	++hashTable;

	int result = 0;

	for (int i = 0; i < key.size(); i++)
	{
		result += static_cast<int>(key[i]);
	}

	return result % max_size;
}

template <class TData>
TData* HashTable<TData>::search(const std::string& key)
{
	Node<Pair<TData>>* cur = this->tData[hash(key)].begin();
	hashTable.Logmsg("HashTable::search()");

	while (cur)
	{
		if (cur->data.key == key)
			return &cur->data.data;

		cur = cur->next;
	}

	return nullptr;
}

template <class TData>
void HashTable<TData>::push(const Pair<TData>& var)
{
	if (this->search(var.key) == nullptr)
	{
		if (tsize == max_size) throw std::out_of_range("Table is full");

		tsize++;
		tData[hash(var.key)].push(var);
	}

	hashTable.Logmsg("HashTable::push()");
}

template <class TData>
void HashTable<TData>::deleteRow(const std::string& key)
{
	if (this->search(key))
	{
		int thash = hash(key);
		Node<Pair<TData>>* temp = this->tData[thash].begin();

		while (temp->data.key != key)
			temp = temp->next;

		this->tData[thash].deleteNode(temp);
		tsize--;
	}

	hashTable.Logmsg("HashTable::deleteRow()");
}

template <class TData>
int HashTable<TData>::size() const
{
	return tsize;
}

template <class TData>
void HashTable<TData>::getTable()
{
	Node<Pair<TData>>* temp;

	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "_";

	std::cout << endl << "|Ключ";

	for (size_t i = 0; i < 20; i++)
		std::cout << " ";

	std::cout << "| Значение" << std::endl;

	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "-";

	std::cout << std::endl;

	for (int i = 0; i < this->max_size; i++)
	{
		temp = this->tData[i].begin();

		while (temp)
		{
			temp->data.getPair();
			temp = temp->next;
		}
	}
}