#pragma once

#include <iostream>

template<class TData>
struct Pair
{
	std::string key;
	TData* data;

	Pair() : key(""), data(new TData())
	{}

	Pair(const std::string& _key, const TData& var) : key(_key), data(new TData(var))
	{}

	~Pair()
	{
		this->data = nullptr;
		delete this->data;
		this->key = "";
	}

	bool operator >(const Pair<TData>& other) const
	{
		//if (this->key == other.key) return *this->data > *other.data;
		return this->key > other.key;
	}

	bool operator >=(const Pair<TData>& other) const
	{
		//if (this->key == other.key) return *this->data >= *other.data;
		return this->key >= other.key;
	}

	bool operator <(const Pair<TData>& other) const
	{
		//if (this->key == other.key) return *this->data < *other.data;
		return this->key < other.key;
	}

	bool operator <=(const Pair<TData>& other) const
	{
		//if (this->key == other.key) return *this->data <= *other.data;
		return this->key <= other.key;
	}

	bool operator ==(const Pair<TData>& other) const
	{
		return this->key == other.key;//&&* this->data == *other.data;
	}

	bool operator !=(const Pair<TData>& other) const
	{
		return !(*this == other);
	}

	void getPair() const
	{
		std::cout << key << " " << *data << std::endl;
	}

	friend std::ostream& operator <<(std::ostream& ostr, const Pair& other)
	{
		ostr << key << " " << *data;

		return ostr;
	}
};