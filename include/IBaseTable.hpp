#pragma once

template <typename KeyType,typename DataType>
class KeyValuePair
{
	KeyType key;
	DataType data;
public:
	KeyValuePair(){}
	KeyValuePair(KeyType key,DataType data):key(key),data(data) {}
	KeyValuePair(const KeyValuePair& keyValuePair) = default;

	//Временная штука удалить потом
	void change(KeyType key, DataType data) { this->key = key; this->data = data; }
	DataType getData() { return data; }

	bool operator == (const KeyValuePair& keyValuePair) { return key == keyValuePair.key;}
	bool operator > (const KeyValuePair& keyValuePair) { return key > keyValuePair.key;}
	bool operator < (const KeyValuePair& keyValuePair) { return key < keyValuePair.key;}
	bool operator != (const KeyValuePair& keyValuePair) { return key != keyValuePair.key; }
};

template <typename KeyType, typename DataType>
class IBaseTTable
{
public:
	//Найти
	virtual DataType find(const KeyType &key) = 0;

	//Добавить
	virtual void insert(KeyType key, DataType data) = 0;

	//Удалить
	virtual void remove(const KeyType& key) = 0;

	virtual bool isEmpty() const = 0;
};