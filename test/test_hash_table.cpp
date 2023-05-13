#include <iostream>
#include "../gtest/gtest.h"
#include "../include/hash-table.h"
#include "../polinom/include/polinom.h"
#include <Windows.h>

TEST(class_HashTable, can_make_HashTable)
{
	ASSERT_NO_THROW(HashTable<Polinoms>());
}

TEST(class_HashTable, can_make_HashTable_with_positive_length)
{
	ASSERT_NO_THROW(HashTable<Polinoms>(10));
}

TEST(class_HashTable, throw_HashTable_with_negative_length)
{
	ASSERT_ANY_THROW(HashTable<Polinoms>(-8));
}

TEST(class_HashTable, can_correct_hashFunction1)
{
	HashTable<Polinoms> A(3);
	EXPECT_EQ(3, A.HashFunction1("abc"));
}

TEST(class_HashTable, can_correct_hashFunction2)
{
	HashTable<Polinoms> A(4);
	EXPECT_EQ(5, A.HashFunction2("adb"));
}

TEST(class_HashTable, can_insert)
{
	int a = 0;
	HashTable<Polinoms> A(4);
	ASSERT_NO_THROW(A.insert("a", Polinoms("123xyz"), a));
	ASSERT_TRUE(std::get<Polinoms>(A.Search("a")) == Polinoms("123xyz"));
}