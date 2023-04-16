#pragma once

#include <iostream>
#include "tree.h"
#include "pair.h"

template<class TData>
class OrderedTable
{
private:
	Tree<Pair<TData>> tData;
	size_t size;
public:
	OrderedTable()
	{}

	~OrderedTable()
	{}

	TData* search(const std::string& key) const
	{
		return tData.search(Pair<TData>(key, TData()))->data.data;
	}

	void push(const Pair<TData>& var)
	{
		tData.push(var);
	}

	void deleteRow(const std::string& key)
	{
		tData.deleteNode(Pair<TData>(key, TData()));
	}

	void getTable()
	{
		tData.show();
	}
};