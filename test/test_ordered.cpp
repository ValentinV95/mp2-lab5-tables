#include "Ordered.h"
#include "gtest.h"

TEST(Ordered, can_insert)
{
	Ordered<int> avl;
	ASSERT_NO_THROW(avl.add(1, 2));
}

TEST(Ordered, can_delete)
{
	Ordered<int> avl;
	avl.add(1, 1);
	ASSERT_NO_THROW(avl.del(1));
}

TEST(Ordered, throw_when_delete_non_existent_element)
{
	Ordered<int> avl;
	ASSERT_ANY_THROW(avl.del(1));
}

TEST(Ordered, can_find)
{
	Ordered<int> avl;
	avl.add(1, 2);
	ASSERT_NO_THROW(avl.find(1));
}

TEST(Ordered, throw_when_find_non_existent_element)
{
	Ordered<int> avl;
	ASSERT_ANY_THROW(avl.find(1));
}