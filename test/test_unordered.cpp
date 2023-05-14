#include "Unordered.h"
#include "gtest.h"


TEST(Unordered, can_insert)
{
	Unordered<int> Unordered;
	ASSERT_NO_THROW(Unordered.add(1, 1));
}

TEST(Unordered, can_delete)
{
	Unordered<int> Unordered;
	Unordered.add(1, 1);
	ASSERT_NO_THROW(Unordered.del(1));
}

TEST(Unordered, throw_when_delete_non_existent_element)
{
	Unordered<int> Unordered;
	ASSERT_ANY_THROW(Unordered.del(1));
}

TEST(Unordered, can_find)
{
	Unordered<int> Unordered;
	Unordered.add(1, 1);
	ASSERT_NO_THROW(Unordered.find(1));
}

//TEST(Unordered, can_chagne_value_find)
//{
//	Unordered<int> Unordered;
//	int val = 1;
//	Unordered.add(1, val);
//	Unordered.find(1) = val + 1;
//	EXPECT_NE(Unordered.getElement(1), val);
//}

TEST(Unordered, throw_when_find_non_existent_element)
{
	Unordered<int> Unordered;
	ASSERT_ANY_THROW(Unordered.find(1));
}