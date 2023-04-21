#include "hash_table.h"
#include <gtest.h>

TEST(HashTable, can_create_table_with_positive_size)
{
	ASSERT_NO_THROW(HashTable<int> table(5));
}

TEST(HashTable, throws_when_create_table_with_negative_size)
{
	ASSERT_ANY_THROW(HashTable<int> table(-1));
}

TEST(HashTable, throws_when_create_table_with_zero_size)
{
	ASSERT_ANY_THROW(HashTable<int> table(0));
}

TEST(HashTable, can_insert_entry_into_table)
{
	HashTable<int> table(3);

	ASSERT_NO_THROW(table.insert("first", 1));
}

TEST(HashTable, can_find_data_in_table_with_correct_insert)
{
	HashTable<int> table(3);
	table.insert("first", 1);
	int return_data = 0;
	ASSERT_NO_THROW(return_data = *table.find("first"));
	EXPECT_EQ(return_data, 1);
}

TEST(HashTable, returns_nullptr_when_key_is_not_found)
{
	HashTable<int> table(3);
	EXPECT_EQ(table.find("first"), nullptr);
}

TEST(HashTable, can_get_length)
{
	HashTable<int> table(3);
	table.insert("first", 1);
	EXPECT_EQ(table.get_length(), 1);
}

TEST(HashTable, cant_insert_dublicate_by_key)
{
	HashTable<int> table(3);
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.insert("first", 2));
}

TEST(HashTable, can_remove_entry)
{
	HashTable<int> table(2);
	table.insert("first", 1);
	ASSERT_NO_THROW(table.remove("first"));
	EXPECT_EQ(table.get_length(), 0);
}

TEST(HashTable, cant_remove_entry_when_key_is_not_found)
{
	HashTable<int> table(2);
	ASSERT_ANY_THROW(table.remove("first"));
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.remove("second"));
}

TEST(HashTable, can_insert_entry_after_remove)
{
	HashTable<int> table(2);
	table.insert("first", 1);
	table.insert("second", 2);
	table.remove("second");
	table.insert("second", 3);
	EXPECT_EQ(table.get_length(), 2);
	EXPECT_EQ(*table.find("second"), 3);
}
