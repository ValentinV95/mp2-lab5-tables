#include <gtest.h>
#include "unordered_table.hpp"

TEST(UnorderedTable, can_create_unordered_table)
{
	ASSERT_NO_THROW(UnorderedTable<int> table);
}

TEST(UnorderedTable, can_push_to_empty_unordered_table)
{
	UnorderedTable<int> table;
	ASSERT_NO_THROW(table.push(Pair<int>("", 1)));
}

TEST(UnorderedTable, after_pushing_size_increase_to_one_in_empty_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	EXPECT_EQ(1, table.size());
}

TEST(UnorderedTable, can_push_to_unordered_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	ASSERT_NO_THROW(table.push(Pair<int>("", 1)));
}

TEST(UnorderedTable, after_pushing_size_increase_to_one_in_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	table.push(Pair<int>("1", 1));
	EXPECT_EQ(2, table.size());
}

TEST(UnorderedTable, after_pushing_duplicate_size_dont_increase_in_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	table.push(Pair<int>("", 1));
	EXPECT_EQ(1, table.size());
}

TEST(UnorderedTable, can_search_in_empty_unordered_table)
{
	UnorderedTable<int> table;
	ASSERT_NO_THROW(table.search(""));
}

TEST(UnorderedTable, search_in_empty_unordered_table_return_nullptr)
{
	UnorderedTable<int> table;
	EXPECT_EQ(nullptr, table.search(""));
}

TEST(UnorderedTable, can_search_in_unordered_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	ASSERT_NO_THROW(table.search(""));
}

TEST(UnorderedTable, searching_in_unordered_table_true)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	EXPECT_EQ(1, *table.search(""));
}

TEST(UnorderedTable, searching_in_unordered_table_false)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	EXPECT_EQ(nullptr, table.search("k"));
}

TEST(UnorderedTable, can_delete_row_in_unordered_table)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	ASSERT_NO_THROW(table.deleteRow(""));
}

TEST(UnorderedTable, deleting_row_in_unordered_table_true)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	table.deleteRow("");
	EXPECT_EQ(nullptr, table.search(""));
}

TEST(UnorderedTable, deleting_row_in_unordered_table_decrease_size_on_one)
{
	UnorderedTable<int> table;
	table.push(Pair<int>("", 1));
	table.deleteRow("");
	EXPECT_EQ(0, table.size());
}

TEST(UnorderedTable, can_delete_row_in_empty_table)
{
	UnorderedTable<int> table;
	ASSERT_NO_THROW(table.deleteRow(""));
}
