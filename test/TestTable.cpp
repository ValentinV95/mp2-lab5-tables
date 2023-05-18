#include "../gtest/gtest.h"
#include "../include/UI.h"



TEST(MONOM, can_be_created)
{
	monom* mon = new monom(12, 100);

	EXPECT_EQ(mon->data, 12);
	EXPECT_EQ(mon->xyz, 100);
}

TEST(POLINOM, can_be_created)
{
	EXPECT_NO_THROW(polinom A;);
}

TEST(POLINOM, can_be_expansed)
{
	polinom A;
	EXPECT_NO_THROW(A.push(1, 1););
	EXPECT_NO_THROW(A.push(2, 1););
	EXPECT_NO_THROW(A.push(3, 1););
	EXPECT_NO_THROW(A.push(4, 1););
	EXPECT_NO_THROW(A.push(5, 1););

}



TEST(POLINOM, merge)
{
	polinom A;
	A.push(1, 1);
	A.push(2, 1);
	A.push(3, 1);
	A.push(4, 1);
	A.push(5, 1);

	EXPECT_EQ(A.head->data, 15);
	EXPECT_EQ(A.head->xyz, 1);
}

TEST(POLINOM, operator_plus)
{
	polinom A;
	A.push(1, 1);
	A.push(2, 1);

	polinom B;
	B.push(3, 1);
	B.push(4, 1);
	B.push(5, 1);

	A = A + B;

	EXPECT_EQ(A.head->data, 15);
	EXPECT_EQ(A.head->xyz, 1);
}
TEST(POLINOM, operator_minus)
{
	polinom A;
	A.push(1, 1);
	A.push(2, 1);

	polinom B;
	B.push(3, 1);
	B.push(4, 1);
	B.push(5, 1);

	A = A - B;

	EXPECT_EQ(A.head->data, -9);
	EXPECT_EQ(A.head->xyz, 1);
}


TEST(POLINOM, operator_to)
{
	polinom A;
	A.push(1, 1);
	A.push(2, 1);

	polinom B;
	B.push(3, 1);
	B.push(4, 1);
	B.push(5, 1);

	A = A * B;

	EXPECT_EQ(A.head->data, 36);
	EXPECT_EQ(A.head->xyz, 2);
}

TEST(POLINOM, operator_to_but_its_number)
{
	polinom A;
	A.push(1, 1);
	A.push(2, 1);

	A = A * 7;

	EXPECT_EQ(A.head->data, 21);
	EXPECT_EQ(A.head->xyz, 1);
}

TEST(POLINOM, clear)
{
	polinom A;

	A.push(1, 13);
	EXPECT_EQ(A.head->data, 1);
	EXPECT_EQ(A.head->xyz, 13);

	A.clear();
	EXPECT_EQ(A.head, nullptr);

	A.push(1, 13);
	EXPECT_EQ(A.head->data, 1);
	EXPECT_EQ(A.head->xyz, 13);
}

TEST(POLINOM, degree)
{
	polinom A;
	polinom B;

	A.push(0, 85);
	B.push(3, 15);

	EXPECT_NO_THROW(A = A * B;);
}

TEST(POLINOM, problem_degree)
{
	polinom A;
	polinom B;

	EXPECT_NO_THROW(A.push(0, -185););
	EXPECT_NO_THROW(B.push(0, 11231235););
}

TEST(POLINOM, minus_and_plus)
{
	polinom A;
	polinom B;

	A.push(3, 15);
	B.push(5, 15);

	A = A + B;
	EXPECT_EQ(A.head->data, 8);
	EXPECT_EQ(A.head->xyz, 15);



	A.clear();
	B.clear();

	A.push(-3, 15);
	B.push(-5, 15);

	A = A + B;
	EXPECT_EQ(A.head->data, -8);
	EXPECT_EQ(A.head->xyz, 15);



	A.clear();
	B.clear();

	A.push(3, 15);
	B.push(5, 15);

	A = A - B;
	EXPECT_EQ(A.head->data, -2);
	EXPECT_EQ(A.head->xyz, 15);



	A.clear();
	B.clear();

	A.push(-3, 15);
	B.push(-5, 15);

	A = A - B;
	EXPECT_EQ(A.head->data, 2);
	EXPECT_EQ(A.head->xyz, 15);
}


TEST(POLINOM, check)
{
	polinom A;
	polinom B;

	A.push(3, 15);
	B.push(-5, 15);

	A = A + B;
	EXPECT_EQ(A.head->data, -2);
	EXPECT_EQ(A.head->xyz, 15);


	A.clear();
	B.clear();

	A.push(3, 15);
	B.push(5, 15);
	A.push(3, 25);
	B.push(5, 10);

	A = A + B;

	EXPECT_EQ(A.head->data, 5);
	EXPECT_EQ(A.head->xyz, 10);

	EXPECT_EQ(A.head->next->data, 8);
	EXPECT_EQ(A.head->next->xyz, 15);

	EXPECT_EQ(A.head->next->next->data, 3);
	EXPECT_EQ(A.head->next->next->xyz, 25);

}





TEST(FUNCTIONS, degree_in_range_0_99)
{
	polinom A;
	polinom B;

	A.push(1, 85);
	B.push(3, 15);

	EXPECT_ANY_THROW(A = A * B;);

	A.clear();
	B.clear();

	A.push(1, 8);
	B.push(3, 5);

	EXPECT_NO_THROW(A = A * B;);


	B.clear();

	B.push(1, 99);
	EXPECT_ANY_THROW(A = A * B;);
}