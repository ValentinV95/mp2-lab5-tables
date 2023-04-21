#include <stdexcept>

using std::string;

template <class T>
class UnorderedTable
{
private:
	struct Entry
	{
		string key;
		T data;
	};
	Entry** table;
	size_t capacity;
	size_t length;

	size_t operations_count;
public:
	UnorderedTable(size_t size) : capacity(size), length(0), operations_count(0)
	{
		if (size <= 0)
		{
			throw std::exception("Table size should be greater than zero");
		}
		else
		{
			table = new Entry*[capacity];
			for (size_t i = 0; i < capacity; i++)
				table[i] = nullptr;
		}
	}

	size_t get_length() const noexcept
	{
		return length;
	}
	size_t get_operations_number() const noexcept
	{
		return operations_count;
	}

	T* find(string _key)
	{
		operations_count = 0;
		for (size_t i = 0; i < length; i++)
		{
			if (++operations_count && table[i]->key == _key)
			{
				return &table[i]->data;
			}
		}
		return nullptr;
	}
	void insert(string _key, T _data)
	{
		if (find(_key)) // checking for a dublicate
		{
			throw std::exception("key duplicate insert failure");
		}
		if (length == capacity)
		{
			throw std::exception("table is full");
		}
		table[length++] = new Entry{ _key, _data };
	}
	void remove(string _key)
	{
		operations_count = 0;
		for (int index = 0; index < length; index++)
		{
			if (++operations_count && table[index]->key == _key)
			{
				Entry* tmp = table[index];
				table[index] = table[length - 1];
				delete tmp;
				table[length - 1] = nullptr;
				length--;
				return;
			}
		}
		throw std::exception("key was not found");
	}

	~UnorderedTable()
	{
		for (size_t i = 0; i < capacity; i++)
		{
			if (table[i] != nullptr) delete table[i];
		}
		delete[] table;
	}
};
