#include <iostream>

using namespace std;

template <typename T>
struct NodeU
{
	int key;
	T data;
	NodeU(int k, T d)
	{
		data = d;
		key = k;
	}
	NodeU() {}
};

template <typename T>
class Unordered
{
public:
	Unordered(size_t size = 50)
	{
		Msize = size;
		this->size = 0;
		table = new NodeU<T>*[size];
		for (size_t i = 0; i < size; i++)
		{
			table[i] = nullptr;
		}
	}
	void add(int key, T data)
	{
		if (size > Msize)
		{
			throw exception("Low memory");
		}
		table[size] = new NodeU<T>(key, data);
		size++;
		cout << "Unordered add " << 1 << endl;
	}
	void del(int key)
	{
		size_t ct = 1;
		if (size == 0)
		{
			throw exception("Nothing to delete");
		}
		size_t t;
		for (size_t i = 0; i < size; i++)
		{
			if (table[i]->key == key)
			{
				t = i;
			}
			ct++;
		}
		ct++;
		table[t] = table[size - 1];
		table[size - 1] = nullptr;
		size--;
		cout << "Unordered delete " << ct << endl;
	}
	T& find(int key)
	{
		size_t ct = 1;
		for (size_t i = 0; i < size; i++)
		{
			ct++;
			if (table[i]->key == key)
			{
				cout << "Unordered find " << ct << endl;
				return table[i]->data;
			}
		}
		throw exception("Cant find key");
	}
private:
	NodeU<T>** table;
	size_t Msize, size;
};