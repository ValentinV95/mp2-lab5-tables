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
	Entry* table;
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
		else table = new Entry[capacity];
	}

	size_t get_length() const noexcept
	{
		return length;
	}
	size_t get_operations_number() const noexcept
	{
		return operations_count;
	}

	/// Return entry's data pointer
	T* find(const string& _key)
	{
		operations_count = 0;
		for (size_t index = 0; index < length; index++)
		{
			operations_count++;
			if (table[index].key == _key)
			{
				return &table[index].data;
			}
		}
		return nullptr;
	}
	void insert(const string& _key, const T& _data)
	{
		if (length == capacity)
		{
			throw std::exception("table is full");
		}
		if (find(_key)) // checking for a duplicate
		{
			throw std::exception("key duplicate insert failure");
		}
		table[length++] = Entry{ _key, _data };
	}
	void remove(const string& _key)
	{
		operations_count = 0;
		for (size_t index = 0; index < length; index++)
		{
			operations_count++;
			if (table[index].key == _key)
			{
				table[index] = table[length - 1];
				length--;
				return;
			}
		}
		throw std::exception("key was not found");
	}

	~UnorderedTable()
	{
		delete[] table;
	}
};
