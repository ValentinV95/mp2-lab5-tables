#pragma once

#include <string>
#include <vector>

using namespace std;

template <class TValue>
class TUnorderedTable
{
private:
	struct TTableRec
	{
		TValue value;
		string key;
		TTableRec() : value(TValue()), key("") {}
		TTableRec(string _key, TValue _value) : value(_value), key(_key) {}
		const bool operator > (const TTableRec& other) const { return key > other.key; }
		const bool operator < (const TTableRec& other) const { return key < other.key; }
		const bool operator == (const TTableRec& other) const { return key == other.key; }
		const bool operator != (const TTableRec& other) const { return key != other.key; }
		friend ostream& operator<<(ostream& ostr, TTableRec& row)
		{
			ostr << row.key << ": " << row.value;
			return ostr;
		}
	};
	struct Logger
	{
		int comp;
		string log;
	};

	vector<TTableRec> table;
	Logger logger;
public:
	size_t size() { return table.size(); }
	TValue& Search(string key)
	{
		logger.log = string("Operation Search: ");
		logger.comp = 0;
		for (int i = 0; i < table.size(); i++)
		{
			logger.comp++;
			if (table[i].key == key)
			{
				return table[i].value;
			}
		}
		throw exception("This element was not found!");
	}
	void Insert(string key, TValue value)
	{
		logger.log = string("Operation Insert: ");
		logger.comp = 0;
		TTableRec row(key, value);
		for (int i = 0; i < table.size(); i++)
		{
			logger.comp++;
			if (table[i].key == key)
				throw exception("Element with this key is already exists");
		}
		table.push_back(row);
	}
	void Delete(string key)
	{
		logger.log = string("Operation Delete: ");
		logger.comp = 0;
		for (int i = 0; i < table.size(); i++)
		{
			logger.comp++;
			if (table[i].key == key)
			{
				table.erase(table.begin() + i);
				return;
			}
		}
	}
	string logging()
	{
		return logger.log + string("Cost: ") + to_string(logger.comp) + string(" comparisons!");
	}
};