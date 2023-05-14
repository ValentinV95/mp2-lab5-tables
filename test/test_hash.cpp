#include "Hash.h"
#include "gtest.h"

TEST(Hash, can_insert)
{
	Hash<int> Hash;
	ASSERT_NO_THROW(Hash.add(1, 1));
}

TEST(Hash, can_delete)
{
	Hash<int> Hash;
	Hash.add(1, 1);
	ASSERT_NO_THROW(Hash.del(1));
}

TEST(Hash, throw_when_table_oveflow)
{
	Hash<int> Hash(1);
	Hash.add(1, 1);
	ASSERT_ANY_THROW(Hash.add(1, 1));
}

TEST(Hash, throw_when_delete_non_existent_element)
{
	Hash<int> Hash;
	ASSERT_ANY_THROW(Hash.del (1));
}

TEST(Hash, can_find)
{
	Hash<int> Hash;
	Hash.add(1, 1);
	ASSERT_NO_THROW(Hash.find(1));
}

TEST(Hash, throw_when_find_non_existent_element)
{
	Hash<int> Hash;
	ASSERT_ANY_THROW(Hash.find(1));
}