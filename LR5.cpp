
#include <iostream>
#include "disordered.h"
#include "Ordered.h"
#include "Wraper.h"
#include "hash_table/HashTable.h"
#include <string>

using namespace std;

int main()
{
	Wraper<int> w = Wraper<int>(10);

	bool ext = false;
	string s_cmd;
	string key;
	string value;
	int cmd;
	int k,v;

	while (!ext)
	{	
		k = -1;
		v = -1;
		s_cmd = "";
		cout << "\nEnter command: ";
		std::getline(cin, s_cmd);
		cmd = -1;
		if (s_cmd == "add") {

			cmd = 1;
		}

		if (s_cmd == "set_quan") {
			cmd = 2;
		}

		if (s_cmd == "delete") {
			cmd = 4;
		}

		if (s_cmd == "find") {
			cmd = 3;
		}

		if (s_cmd == "ext") {
			ext = true;
			cmd = -1;
		}
		

		switch (cmd)
		{
		case 1:
			cout << "\nInsert key: ";
			std::getline(cin, key);
			cout << "\nInsert value: ";
			std::getline(cin, value);
			k = atoi(key.c_str());
			v = atoi(value.c_str());
			w.add(k, v);
			break;

		case 2:
			cout << "\nInsert new Length: ";
			std::getline(cin, key);
			k = atoi(key.c_str());
			w = Wraper<int>(k);
			break;

		case 3:
			cout << "\nInsert key: ";
			std::getline(cin, key);
			k = atoi(key.c_str());
			cout<<w.find(k);
			break;
			
		case 4:
			cout << "\nInsert key: ";
			std::getline(cin, key);
			k = atoi(key.c_str());
			w.remove(k);
			break;

		default:
			break;
		}
	}
}