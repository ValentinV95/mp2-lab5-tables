#pragma once

#include <iostream>

template<class TData>
struct Pair
{
	std::string key;
	TData data;

	Pair();                                                                    // Конструктор по умолчанию 
	Pair(const std::string&, const TData&);                                    // Конструктор инициализации
	bool operator >(const Pair<TData>&) const;                                 // Оператор больше
	bool operator <(const Pair<TData>&) const;                                 // Оператор меньше
	bool operator >=(const Pair<TData>&) const;                                // Оператор больше или равно
	bool operator <=(const Pair<TData>&) const;                                // Оператор меньше или равно
	bool operator ==(const Pair<TData>&) const;                                // Оператор равно
	bool operator !=(const Pair<TData>&) const;                                // Оператор неравно 
	void getPair();                                                            // Вывести пару в консоль 
};

template<class TData>
Pair<TData>::Pair() : key(""), data(TData())
{}

template<class TData>
Pair<TData>::Pair(const std::string& _key, const TData& var) : key(_key), data(var)
{}

template<class TData>
bool Pair<TData>::operator >(const Pair<TData>& other) const
{ return this->key > other.key; }

template<class TData>
bool Pair<TData>::operator >=(const Pair<TData>& other) const
{ return this->key >= other.key; }

template<class TData>
bool Pair<TData>::operator <(const Pair<TData>& other) const
{ return this->key < other.key; }

template<class TData>
bool Pair<TData>::operator <=(const Pair<TData>& other) const
{ return this->key <= other.key; }

template<class TData>
bool Pair<TData>::operator ==(const Pair<TData>& other) const
{ return this->key == other.key; }

template<class TData>
bool Pair<TData>::operator !=(const Pair<TData>& other) const
{ return *this != other; }