#include "unordered_table.h"
#include <gtest.h>

TEST(UnorderedTable, can_create_table_with_positive_size)
{
	ASSERT_NO_THROW(UnorderedTable<int> table(5));
}

TEST(UnorderedTable, throws_when_create_table_with_negative_size)
{
	ASSERT_ANY_THROW(UnorderedTable<int> table(-1));
}

TEST(UnorderedTable, throws_when_create_table_with_zero_size)
{
	ASSERT_ANY_THROW(UnorderedTable<int> table(0));
}

TEST(UnorderedTable, can_insert_entry_into_table)
{
	UnorderedTable<int> table(3);

	ASSERT_NO_THROW(table.insert("first", 1));
}

TEST(UnorderedTable, can_find_data_in_table_with_correct_insert)
{
	UnorderedTable<int> table(3);
	table.insert("first", 1);
	int return_data = 0;
	ASSERT_NO_THROW(return_data = *table.find("first"));
	EXPECT_EQ(return_data, 1);
}

TEST(UnorderedTable, returns_nullptr_when_key_is_not_found)
{
	UnorderedTable<int> table(3);
	EXPECT_EQ(table.find("first"), nullptr);
}

TEST(UnorderedTable, can_get_length)
{
	UnorderedTable<int> table(3);
	table.insert("first", 1);
	EXPECT_EQ(table.get_length(), 1);
}

TEST(UnorderedTable, cant_insert_dublicate_by_key)
{
	UnorderedTable<int> table(3);
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.insert("first", 2));
}

TEST(UnorderedTable, can_remove_entry)
{
	UnorderedTable<int> table(2);
	table.insert("first", 1);
	ASSERT_NO_THROW(table.remove("first"));
	EXPECT_EQ(table.get_length(), 0);
}

TEST(UnorderedTable, cant_remove_entry_when_key_is_not_found)
{
	UnorderedTable<int> table(2);
	ASSERT_ANY_THROW(table.remove("first"));
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.remove("second"));
}

TEST(UnorderedTable, cant_find_entry_after_remove)
{
	UnorderedTable<int> table(2);
	table.insert("first", 1);
	table.remove("first");
	EXPECT_EQ(table.find("first"), nullptr);
}

TEST(UnorderedTable, can_insert_entry_after_remove)
{
	UnorderedTable<int> table(2);
	table.insert("first", 1);
	table.remove("first");
	table.insert("first", 2);
	EXPECT_EQ(table.get_length(), 1);
	EXPECT_EQ(*table.find("first"), 2);
	table.insert("second", 2);
	table.remove("second");
	table.insert("second", 3);
	EXPECT_EQ(table.get_length(), 2);
	EXPECT_EQ(*table.find("second"), 3);
}
