#pragma once

#include <iostream>
#include "tree.hpp"
#include "pair.hpp"

template<class TData>
class OrderedTable
{
private:
	Tree<Pair<TData>> tData;                               // Красно-черное дерево пар

public:
	OrderedTable();                                        // Конструктор по умолчанию
	TData* search(const std::string&) const;               // Поиск
	void push(const Pair<TData>&);                         // Вставка
	void deleteRow(const std::string&);                    // Удаление
	int size() const;                                      // Количество элементов в данный момент
	void getTable();                                       // Вывод таблицы

};

template<class TData>
OrderedTable<TData>::OrderedTable()
{}

template<class TData>
TData* OrderedTable<TData>::search(const std::string& key) const
{
	return &tData.search(Pair<TData>(key, TData()))->data.data;
}

template<class TData>
void OrderedTable<TData>::push(const Pair<TData>& var)
{
	tData.push(var);
}

template<class TData>
void OrderedTable<TData>::deleteRow(const std::string& key)
{
	tData.deleteNode(tData.search(Pair<TData>(key, TData())));
}

template<class TData>
int OrderedTable<TData>::size() const
{
	return this->tData.size();
}

template<class TData>
void OrderedTable<TData>::getTable()
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
	tData.getTree();
}