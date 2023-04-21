#include "ordered_table.h"
#include <gtest.h>

TEST(OrderedTable, can_create_table)
{
	ASSERT_NO_THROW(OrderedTable<int> table);
}

TEST(OrderedTable, can_insert_entry_into_table)
{
	OrderedTable<int> table;

	ASSERT_NO_THROW(table.insert("first", 1));
}

TEST(OrderedTable, can_find_data_in_table_with_correct_insert)
{
	OrderedTable<int> table;
	table.insert("first", 1);
	int return_data = 0;
	ASSERT_NO_THROW(return_data = *table.find("first"));
	EXPECT_EQ(return_data, 1);
}

TEST(OrderedTable, returns_nullptr_when_table_is_empty)
{
	OrderedTable<int> table;
	EXPECT_EQ(table.find("first"), nullptr);
}

TEST(OrderedTable, returns_nullptr_when_table_is_not_found)
{
	OrderedTable<int> table;
	table.insert("first", 1);
	EXPECT_EQ(table.find("second"), nullptr);
}

TEST(OrderedTable, cant_insert_dublicate_by_key)
{
	OrderedTable<int> table;
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.insert("first", 2));
}

TEST(OrderedTable, can_remove_entry)
{
	OrderedTable<int> table;
	table.insert("first", 1);
	ASSERT_NO_THROW(table.remove("first"));
	EXPECT_EQ(table.find("first"), nullptr);
}

TEST(OrderedTable, cant_remove_entry_when_key_is_not_found)
{
	OrderedTable<int> table;
	ASSERT_ANY_THROW(table.remove("first"));
	table.insert("first", 1);
	ASSERT_ANY_THROW(table.remove("second"));
}

TEST(OrderedTable, can_insert_entry_after_remove)
{
	OrderedTable<int> table;
	table.insert("first", 1);
	table.insert("second", 2);
	table.remove("second");
	table.insert("second", 3);
	EXPECT_EQ(*table.find("second"), 3);
}
