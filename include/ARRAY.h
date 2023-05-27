#include "../polinom/include/Polinom.h"

int ARRAY_equesions = 0;
int ARRAY_del_vector = 0;
int ARRAY_search = 0;
int ARRAY_push_vector = 0;

template<typename T>
class ARRAY
{
public:
	vector<pair<int, T>> mas;

	ARRAY(){}

	void push(pair<int, T> A)
	{
		ARRAY_push_vector++;
		pair<int, T> I;
		if (search(A.first).first != -1)
		{
			for (int i = 0; i < mas.size(); i++)
			{
				I = mas[i];
				ARRAY_equesions +=2;
				if (I.first == A.first)
				{
					I.second = A.second;
					mas[i] = I;
				}
			}
		}
		else
		{
			mas.push_back(A);
		}
	}
	pair<int, T> search(int key)
	{
		ARRAY_search++;
		pair<int, T> I;
		ARRAY_equesions++;
		for (int i = 0; i < mas.size(); i++)
		{
			I = mas[i];
			ARRAY_equesions++;
			if (I.first == key)
			{
				return I;
			}
			ARRAY_equesions++;
		}
		return make_pair(-1, T());
	}

	void del(int key)
	{
		ARRAY_del_vector++;
		pair<int, T> I,tmp;
		ARRAY_equesions++;
		for (int i = 0; i < mas.size(); i++)
		{
			I = mas[i];
			ARRAY_equesions++;
			if (I.first == key)
			{
				ARRAY_equesions++;
				for (int j = i+1; j < mas.size(); j++, ARRAY_equesions++)
				{
					tmp = mas[j - 1];
					mas[j - 1] = mas[j];
					mas[j] = tmp;
				}
				mas.pop_back();
				break;
			}
			ARRAY_equesions++;
		}
	}
	void show();

	//vector have destructor
};

template<typename T>
void ARRAY<T>::show()
{
	cout << endl << "ARRAY" << endl << endl;
	pair<int, T> I;
	for (int i = 0; i < mas.size(); i++)
	{
		I = mas[i];
		cout << "Key: " << I.first << " Value: " << I.second << endl;
	}
}

void ARRAY<Polinom>::show()
{
	cout << endl << "ARRAY" << endl << endl;
	pair<int, Polinom> I;
	for (int i = 0; i < mas.size(); i++)
	{
		I = mas[i];
		cout << "Key: " << I.first << " Value: ";
		I.second << cout << endl;

	}
}