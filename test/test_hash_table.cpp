#include "../gtest/gtest.h"
#include "../include/hash-table.h"
#include "../polinom/include/polinom.h"

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

	EXPECT_EQ(A.HashFunction1("abc"), int("ab"));
}