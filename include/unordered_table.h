#pragma once

#include <iostream>
#include "pair.h"

template<class TData>
class UnorderedTable
{
private:
	Pair<TData>* tData;
	size_t tsize;    // Количество элементов на данный момент
	size_t max_size; // Количество выделенной памяти на данный момент

public:
	UnorderedTable() : tsize(0), max_size(10)
	{
		this->tData = new Pair<TData>[this->max_size];
	}

	~UnorderedTable()
	{
		delete[] this->tData;
		this->tData = nullptr;
		this->tsize = 0;
	}

	TData* search(const std::string& key) const
	{
		for (size_t i = 0; i < tsize; i++)
			if (tData[i].key == key)
				return tData[i].data;

		return nullptr;
	}

	void push(const Pair<TData>& var)
	{
		if (this->search(var.key) == nullptr)
		{
			if (this->tsize == this->max_size)
			{
				Pair<TData>* temp = new Pair<TData>[this->max_size];

				for (size_t i = 0; i < this->max_size; i++)
					temp[i] = this->tData[i];

				delete[] this->tData;
				this->tData = new Pair<TData>[this->max_size * 2];

				for (size_t i = 0; i < this->max_size; i++)
					this->tData[i] = temp[i];

				this->max_size *= 2;
				delete[] temp;
			}

			this->tData[this->tsize++] = var;
		}
	}

	void deleteRow(const std::string& key)
	{
		for (size_t i = 0; i < this->tsize; i++)
		{
			if (this->tData[i].key == key)
			{
				this->tData[i] = this->tData[--this->tsize];
				return;
			}
		}
	}

	void getTable()
	{
		for (size_t i = 0; i < this->tsize; i++)
			std::cout << this->tData[i] << std::endl;
	}
};