#include<vector>
#include <string>
using namespace std;


template<class TKey, class TValue>
class THashTable
{
	struct TTableRec
	{
		TKey key;
		TValue value;
		bool empty = true;

		const bool operator > (const TTableRec& other) const
		{
			return key > other.key;
		}

		const bool operator < (const TTableRec& other) const
		{
			return key < other.key;
		}

		const bool operator >= (const TTableRec& other) const
		{
			return key >= other.key;
		}

		const bool operator <= (const TTableRec& other) const
		{
			return key <= other.key;
		}

		const bool operator == (const TTableRec& other) const
		{
			return key == other.key;
		}

		const bool operator != (const TTableRec& other) const
		{
			return key == other.key;
		}
	};

	struct Logger
	{
		size_t sam;
		string log;
	}logger;

	vector<TTableRec> table;

	const size_t sz;

	template<class TKey>
	const size_t hash(const TKey& key) const
	{
		return key % sz;
	}

	template<>
	const size_t hash<string>(const string& key) const
	{
		size_t res = 0;
		for(auto& letter : key)
		{
			res += static_cast<size_t>(letter);
		}
		return res % sz;
	}
public:

	THashTable(size_t size) :sz(size), table(size) {}

	~THashTable() = default;

	const TValue& Find(const TKey& key)
	{
		logger.log = string("Operation Find: ");
		logger.sam = 0;
		size_t hashRes = hash(key);
		for(size_t i = 0; i < sz/2; i++)
		{
			logger.sam++;
			size_t ind = (hashRes + 3 * i + 7 * i * i) % sz;
			auto& rec = table[ind];
			if (rec.empty == true)
			{
				throw exception("Element not found!");
			}
			else
			{
				if(rec.key == key)
				{
					return rec.value;
				}
			}
		}
	}

	void Insert(const TKey& key, const TValue& value)
	{
		logger.log = string("Operation Insert: ");
		logger.sam = 0;
		TTableRec rec{ key, value, false };
		size_t hashRes = hash(key);
		for (size_t i = 0; i < sz / 2; i++)
		{
			logger.sam++;
			size_t ind = (hashRes + 3 * i + 7 * i * i) % sz;
			auto& curRec = table[ind];
			if (curRec.empty == true)
			{
				curRec = rec;
				return;
			}
			if(curRec.key == key)
			{
				return;
			}
		}
		throw exception("Table is full!");
	}

	void Delete(const TKey& key)
	{
		logger.log = string("Operation Delete: ");
		logger.sam = 0;
		size_t hashRes = hash(key);
		for (size_t i = 0; i < sz / 2; i++)
		{
			logger.sam++;
			size_t ind = (hashRes + 3 * i + 7 * i * i) % sz;
			auto& rec = table[ind];
			if(rec.key == key)
			{
				rec.empty = true;
				return;
			}
		}
	}

	string log()
	{
		return logger.log + string("Cost: ") + to_string(logger.sam) + string(" samplings!");
	}

	size_t size()
	{
		return sz;
	}
};