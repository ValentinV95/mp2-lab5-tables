#include "pch.h"
#include "../disordered.h"
#include "../Ordered.h"
#include "../hash_table/HashTable.h"
#include "../AVL.h"
#include "../hash_table/HashTable.cpp"

TEST(TestTables, TesrOrdered) {
	Ordered<int, int> o = Ordered<int, int>();

	o.add(0, 0);
	o.add(4, 4);
	o.add(3, 3);
	o.add(1, 1);
	o.add(4, 6);
	o.add(2, 2);

	EXPECT_EQ(o.find(0), 0);
	EXPECT_EQ(o.find(1), 1);
	EXPECT_EQ(o.find(2), 2);
	EXPECT_EQ(o.find(3), 3);
	EXPECT_EQ(o.find(4), 6);

	o.remove(4);
	EXPECT_EQ(o.find(4), int());
	o.remove(0);
	EXPECT_EQ(o.find(0), int());
	o.remove(2);
	EXPECT_EQ(o.find(2), int());

	//o.cprint();

}
TEST(TestTables, TesrHashTab) {

	HashTable<int> h = HashTable<int>(5);

	h.insert(0, 12);
	h.insert(1, 144);
	h.insert(2, 22);
	h.insert(3, 155);
	h.insert(4, 227);

	h.search(0);
	h.search(1);
	h.search(2);
	h.search(3);
	h.search(4);

	EXPECT_EQ(h.search(0)->getData(), 12);
	EXPECT_EQ(h.search(1)->getData(), 144);
	EXPECT_EQ(h.search(2)->getData(), 22);
	EXPECT_EQ(h.search(3)->getData(), 155);
	EXPECT_EQ(h.search(4)->getData(), 227);

	h.deleteItem(0); // !
	EXPECT_EQ(h.search(0), nullptr);

	h.deleteItem(2); // !
	EXPECT_EQ(h.search(2), nullptr);

	h.deleteItem(4); // !
	EXPECT_EQ(h.search(4), nullptr);

}

TEST(TestTables, TesrUnordered) {

	unordered<int> d = unordered<int>();
	
	d.add(0, 0);
	d.add(1, 1);
	d.add(2, 2);
	d.add(3, 3);
	d.add(4, 4);
	d.add(4, 6);


	EXPECT_EQ(d.find(0).data, 0);
	EXPECT_EQ(d.find(1).data, 1);
	EXPECT_EQ(d.find(2).data, 2);
	EXPECT_EQ(d.find(3).data, 3);
	EXPECT_EQ(d.find(4).data, 6);

	d.remove(4);
	EXPECT_EQ(d.find(4).data, int());
	d.remove(0);
	EXPECT_EQ(d.find(0).data, int());
	d.remove(2);
	EXPECT_EQ(d.find(2).data, int());

	//d.cprint();
}

TEST(TestTables, TestAVL) {
	AVL<int>* a = new AVL<int>();

	a = a->insert(a, 0, 0);
	a = a->insert(a, 1, 1);
	a = a->insert(a, 2, 2);
	a = a->insert(a, 3, 3);
	a = a->insert(a, 4, 4);
	a = a->insert(a, 4, 6);

	EXPECT_EQ(a->getHeight(a), 3);
	
	EXPECT_EQ(a->find(a, 1), 1);
	EXPECT_EQ(a->find(a, 2), 2);


	a = a->deleteNode(a, 1);
	a = a->deleteNode(a, 0);

	EXPECT_EQ(a->find(a, 0), int());
	EXPECT_EQ(a->find(a, 1), int());
}