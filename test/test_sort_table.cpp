#include "../gtest/gtest.h"
#include "../include/AVL_Tree.h"
#include "../polinom/include/polinom.h"
#include <Windows.h>

TEST(class_sort_table, can_make_avltree)
{
	ASSERT_NO_THROW(Sorting_table<Polinoms>());
}

TEST(class_sort_table, can_correct_insert_in_left_subtree)
{
	int a = 0;
	Sorting_table<Polinoms> A;
	A.insert("a", Polinoms("123xyz"), a);
	A.insert("b", Polinoms("45x^3"), a);
	EXPECT_TRUE(A.getRoot()->key == "a");
	EXPECT_TRUE(A.getRoot()->value == Polinoms("123xyz"));
	EXPECT_TRUE(A.getRoot()->right->key == "b");
	EXPECT_TRUE(A.getRoot()->right->value == Polinoms("45x^3"));
}

TEST(class_sort_table, can_insert_with_name_already_used)
{
	int a = 0;
	Sorting_table<Polinoms> A;
	A.insert("a", Polinoms("123xyz"), a);
	ASSERT_ANY_THROW(A.insert("a", Polinoms("45x^3"), a));
}

TEST(class_sort_table, can_correct_insert_in_right_subtree)
{
	int a = 0;
	Sorting_table<Polinoms> A;
	A.insert("c", Polinoms("123xyz"), a);
	A.insert("b", Polinoms("45x^3"), a);
	EXPECT_TRUE(A.getRoot()->key == "c");
	EXPECT_TRUE(A.getRoot()->value == Polinoms("123xyz"));
	EXPECT_TRUE(A.getRoot()->left->key == "b");
	EXPECT_TRUE(A.getRoot()->left->value == Polinoms("45x^3"));
}