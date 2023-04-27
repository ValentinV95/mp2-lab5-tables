#include "gtest.h"
#include "TUnorderedTable.h"

TEST(UnorderedTable, can_create_table)
{
	ASSERT_NO_THROW(TUnorderedTable<double> table);
}

TEST(UnorderedTable, can_insert_element)
{
	TUnorderedTable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
}

TEST(UnorderedTable, can_insert_elements)
{
	TUnorderedTable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
	ASSERT_NO_THROW(table.Insert("k2", 2));
	ASSERT_NO_THROW(table.Insert("k3", 3));
}

TEST(UnorderedTable, can_search_element)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	EXPECT_EQ(table.Search("k1"), 1);
}

TEST(UnorderedTable, throws_when_search_element_is_not_in_the_table)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_ANY_THROW(table.Search("k4"));
}

TEST(UnorderedTable, can_delete_element)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k1"));
}

TEST(UnorderedTable, can_delete_root)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k2"));
}

TEST(UnorderedTable, cant_search_deleted_element)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_ANY_THROW(table.Search("k2"));
}

TEST(UnorderedTable, can_insert_element_after_delete)
{
	TUnorderedTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_NO_THROW(table.Insert("k2", 2));
}
