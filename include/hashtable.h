#pragma once
#include <stdexcept>
#include <cmath>

using std::string;

namespace hash_constants
{
	const double GOLDEN_RATIO = (sqrt(5) - 1) / 2;
}

template <class T>
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
	Entry* table;
	size_t capacity;
	size_t length;
	size_t operations_count;

	int hash(const string& _key)
	{
		int sum = 0;
		for (char character : _key)
		{
			sum += character;
		}
		return static_cast<int>(capacity * fmod(sum * hash_constants::GOLDEN_RATIO, 1.0));
	}
	void probe(int& hash_index)
	{
		operations_count++;
		hash_index = (hash_index + mutually_prime) % static_cast<int>(capacity);
	}

	Entry* find_entry(const string& _key)
	{
		int num = -1;
		int index = hash(_key);
		const int first_index = index;
		do
		{
			if (table[index].state == Status::occupied)
			{
				if (table[index].key == _key)
				{
					return &table[index];
				}
			}
			else if (table[index].state == Status::free)
			{
				return nullptr;
			}
			probe(index);
		} while (index != first_index);
		return nullptr;
	}

	int mutually_prime;
	int get_mutually_prime(const int& _number)
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
			if (number == 1)
			{
				return mutually_prime_number;
			}
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
			throw std::exception("Размер таблицы должен быть больше нуля");
		}
		else
		{
			table = new Entry[capacity];
			for (size_t i = 0; i < capacity; i++)
			{
				table[i] = Entry{ Status::free };
			}
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

	/// Возвращаем указатель значения записи
	T* find(const string& _key)
	{
		operations_count = 0;
		Entry* entry = find_entry(_key);

		if (entry == nullptr) return nullptr;

		return &(*entry).value;
	}
	void insert(const string& _key, const T& _value)
	{
		operations_count = 0;
		if (length == capacity) throw std::exception("таблица заполнена");;
		int num = -1;
		int index = hash(_key);
		const int first_index = index;
		do
		{
			switch (table[index].state)
			{
			case Status::occupied:
			{
				if (table[index].key == _key) // checking for a duplicate
				{
					throw std::exception("сбой вставки дубликата");
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
					table[index] = Entry{ Status::occupied, _key, _value };
				}
				else table[num] = Entry{ Status::occupied, _key, _value };
				length++;
				return;
			}
			}
			probe(index);
		} while (index != first_index);
		table[num] = Entry{ Status::occupied, _key, _value };
		length++;
	}
	void remove(const string& _key)
	{
		operations_count = 0;
		Entry* entry = find_entry(_key);
		if (entry != nullptr)
		{
			(*entry).state = Status::deleted;
			length--;
		}
		else
		{
			throw std::exception("ключ не найден");
		}
	}

	~HashTable()
	{
		delete[] table;
	}
};