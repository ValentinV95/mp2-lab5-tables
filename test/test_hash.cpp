#include <gtest.h>
#include "hash_table.hpp"

TEST(HashTable, can_create_hash_table)
{
	ASSERT_NO_THROW(HashTable<int> table);
}

TEST(HashTable, can_create_hash)
{
	HashTable<int> table;
	ASSERT_NO_THROW(table.hash("a"));
}

TEST(HashTable, hash_is_true)
{
	HashTable<int> table;
	int test = static_cast<int>('a') % 200;
	EXPECT_EQ(test, table.hash("a"));
}

TEST(HashTable, can_search_in_empty_hash_table)
{
	HashTable<int> table;
	ASSERT_NO_THROW(table.search("a"));
}

TEST(HashTable, searching_in_empty_hash_table_return_nullptr)
{
	HashTable<int> table;
	EXPECT_EQ(nullptr, table.search("a"));
}

TEST(HashTable, can_push_in_empty_hash_table)
{
	HashTable<int> table;
	ASSERT_NO_THROW(table.push(Pair<int>("a", 1)));
}

TEST(HashTable, pushing_in_empty_hash_table_increase_size_on_one)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	EXPECT_EQ(1, table.size());
}

TEST(HashTable, pushing_in_empty_hash_table_true)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	EXPECT_EQ(1, *table.search("a"));
}

TEST(HashTable, can_search_in_hash_table)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	ASSERT_NO_THROW(table.search("a"));
}

TEST(HashTable, searching_in_hash_table_return_nullptr)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	EXPECT_EQ(nullptr, table.search("2"));
}

TEST(HashTable, can_push_in_hash_table)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	ASSERT_NO_THROW(table.push(Pair<int>("c", 1)));
}

TEST(HashTable, pushing_in_hash_table_increase_size_on_one)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	table.push(Pair<int>("c", 1));
	EXPECT_EQ(2, table.size());
}

TEST(HashTable, pushing_in_hash_table_true)
{
	HashTable<int> table;
	table.push(Pair<int>("a", 1));
	table.push(Pair<int>("c", 12));
	EXPECT_EQ(12, *table.search("c"));
}

TEST(HashTable, can_delete_row_in_empty_hash_table)
{
	HashTable<int> table;
	ASSERT_NO_THROW(table.deleteRow(""));
}

TEST(HashTable, deleting_row_in_empty_hash_table_dont_decrease_size)
{
	HashTable<int> table;
	table.deleteRow("");
	EXPECT_EQ(0, table.size());
}

TEST(HashTable, can_delete_row_in_hash_table)
{
	HashTable<int> table;
	table.push(Pair<int>("", 1));
	ASSERT_NO_THROW(table.deleteRow(""));
}

TEST(HashTable, deleting_row_in_hash_table_true)
{
	HashTable<int> table;
	table.push(Pair<int>("", 1));
	table.deleteRow("");
	EXPECT_EQ(nullptr, table.search(""));
}

TEST(HashTable, deleting_row_in_hash_table_decrease_size_on_one)
{
	HashTable<int> table;
	table.push(Pair<int>("", 1));
	table.deleteRow("");
	EXPECT_EQ(0, table.size());
}
