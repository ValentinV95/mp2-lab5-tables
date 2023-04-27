#include "gtest.h"
#include "THashtable.h"

TEST(HashTable, can_create_table)
{
	ASSERT_NO_THROW(THashTable<double> table);
}

TEST(HashTable, can_insert_element)
{
	THashTable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
}

TEST(HashTable, can_insert_elements)
{
	THashTable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
	ASSERT_NO_THROW(table.Insert("k2", 2));
	ASSERT_NO_THROW(table.Insert("k3", 3));
}

TEST(HashTable, can_search_element)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	EXPECT_EQ(table.Search("k1"), 1);
}

TEST(HashTable, throws_when_search_element_is_not_in_the_table)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_ANY_THROW(table.Search("k4"));
}

TEST(HashTable, can_delete_element)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k1"));
}

TEST(HashTable, can_delete_root)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k2"));
}

TEST(HashTable, cant_search_deleted_element)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_ANY_THROW(table.Search("k2"));
}

TEST(HashTable, can_insert_element_after_delete)
{
	THashTable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_NO_THROW(table.Insert("k2", 2));
}
