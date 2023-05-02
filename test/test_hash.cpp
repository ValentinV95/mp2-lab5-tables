#include"gtest.h"
#include"THashTable.h"

TEST(HASH_TABLE, can_create_empty_table)
{
	THashTable<string, size_t> table(10);
	EXPECT_EQ(table.size(), 10);
}

TEST(HASH_TABLE, can_insert_element)
{
	THashTable<string, size_t> table(10);
	ASSERT_NO_THROW(table.Insert(string("One"), 1));
}

TEST(HASH_TABLE, can_insert_elements_with_equals_keys)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("AC"), 1); //int(A)+int(C) == int(B)+int(D)
	ASSERT_NO_THROW(table.Insert(string("BD"), 2));
}

TEST(HASH_TABLE, can_find_elements_with_equals_keys)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("AC"), 1); //int(A)+int(C) == int(B)+int(D)
	table.Insert(string("BD"), 2);
	EXPECT_EQ(table.Find(string("BD")),2);
}

TEST(HASH_TABLE, can_delete_element)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("One"), 1);
	ASSERT_NO_THROW(table.Delete(string("One")));
}

TEST(HASH_TABLE, can_find_element)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("One"), 1);
	EXPECT_EQ(table.Find(string("One")), 1);
}

TEST(HASH_TABLE, cant_find_element_with_wrong_key)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("One"), 1);
	ASSERT_ANY_THROW(table.Find(string("O")));
}

TEST(HASH_TABLE, cant_find_deleted_element)
{
	THashTable<string, size_t> table(10);
	table.Insert(string("One"), 1);
	table.Insert(string("Two"), 2);
	table.Delete(string("One"));
	ASSERT_ANY_THROW(table.Find(string("One")));
}