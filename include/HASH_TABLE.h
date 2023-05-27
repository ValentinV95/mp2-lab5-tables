#include "TREE.h"


int HASH_TABLE_equesions = 0;
int HASH_TABLE_del = 0;
int HASH_TABLE_search = 0;
int HASH_TABLE_push = 0;
int HASH_TABLE_hash = 0;
int HASH_TABLE_collisions = 0;









template<typename T,bool T_is_Polinom>
class HASH_TABLE
{
public:
	pair<int, T> *mas;
	int size = 0;
	int real_size = 0;

	
	HASH_TABLE(int N)
	{
		mas = new pair<int, T>[N];
		size = N;
		pair<int, T> *I;
		HASH_TABLE_equesions++;
		for (int i = 0; i < size; i++)
		{
			HASH_TABLE_equesions++;
			I = &mas[i];
			I->first = -1;
		}
	}
	void push(pair<int,T> A)
	{
		HASH_TABLE_push++;
		HASH_TABLE_equesions++;
		real_size++;
		if (real_size > size)
		{
			throw out_of_range("Table if full, dont push anymore!");
		}
		int key = A.first;
		int i = 0;
		int ret;
		pair<int, T> I;
		while (true)
		{
			ret = hash(key, i);
			I = mas[ret];
			HASH_TABLE_equesions++;
			if (I.first == -1 || I.first == key)
			{
				HASH_TABLE_equesions++;
				if (I.first == key)
				{
					real_size--;
				}
				mas[ret] = A;
				break;
			}
			HASH_TABLE_equesions++;
			HASH_TABLE_collisions++;
			i++;
		}
	}
	int hash(int key, int i)
	{
		HASH_TABLE_hash++;
		return (key + i * i) % size;
	}
	pair<int, T> search(int key)
	{
		HASH_TABLE_search++;
		pair<int, T> I,ret = make_pair(-2,T());
		for (int i = 0; i < size; i++)
		{
			I = mas[hash(key, i)];
			HASH_TABLE_equesions++;
			if (I.first == key)
			{
				return I;
			}
			HASH_TABLE_equesions++;
		}
		return ret;
	}
	void del(int key)
	{
		HASH_TABLE_del++;
		pair<int, T> I;
		HASH_TABLE_equesions++;
		for (int i = 0; i < 100; i++)
		{
			I = mas[hash(key, i)];
			HASH_TABLE_equesions++;
			if (I.first == key)
			{
				real_size--;
				mas[hash(key, i)] = make_pair(-1, T());
				break;
			}
			HASH_TABLE_equesions++;
		}
	}

	template<bool F = T_is_Polinom>
	enable_if_t<F,void>
	show()
	{
		pair<int, T> I;
		cout << endl << "HASH_TABLE" << endl << endl;
		for (int i = 0; i < size; i++)
		{
			I = mas[i];
			if (I.first != -1)
			{
				cout << "Key: " << I.first << " Value: ";
				I.second << cout << endl;
			}
		}
	}
	template<bool F = T_is_Polinom>
	enable_if_t<!F, void>
	show()
	{
		pair<int, T> I;
		cout << "HASH_TABLE" << endl << endl;
		for (int i = 0; i < size; i++)
		{
			I = mas[i];
			if (I.first != -1)
			{
				cout << "Key: " << I.first << " Value: " << I.second << endl;
			}
		}
	}
	//no need destructor
};






// Special polinom get_key function  (EXAMPLE1:  F(x,y,z) = x^2 --> key = 200      EXAMPLE2: F(x,y,z) = xy^2z^3+x^2z --> key = 123+201 = 324)

int key(Polinom A)
{
	int ret = 0;
	for (auto it = A.head; it != nullptr; it = it->next)
	{
		ret += it->xyz;
	}
	return (ret);
}

//NULL all loggers

void NULL_LOG()
{
	cout << "All logs cleared" << endl;

	HASH_TABLE_equesions = 0;
	HASH_TABLE_del = 0;
	HASH_TABLE_search = 0;
	HASH_TABLE_push = 0;
	HASH_TABLE_hash = 0;
	HASH_TABLE_collisions = 0;

	ARRAY_equesions = 0;
	ARRAY_del_vector = 0;
	ARRAY_search = 0;
	ARRAY_push_vector = 0;

	TREE_equesions = 0;
	TREE_del = 0;
	TREE_search = 0;
	TREE_push = 0;
}
void show_log()
{
	cout << endl << "/	/	/	/	/	/	/Logger	/	/	/	/	/	/	/" << endl << endl;
	cout << "///  HASH_TABLE  ///\n";
	cout << "HASH_TABLE_equesions " << HASH_TABLE_equesions << endl;
	cout << "HASH_TABLE_del " << HASH_TABLE_del << endl;
	cout << "HASH_TABLE_search " << HASH_TABLE_search << endl;
	cout << "HASH_TABLE_push " << HASH_TABLE_push << endl;
	cout << "HASH_TABLE_hash " << HASH_TABLE_hash << endl;
	cout << "HASH_TABLE_collisions " << HASH_TABLE_collisions << endl;
	cout << "///  ARRAY  ///\n";
	cout << "ARRAY_equesions " << ARRAY_equesions << endl;
	cout << "ARRAY_del_vector " << ARRAY_del_vector << endl;
	cout << "ARRAY_search " << ARRAY_search << endl;
	cout << "ARRAY_push_vector " << ARRAY_push_vector << endl;
	cout << "///  AWL_TREE  ///\n";
	cout << "TREE_equesions " << TREE_equesions << endl;
	cout << "TREE_del " << TREE_del << endl;
	cout << "TREE_search " << TREE_search << endl;
	cout << "TREE_push " << TREE_push << endl << endl << endl;

}






