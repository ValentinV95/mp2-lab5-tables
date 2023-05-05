#include "hashTable.h"
#include "gtest.h"

TEST(hashTable, can_insert)
{
	hashTable<int, int> hash;
	ASSERT_NO_THROW(hash.addElement(1, 1));
}

TEST(hashTable, can_delete)
{
	hashTable<int, int> hash;
	hash.addElement(1, 1);
	ASSERT_NO_THROW(hash.delElement(1));
}

TEST(hashTable, throw_when_table_oveflow)
{
	hashTable<int, int> hash(1);
	hash.addElement(1, 1);
	ASSERT_ANY_THROW(hash.addElement(1, 1));
}

TEST(hashTable, throw_when_delete_non_existent_element)
{
	hashTable<int, int> hash;
	ASSERT_ANY_THROW(hash.delElement(1));
}

TEST(hashTableTable, can_find)
{
	hashTable<int, int> hash;
	hash.addElement(1, 1);
	ASSERT_NO_THROW(hash.getElement(1));
}

TEST(hashTableTable, can_chagne_value_find)
{
	hashTable<int, int> hash;
	int val = 1;
	hash.addElement(1, val);
	hash.getElement(1) = val + 1;
	EXPECT_NE(hash.getElement(1), val);
}

TEST(hashTableTable, throw_when_find_non_existent_element)
{
	hashTable<int, int> hash;
	ASSERT_ANY_THROW(hash.getElement(1));
}