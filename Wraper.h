#pragma once
#include "disordered.h"
#include "Ordered.h"
#include "hash_table/HashTable.h"
#include "AVL.h"

template <typename T>
class Wraper {
public:
	Wraper(int size) {
		hs = HashTable<T>(size);
		un = unordered<T>();
		//o = Ordered<int, T>();
		avl = new  AVL<T>();

	}

	void add(int key, T t) {
		hs.insert(key, t);
		un.add(key, t);
		avl = avl->insert(avl, key, t);
		//o.add(key, t);
	}

	void remove(int key) {
		hs.deleteItem(key);
		un.remove(key);
		avl = avl->deleteNode(avl, key);
		//o.add(key);

	}

	T find(int key) {
		
		hs.search(key);
		auto a = avl->insert(avl, key, T());
		return un.find(key).data;
	}
private:
	HashTable<T> hs = HashTable<T>(0);
	unordered<T> un;
	//Ordered<int, T> o;
	AVL<T>* avl;

};

