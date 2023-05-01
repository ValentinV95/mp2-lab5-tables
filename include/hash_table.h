#include <stdexcept>
#include <cmath>

using std::string;

namespace hash_constants
{
	const double GOLDEN_RATIO = (sqrt(5) - 1) / 2;
}

template<class T>
class HashTable
{
private:
	enum class Status { free, occupied, deleted };
	struct Entry
	{
		Status state;
		string key;
		T value;
	};
	Entry** table;
	Entry* nil;
	size_t capacity;
	size_t length;

	size_t operations_count;
	
	int hash(string _key)
	{
		int sum = 0;
		for (char character : _key)
		{
			sum += character;
		}
		return static_cast<int>(capacity * fmod(sum * hash_constants::GOLDEN_RATIO, 1.0));
	}
	int probe(int hash_index)
	{
		operations_count++;
		return (hash_index + mutually_prime) % capacity;
	}

	Entry* find_entry(string _key)
	{
		int num = -1;
		int index = hash(_key);
		const int first_index = index;
		do
		{
			if (table[index]->state == Status::occupied)
			{
				if (table[index]->key == _key)
				{
					return table[index];
				}
			}
			else if (table[index]->state == Status::free)
			{
				return nullptr;
			}
			index = probe(index);
		} 
		while (index != first_index);
		return nullptr;
	}

	int mutually_prime;
	int get_mutually_prime(int _number)
	{
		int number = _number;
		int mutually_prime_number = number / 4 + 1;
		int remainder = 1;
		int divisor = mutually_prime_number;
		while (mutually_prime_number > 1)
		{
			while (remainder != 0)
			{
				remainder = number % divisor;
				number = divisor;
				divisor = remainder;
			}
			if (number == 1) return mutually_prime_number;
			divisor = --mutually_prime_number;
			number = _number;
			remainder++;
		}
		return 1;
	}
public:
	HashTable(size_t size) : capacity(size), length(0), mutually_prime(1), operations_count(0)
	{
		if (size <= 0)
		{
			throw std::exception("Table size should be greater than zero");
		}
		else
		{
			nil = new Entry{ Status::free };
			table = new Entry*[capacity];
			for (size_t i = 0; i < capacity; i++) 
				table[i] = nil;

			mutually_prime = get_mutually_prime(capacity);
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
	
	/// Return entry's value pointer
	T* find(string _key)
	{
		operations_count = 0;
		Entry* entry = find_entry(_key);

		if (entry == nullptr) return nullptr;

		return &entry->value;
	}
	void insert(string _key, T _value) 
	{
		operations_count = 0;
		if (length == capacity) throw std::exception("table is full");;
		int num = -1;
		int index = hash(_key);
		const int first_index = index;
		do
		{
			switch (table[index]->state)
			{
			case Status::occupied:
			{
				if (table[index]->key == _key) // checking for a duplicate
				{
					throw std::exception("key duplicate insert failure");
				}
				break;
			}
			case Status::deleted:
			{
				if (num == -1)
				{
					num = index;
				}
				break;
			}
			case Status::free:
			{
				if (num == -1)
				{
					table[index] = new Entry{ Status::occupied, _key, _value };
				}
				else
				{
					table[num]->state = Status::occupied;
					table[num]->key = _key;
					table[num]->value = _value;
				}
				length++;
				return;
			}
			}
			index = probe(index);
		} 
		while (index != first_index);
		table[num]->state = Status::occupied;
		table[num]->key = _key;
		table[num]->value = _value;
		length++;
	}
	void remove(string _key) 
	{
		operations_count = 0;
		Entry* entry = find_entry(_key);
		if (entry != nullptr)
		{
			entry->state = Status::deleted;
			length--;
		}
		else
		{
			throw std::exception("key was not found");
		}
	}

	~HashTable()
	{
		for (size_t index = 0; index < capacity; index++)
		{

			if (table[index] != nil)
			{
				delete table[index];
			}
		}
		delete nil;
		delete[] table;
	}
};
