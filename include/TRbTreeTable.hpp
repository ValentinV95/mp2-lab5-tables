#pragma once
#include <iostream>
#include "TRbTree.hpp"
#include <string.h>

template <typename KeyType, typename DataType>
class TRbTreeTable
{
	template <typename KeyType, typename DataType>
	class KeyValuePair
	{
		KeyType key;
		DataType data;
	public:
		KeyValuePair() {}
		KeyValuePair(KeyType key, DataType data) :key(key), data(data) {}
		KeyValuePair(const KeyValuePair& keyValuePair) = default;

		KeyType getKey() const { return key; }
		DataType getData() const { return data; }

		bool operator == (const KeyValuePair& keyValuePair) { return key == keyValuePair.key; }
		bool operator > (const KeyValuePair& keyValuePair) { return key > keyValuePair.key; }
		bool operator < (const KeyValuePair& keyValuePair) { return key < keyValuePair.key; }
		bool operator != (const KeyValuePair& keyValuePair) { return key != keyValuePair.key; }
	};

	TRbTree<KeyValuePair<KeyType, DataType>> data;
public:
	//Найти
	DataType find(const KeyType& key)
	{
		KeyValuePair<KeyType, DataType> tmp = data.find(KeyValuePair<KeyType, DataType>(key, DataType()));
		return tmp.getData();
	}

	//Добавить
	void insert(KeyType key, DataType data) { this->data.insert(KeyValuePair<KeyType, DataType>(key, data)); }

	//Удалить
	void remove(const KeyType& key) { data.remove(KeyValuePair<KeyType, DataType>(key, DataType())); }

	bool isEmpty() const { return data.isEmpty(); }

	void show()
	{
		vector<KeyValuePair<KeyType, DataType>> dataVec = data.vectorize();

		for (int i=0;i<dataVec.size();i++)
		{
			cout << "Key: " << dataVec[i].getKey() << " Value: " << dataVec[i].getData() <<endl;
		}
	}
};