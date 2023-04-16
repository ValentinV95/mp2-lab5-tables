#pragma once

#include <iostream>
#include "pair.h"
#include "list.hpp"

template <class TData>
class HashTable
{
private:
	int max_size;
	List<Pair<TData>>* tData;
public:
	HashTable() : max_size(20) 
	{
		tData = new List<Pair<TData>>[max_size]();
	}

	~HashTable()
	{
		delete[] tData;
		tData = nullptr;
		max_size = 0;
	}

	int hash(std::string key)
	{
		int result = 0;

		for (size_t i = 0; i < key.size(); i++)
		{
			result += static_cast<int>(key[i]);
		}

		return result % max_size;
	}

	void push(const Pair<TData>& var)
	{
		if (this->search(var.key) == nullptr)
		{
			tData[hash(var.key)].push(var);
		}
	}

	TData* search(const std::string& key)
	{
		Node<Pair<TData>>* cur = this->tData[hash(key)].begin();

		while (cur)
		{
			if (cur->data.key == key)
				return cur->data.data;

			cur = cur->next;
		}

		return nullptr;
	}

	void deleteRow(const std::string& key)
	{
		if (this->search(key))
		{
			int hash = hash(key);
			Node<Pair<TData>>* temp = this->tData[hash].begin();

			while (temp->data.key != key)
				temp = temp->next;

			this->tData[hash].deleteNode(temp);
		}
	}

	void getTable()
	{
		Node<Pair<TData>>* temp;

		for (size_t i = 0; i < this->max_size; i++)
		{
			temp = this->tData[i].begin();

			while (temp)
			{
				std::cout << temp->data << endl;
				temp = temp->next;
			}
		}
	}
};