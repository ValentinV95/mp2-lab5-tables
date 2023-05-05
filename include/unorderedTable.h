#pragma once
#include <iostream>

template<class T1, class T2>
class unorderedTable
{
private:
	struct pair
	{
		T1 key;
		T2 data;
		pair(T1 key, T2 data)
		{
			this->key = key;
			this->data = data;
		}
		pair(){}
	};

	struct Log
	{
		std::string name;
		int operation = 0;
		Log() { name = "no operations"; operation = 0; };
	} loger;


	int realSize;
	int size;
	pair* array = nullptr;
public:
	unorderedTable(int size = 5) 
	{
		realSize = size;
		this->size = 0;
		array = new pair[realSize];
	}

	~unorderedTable()
	{
		delete[] array;
	}

	void addElement(T1 key, T2 value)
	{
		loger.name = "insert";
		loger.operation = 0;

		loger.operation++;
		if (size == realSize)
		{
			loger.operation++;

			pair* tmp = new pair[realSize * 2];
			for (int i = 0; i < realSize; i++)
			{
				loger.operation += 2;
				tmp[i] = array[i];
				if(array[i].key == key)
					throw std::exception("key bussy!");
			}
			delete[] array;
			array = tmp;
			realSize *= 2;
		}
		for (int i = 0; i < size; i++)
		{
			loger.operation += 2;
			if (array[i].key == key)
				throw std::exception("key bussy!");
		}
		array[size++] = pair(key, value);
	}

	T2& getElement(T1 key)
	{
		loger.name = "search";
		loger.operation = 0;

		for (int i = 0; i < size; i++)
		{
			loger.operation += 2;
			if (array[i].key == key)
				return array[i].data;
		}
		throw std::exception("No such elem");
	}

	void deleteElement(T1 key)
	{
		loger.name = "delete";
		loger.operation = 0;

		int i = 0;
		for (; i < size; i++)
		{
			loger.operation += 2;
			if (array[i].key == key)
				break;
		}

		loger.operation++;
		if (i >= size)
			throw std::exception("No such elem");
		for (; i < size-1; i++)
		{
			loger.operation++;
			array[i] = array[i + 1];
		}
		size--;
	}

	void showTable()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << array[i].key << " : " << array[i].data << '\n';
		}
	}

	void showKeys()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << array[i].key << "\n";
		}
	}


	void getLog()
	{
		std::cout << loger.name << " : " << loger.operation << "\n";
	}
};
