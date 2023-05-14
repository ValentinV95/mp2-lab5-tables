#include <iostream>

using namespace std;

template <typename T>
struct NodeH
{
	int key;
	T data;
	NodeH(int k, T d)
	{
		data = d;
		key = k;
	}
	NodeH() {}
};

template <typename T>
class Hash
{
public:
	Hash(size_t size = 50)
	{
		Msize = size;
		this->size = 0;
		table = new NodeH<T>*[size];
		for (size_t i = 0; i < size; i++)
		{
			table[i] = nullptr;
		}
	}
	void add(int key, T data)
	{
		if (size == Msize)
		{
			throw exception("Low memory");
		}
		NodeH<T>* t = new NodeH<T>(key, data);
		if (table[key % Msize] == nullptr)
		{
			table[key % Msize] = t;
			size++;
			cout << "Hash add " << 1 << endl;
		}
		else
		{
			size_t ct = 0;
			int hs = key % Msize;
			while (true)
			{
				ct++;
				hs = (hs + (key / 2) % Msize + 1) % Msize;
				if (table[hs] == nullptr)
				{
					table[hs] = t;
					size++;
					cout << "Hash add " << ct << endl;
					return;
				}
			}
		}
	}
	T& find(int key)
	{
		size_t ct = 0;
		int hs = key % Msize;
		while (ct < Msize)
		{
			ct++;
			if ((table[hs] != nullptr) && (table[hs]->key == key))
			{
				break;
			}
			hs = (hs + (key / 2) % Msize + 1) % Msize;
		}
		if (ct == Msize)
		{
			throw exception("Cant find key");
		}
		cout << "Hash find " << ct << endl;
		return table[hs]->data;
	}
	void del(int key)
	{
		size_t ct = 0;
		if (size == 0)
		{
			throw exception("Nothing to delete");
		}
		int hs = key % Msize;
		while (ct < Msize)
		{
			ct++;
			if ((table[hs] != nullptr) && (table[hs]->key == key))
			{
				table[hs] = nullptr;
				size--;
				cout << "Hash delete " << ct << endl;
				return;
			}
			hs = (hs + (key / 2) % Msize + 1) % Msize;
		}
		throw exception("Nothing to delete");
	}
	size_t get_size()
	{
		return size;
	}
private:
	NodeH<T>** table;
	size_t Msize, size;
};