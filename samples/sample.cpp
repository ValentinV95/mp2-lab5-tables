#include <iostream>
#include <locale.h>
//#include "tree.h"
#include "unordered_table.h"
//#include "polynomial.h"
#include "hash_table.h"
#include <random>
#include "ordered_table.h"

using namespace std;

std::string random_string(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	UnorderedTable<int> table1;
	//HashTable<int> table2;
	//OrderedTable<int> table3;
	string temp;
	int tmp;

	for (int i = 1; i < 20; i++)
	{
		table1.push(Pair<int>(random_string(i % 20), i));
		//table2.push(Pair<int>(random_string(i % 20), i));
		//table3.push(Pair<int>(random_string(i % 20), i));
	}

	table1.getTable();
	//table2.getTable();
	//table3.getTable();
}