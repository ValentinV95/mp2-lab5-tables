#pragma once

#include <string>
#include <vector>

using namespace std;
 
const int MAX_SIZE = 10000;

template <class TValue>
class THashTable
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

	vector<TTableRec> table[MAX_SIZE];
	Logger logger;

	int hashFunc(string key)
	{
		int tmp = 0;
		for (int i = 0; i < key.size(); i++)
			tmp += key[i];
		return tmp % MAX_SIZE;
	}
public:
	void Insert(string key, TValue value)
	{
		logger.log = string("Operation Insert: ");
		logger.comp = 0;
		int index = hashFunc(key);
		TTableRec row(key, value);
		for (int i = 0; i < table[index].size(); i++)
		{
			logger.comp++;
			if (table[index][i].key == key)
				throw exception("Element with this key is already exists");
		}
		table[index].push_back(row);
	}
	void Delete(string key)
	{
		logger.log = string("Operation Delete: ");
		logger.comp = 0;
		int index = hashFunc(key);
		for (int i = 0; i < table[index].size(); i++)
		{
			logger.comp++;
			if (table[index][i].key == key)
			{
				table[index].erase(table[index].begin() + i);
				return;
			}
		}
	}
	TValue& Search(string key)
	{
		logger.log = string("Operation Search: ");
		logger.comp = 0;
		int index = hashFunc(key);
		for (int i = 0; i < table[index].size(); i++)
		{
			logger.comp++;
			if (table[index][i].key == key)
			{
				return table[index][i].value;
			}
		}
		throw exception("This element was not found");
	}
	string logging()
	{
		return logger.log + string("Cost: ") + to_string(logger.comp) + string(" comparisons!");
	}
	void Print()
	{
		cout << endl << endl;
		for (int i = 0; i < MAX_SIZE; i++)
			for (int j = 0; j < table[i].size(); j++)
				cout << table[i][j].key << ": " << table[i][j].value;
		cout << endl << endl;
	}
};