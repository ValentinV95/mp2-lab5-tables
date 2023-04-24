#include"gtest.h"
#include"TRBtree.h"

TEST(RBT_TABLE, can_create_empty_tree)
{
	ASSERT_NO_THROW(TRBTree<size_t> tree);
}

TEST(RBT_TABLE, can_insert_element)
{
	TRBTreeTable<string, size_t> table;
	ASSERT_NO_THROW(table.Insert(string("One"), 1));
}

TEST(RBT_TABLE, can_insert_many_elements)
{
	TRBTreeTable<string, size_t> table;
	ASSERT_NO_THROW(table.Insert(string("One"), 1));
	ASSERT_NO_THROW(table.Insert(string("Two"), 2));
	ASSERT_NO_THROW(table.Insert(string("Three"), 3));
	ASSERT_NO_THROW(table.Insert(string("Four"), 4));
	ASSERT_NO_THROW(table.Insert(string("Five"), 5));
	ASSERT_NO_THROW(table.Insert(string("Six"), 6));
}

TEST(RBT_TABLE, can_delete_root)
{
	TRBTreeTable<string, size_t> table;
	table.Insert(string("One"), 1);
	ASSERT_NO_THROW(table.Delete(string("One")));
}

TEST(RBT_TABLE, can_delete_leaf)
{
	TRBTreeTable<string, size_t> table;
	table.Insert(string("One"), 1);
	table.Insert(string("Two"), 2);
	ASSERT_NO_THROW(table.Delete(string("Two")));
}

TEST(RBT_TABLE, can_insert_element_after_delete_root)
{
	TRBTreeTable<size_t, size_t> table;
	table.Insert(2, 2);
	table.Insert(1, 1);
	table.Insert(3, 3);
	table.Delete(1);
	ASSERT_NO_THROW(table.Insert(4, 4));
}

TEST(RBT_TABLE, can_find_element)
{
	TRBTreeTable<string, size_t> table;
	table.Insert(string("One"), 1);
	EXPECT_EQ(table.Find(string("One")), 1);
}

TEST(RBT_TABLE, cant_find_element_with_wrong_key)
{
	TRBTreeTable<string, size_t> table;
	table.Insert(string("One"), 1);
	ASSERT_ANY_THROW(table.Find(string("O")));
}

TEST(RBT_TABLE, cant_find_deleted_element)
{
	TRBTreeTable<string, size_t> table;
	table.Insert(string("One"), 1);
	table.Insert(string("Two"), 2);
	table.Delete(string("One"));
	ASSERT_ANY_THROW(table.Find(string("One")));
}