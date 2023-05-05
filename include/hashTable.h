#pragma once
#include <string>
#include <exception>
#include <iostream>



template<class T1, class T2>
class hashTable
{
private:
	int size;
	struct elem
	{
		T1 key;
		T2 data;
		bool isEmpty;
		elem() { isEmpty = true; }
		elem(T1 key, T2 value) { this->key = key; data = value; isEmpty = false; }
	};
	elem* array = nullptr;

	struct Log
	{
		std::string name;
		int operation = 0;
		Log() { name = "no operations"; operation = 0; };
	} loger;


	template<class T1>
	int hashFunction(T1 key)
	{
		return key % size;
	}

	template<>
	int hashFunction<std::string>(std::string key)
	{
		int res = 0;
		for (int i = 0; i < key.length(); i++)
			res += key[i];
		return res % size;
	}


public:
	hashTable(int size = 5)
	{
		this->size = size;
		array = new elem[size];
	}
	~hashTable()
	{
		delete[] array;
	}

	void showTable()
	{
		for (int i = 0; i < size; i++)
		{
			if(!array[i].isEmpty)
				std::cout << array[i].key << " : " << array[i].data << '\n';
		}
	}

	void showKeys()
	{
		for (int i = 0; i < size; i++)
		{
			if (!array[i].isEmpty)
				std::cout << array[i].key << '\n';
		}
	}


	void addElement(T1 key, T2 value)
	{
		loger.name = "insert";
		loger.operation = 0;

		int hash = hashFunction(key);
		for (int i = 0; i < size; i++)
		{
			loger.operation++;
			int id = (hash + 2 * i + 5 * i * i) % size;
			loger.operation++;
			if (array[id].isEmpty)
			{
				array[id] = elem(key, value);
				return;
			}
		}
		throw std::exception("table is full!");
	}

	void delElement(T1 key)
	{
		loger.name = "delete";
		loger.operation = 0;

		int hash = hashFunction(key);
		for (int i = 0; i < size; i++)
		{
			loger.operation++;

			int id = (hash + 2 * i + 5 * i * i) % size;
			
			loger.operation++;
			if (array[id].isEmpty)
				throw std::exception("no such element!");
			else if (array[id].key == key)
			{
				array[id].isEmpty = true;
				return;
			}
			loger.operation++;
		}
		throw std::exception("no such element!");
	}

	T2& getElement(T1 key)
	{
		loger.name = "search";
		loger.operation = 0;

		int hash = hashFunction(key);
		for (int i = 0; i < size; i++)
		{
			loger.operation++;

			int id = (hash + 2 * i + 5 * i * i) % size;
			
			loger.operation++;
			if (!array[id].isEmpty && array[id].key == key)
				return array[id].data;
		}
		throw std::exception("no such element!");
	}

	void getLog()
	{
		std::cout << loger.name << " : " << loger.operation << "\n";
	}
};