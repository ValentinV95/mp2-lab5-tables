#include"gtest.h"
#include"TUnorderedTable.h"

TEST(UNORDERED_TABLE, can_create_empty_table)
{
	TUnorderedTable<string, size_t> table;
	EXPECT_EQ(table.size(), 0);
}

TEST(UNORDERED_TABLE, can_insert_element)
{
	TUnorderedTable<string, size_t> table;
	ASSERT_NO_THROW(table.Insert(string("One"),1));
}

TEST(UNORDERED_TABLE, inserted_element_changed_size)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	EXPECT_EQ(table.size(), 1);
}

TEST(UNORDERED_TABLE, can_delete_element)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	ASSERT_NO_THROW(table.Delete(string("One")));
}

TEST(UNORDERED_TABLE, deleting_element_changed_size)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	table.Insert(string("Two"), 2);
	table.Delete(string("One"));
	ASSERT_NO_THROW(table.size(),1);
}

TEST(UNORDERED_TABLE, can_find_element)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	EXPECT_EQ(table.Find(string("One")), 1);
}

TEST(UNORDERED_TABLE, cant_find_element_with_wrong_key)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	ASSERT_ANY_THROW(table.Find(string("O")));
}

TEST(UNORDERED_TABLE, cant_find_deleted_element)
{
	TUnorderedTable<string, size_t> table;
	table.Insert(string("One"), 1);
	table.Insert(string("Two"), 2);
	table.Delete(string("One"));
	ASSERT_ANY_THROW(table.Find(string("One")));
}