#include "Hash.h"
#include "polinom.h"
#include "Ordered.h"
#include "Unordered.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
	string s, sp;
	Unordered<Polinom> u;
	Ordered<Polinom> o;
	Hash<Polinom> h;
	vector<Polinom> pv;
	Polinom poli, p1, p2, p3;
	int key, key1, key2;
	cout << "Keys must not be repeated. And key values cannot be overwritten" << endl;
	cout << "Write the operation you want to perform:\n 'add'\n 'del'\n 'find'\n if you want to perform an operation with monoms, write 'pol'\n";
	cout << "and select operation\n  addition - '+'\n  subtract - '-'\n  multiplication - '*'\n";
	while (true)
	{
		cout << "Waiting for operation" << endl;
		getline(cin, s);
		if (s == "add")
		{
			string c;
			cout << "Enter key " << endl;
			cin >> key;
			poli.Input();
			poli.Delete_Similar();
			u.add(key, poli);
			o.add(key, poli);
			h.add(key, poli);
			cout << u.find(key)<<endl;
			cout << endl;
			poli.Delete_element();
		}
		else if (s == "del")
		{
			cin >> key;
			u.del(key);
			o.del(key);
			h.del(key);
			poli.Print();
			poli.Delete_element();
		}
		else if (s == "find")
		{
			cin >> key;
			u.find(key);
			o.find(key);
			h.find(key);
			cout << u.find(key);
			poli.Delete_element();
		}
		else if (s == "pol")
		{
			cout << "left operand key ";
			cin >> key1;
			cout << "right operand key ";
			cin >> key2;
			p1 = u.find(key1);
			p2 = u.find(key2);
			cout << "Write operation" << endl;
			string c;
			cin >> c;
			if (c == "+")
			{
				cout << "polinom 1 " << p1 << endl;
				cout << "polinom 2 " << p2 << endl;
				p3 = p1 + p2;
				cout << "result " << p3 << endl;
				cout << "Enter key ";
				cin >> key;
				o.add(key, p3);
				u.add(key, p3);
				h.add(key, p3);
				poli.Print();
				poli.Delete_element();
				p1.Delete_element();
				p2.Delete_element();
				p3.Delete_element();
			}
			else if (c == "-")
			{
				cout << "polinom 1 " << p1 << endl;
				cout << "polinom 2 " << p2 << endl;
				p3 = p1 - p2;
				cout << "result " << p3 << endl;
				cout << "Enter key ";
				cin >> key;
				o.add(key, p3);
				u.add(key, p3);
				h.add(key, p3);
				poli.Print();
				poli.Delete_element();
				p1.Delete_element();
				p2.Delete_element();
				p3.Delete_element();
			}
			else if (c == "*")
			{
				cout << "polinom 1 " << p1 << endl;
				cout << "polinom 2 " << p2 << endl;
				try
				{
					p3 = p1 * p2;
					cout << "result " << p3 << endl;
					cout << "Enter key";
					cin >> key;
					o.add(key, p3);
					u.add(key, p3);
					h.add(key, p3);
					poli.Print();
					poli.Delete_element();
					p1.Delete_element();
					p2.Delete_element();
					p3.Delete_element();
				}
				catch (const std::exception& ex)
				{
					cout << ex.what();
				}
			}
		}
	}
}