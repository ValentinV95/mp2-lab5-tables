#include<vector>

using namespace std;

template<class TKey, class TValue>
class TUnorderedTable
{
	struct TTableRec
	{
		TKey key;
		TValue value;
	};

	struct Logger
	{
		size_t comp;
		string log;
	}logger;

	vector<TTableRec> data;
public:
	TUnorderedTable() = default;

	~TUnorderedTable() = default;

	size_t size() { return data.size(); }

	const TValue& Find(TKey key)
	{
		logger.log = string("Operation Find: ");
		logger.comp = 0;
		for(auto& val : data)
		{
			logger.comp++;
			if (val.key == key)
			{
				return val.value;
			}
		}
		throw exception("Element not found!");
	}

	void Insert(TKey key,TValue value)
	{
		logger.log = string("Operation Insert: ");
		logger.comp = 0;
		data.push_back({ key, value });
	}

	void Delete(TKey key)
	{
		logger.log = string("Operation Delete: ");
		logger.comp = 0;
		for (size_t i = 0; i < data.size(); i++)
		{
			logger.comp++;
			if (data[i].key == key)
			{
				data[i] = data[data.size() - 1];
				data.pop_back();
				return;
			}
		}
	}

	string log()
	{
		return logger.log + string("Cost: ") + to_string(logger.comp) + string(" comparisons!");
	}
};