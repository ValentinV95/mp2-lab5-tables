#include "../gtest/gtest.h"
#include "../include/array.h"
#include "../polinom/include/polinom.h"
#include "../polinom/src/polinom.cpp"

TEST(class_non_sort_table, can_make_array_default)
{
	ASSERT_NO_THROW(non_sort_table<Polinoms>());
}

TEST(class_non_sort_table, can_make_array_with_positive_length)
{
	ASSERT_NO_THROW(non_sort_table<Polinoms>(6));
}

TEST(class_non_sort_table, can_make_array_with_negative_length)
{
	ASSERT_ANY_THROW(non_sort_table<Polinoms>(-5));
}

TEST(class_non_sort_table, can_return_element_with_index)
{
	non_sort_table<Polinoms>A("a", Polinoms("123xyz"));
	EXPECT_TRUE(std::get<Polinoms>(A[0]) == Polinoms("123xyz"));
	EXPECT_TRUE(std::get<std::string>(A[0]) == "a");
}

TEST(class_non_sort_table, can_add_new_polinom)
{
	non_sort_table<Polinoms>A("a", Polinoms("123xyz"));
	non_sort_table<Polinoms>B(1);
	B.Add("a", Polinoms("123xyz"));
	EXPECT_TRUE(std::get<Polinoms>(B[0]) == std::get<Polinoms>(A[0]));
	EXPECT_TRUE(std::get<std::string>(B[0]) == std::get<std::string>(A[0]));
}

TEST(class_non_sort_table, can_add_new_polinom_with_name_already_using)
{
	non_sort_table<Polinoms>A("a", Polinoms("123xyz"));
	ASSERT_ANY_THROW(A.Add("a", Polinoms("56yz")));
}

TEST(class_non_sort_table, can_search_polinom_in_table)
{
	non_sort_table<Polinoms>A("a", Polinoms("123xyz"));
	non_sort_table<Polinoms>B(3);
	B.Add("c", Polinoms("34x^2"));
	B.Add("h", Polinoms("3y^2z^2"));
	B.Add("a", Polinoms("123xyz"));
	EXPECT_TRUE(std::get<Polinoms>(B.Search("a")) == std::get<Polinoms>(A[0]));
	EXPECT_TRUE(std::get<std::string>(B.Search("a")) == std::get<std::string>(A[0]));
}

TEST(class_non_sort_table, can_search_polinom_in_table_with_name_unused)
{
	non_sort_table<Polinoms>A("a", Polinoms("123xyz"));
	EXPECT_TRUE(std::get<Polinoms>(A.Search("b")) == Polinoms("0"));
	EXPECT_TRUE(std::get<std::string>(A.Search("b")) == "0");
}

TEST(class_non_sort_table, can_delete_polinom_in_table)
{
	non_sort_table<Polinoms>A(3);
	A.Add("a", Polinoms("123xyz"));
	A.Add("b", Polinoms("456yz"));
	A.Add("c", Polinoms("890z^2"));
	A.Extract("b");
	EXPECT_TRUE(std::get<Polinoms>(A.Search("b")) == Polinoms("0"));
	EXPECT_TRUE(std::get<std::string>(A.Search("b")) == "0");
}