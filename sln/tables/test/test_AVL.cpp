#include "gtest.h"
#include "TAVLtable.h"

TEST(AVLtable, can_create_table)
{
	ASSERT_NO_THROW(TAVLtable<double> table);
}

TEST(AVLtable, can_insert_element)
{
	TAVLtable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
}

TEST(AVLtable, can_insert_elements)
{
	TAVLtable<double> table;
	ASSERT_NO_THROW(table.Insert("k1", 1));
	ASSERT_NO_THROW(table.Insert("k2", 2));
	ASSERT_NO_THROW(table.Insert("k3", 3));
}

TEST(AVLtable, can_search_element)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	EXPECT_EQ(table.Search("k1"), 1);
}

TEST(AVLtable, throws_when_search_element_is_not_in_the_table)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_ANY_THROW(table.Search("k4"));
}

TEST(AVLtable, can_delete_element)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k1"));
}

TEST(AVLtable, can_delete_root)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	ASSERT_NO_THROW(table.Delete("k2"));
}

TEST(AVLtable, cant_search_deleted_element)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_ANY_THROW(table.Search("k2"));
}

TEST(AVLtable, can_insert_element_after_delete)
{
	TAVLtable<double> table;
	table.Insert("k1", 1);
	table.Insert("k2", 2);
	table.Insert("k3", 3);
	table.Delete("k2");
	ASSERT_NO_THROW(table.Insert("k2", 2));
}
