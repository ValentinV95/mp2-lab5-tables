#include "unorderedTable.h"
#include "gtest.h"


TEST(unorderedTable, can_insert)
{
	unorderedTable<int, int> unordered;
	ASSERT_NO_THROW(unordered.addElement(1, 1));
}

TEST(unorderedTable, can_delete)
{
	unorderedTable<int, int> unordered;
	unordered.addElement(1, 1);
	ASSERT_NO_THROW(unordered.deleteElement(1));
}

TEST(unorderedTable, throw_when_delete_non_existent_element)
{
	unorderedTable<int, int> unordered;
	ASSERT_ANY_THROW(unordered.deleteElement(1));
}

TEST(unorderedTable, can_find)
{
	unorderedTable<int, int> unordered;
	unordered.addElement(1, 1);
	ASSERT_NO_THROW(unordered.getElement(1));
}

TEST(unorderedTable, can_chagne_value_find)
{
	unorderedTable<int, int> unordered;
	int val = 1;
	unordered.addElement(1, val);
	unordered.getElement(1) = val + 1;
	EXPECT_NE(unordered.getElement(1), val);
}

TEST(unorderedTable, throw_when_find_non_existent_element)
{
	unorderedTable<int, int> unordered;
	ASSERT_ANY_THROW(unordered.getElement(1));
}