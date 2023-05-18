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

//================================================[ Hash-Table ]===============================================================================


TEST(HASH_TABLE,hash_function_work_properly )
{
	int a1 = h("a");     //a=97   0
	int b = h("b");		//b=98   1
	int v = h("v");		//v=118  21
	int a2 = h("a");		//a=97   26



	EXPECT_EQ(a1, 0);
	EXPECT_EQ(b, 1);
	EXPECT_EQ(v, 21);
	EXPECT_EQ(a2, 0);
}


TEST(HASH_TABLE, insert_and_find_work_properly)
{
	Hash<polinom> H;
	polinom pol;

	H.insert("a1", pol);
	H.insert("b", pol);
	H.insert("v", pol);
	H.insert("a2", pol);

	EXPECT_EQ(H.find("a1"), 0);
	EXPECT_EQ(H.find("b"), 1);
	EXPECT_EQ(H.find("v"), 21);
	EXPECT_EQ(H.find("a2"), 26);
}



TEST(HASH_TABLE, polinom_deletion_work_properly)
{
	Hash<polinom> H;
	polinom pol;

	H.insert("a1", pol);
	H.insert("b", pol);
	H.insert("v", pol);
	H.insert("a2", pol);


	H.vec[H.find("a1")].first = "no!";

	H.vec[H.find("b")].first = "no!";

	H.vec[H.find("v")].first = "no!";

	H.vec[H.find("a2")].first = "no!";


	EXPECT_EQ(H.find("a1"), -1);
	EXPECT_EQ(H.find("b"), -1);
	EXPECT_EQ(H.find("v"), -1);
	EXPECT_EQ(H.find("a2"), -1);



}


TEST(HASH_TABLE, number_of_collision_work_properly)
{

	Hash<polinom> H;
	polinom pol;

	int start = all_collision;
	
	H.insert("a1", pol);
	H.insert("a2", pol);
	H.insert("a3", pol);
	H.insert("a4", pol);

	int end = all_collision;

	start = end - start;

	all_collision = all_collision - 6;

	EXPECT_EQ(start, 6);

	


}









