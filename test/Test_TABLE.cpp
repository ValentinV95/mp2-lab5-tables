#include "../gtest/gtest.h"
#include "../include/HASH_TABLE.h"

TEST(ARRAY, correct_push_not_equal_key)
{
	ARRAY<int> A;
	int N = 100;
	for (int i = 0; i < N; i++)
	{
		A.push(make_pair(N+i, i));
		EXPECT_EQ(A.mas[i].second, i);
	}
}

TEST(ARRAY, correct_push_equal_key)
{
	ARRAY<int> A;
	A.push(make_pair(1, 2));
	A.push(make_pair(1, 3));
	EXPECT_EQ(A.mas.size(), 1);
	EXPECT_EQ(A.mas[0].second, 3);
}

TEST(ARRAY, correct_search_found_key)
{
	ARRAY<int> A;
	A.push(make_pair(1, 2));

	EXPECT_EQ(A.search(1).first, 1);
	EXPECT_EQ(A.search(1).second, 2);
}

TEST(ARRAY, correct_search_not_found_key)
{
	ARRAY<int> A;
	A.push(make_pair(2, 2));

	EXPECT_EQ(A.search(1).first, -1);
}

TEST(ARRAY, correct_del_found_key)
{
	ARRAY<int> A;
	A.push(make_pair(1, 1));
	A.push(make_pair(2, 2));
	EXPECT_EQ(A.search(2).first, 2);
	A.del(2);
	EXPECT_EQ(A.search(2).first, -1);
	EXPECT_EQ(A.mas.size(), 1);
}

TEST(ARRAY, correct_del_not_found_key)
{
	ARRAY<int> A;
	A.push(make_pair(1, 1));
	A.push(make_pair(3, 2));
	EXPECT_EQ(A.search(2).first, -1);
	A.del(2);
	EXPECT_EQ(A.search(2).first, -1);
	EXPECT_EQ(A.mas.size(), 2);
}

TEST(TREE, correct_push_not_equal_key)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	EXPECT_EQ(A.head->data.second, 1);
	A.push(make_pair(5, 2));
	EXPECT_EQ(A.head->left->data.second, 2);
	A.push(make_pair(15, 3));
	EXPECT_EQ(A.head->right->data.second, 3);
	A.push(make_pair(7, 4));
	EXPECT_EQ(A.head->left->right->data.second, 4);
}

TEST(TREE, correct_push_equal_key)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	EXPECT_EQ(A.head->data.second, 1);
	A.push(make_pair(10, 2));
	EXPECT_EQ(A.head->data.second, 2);
	A.push(make_pair(10, 3));
	EXPECT_EQ(A.head->data.second, 3);
	A.push(make_pair(10, 4));
	EXPECT_EQ(A.head->data.second, 4);
	EXPECT_EQ(A.head->left, nullptr);
	EXPECT_EQ(A.head->right, nullptr);
}

TEST(TREE, correct_search_found_key)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	EXPECT_EQ(A.search(7)->data.second,4);
}

TEST(TREE, correct_search_not_found_key)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	EXPECT_EQ(A.search(8), nullptr);
}

TEST(TREE, correct_del_found_key)
{
	AWL_TREE<int> A;
	Node<int> *B;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	B = A.del(10);
	EXPECT_EQ(B->data.first, 10);
	EXPECT_EQ(A.search(10), nullptr);
}

TEST(TREE, correct_del_not_found_key)
{
	AWL_TREE<int> A;
	Node<int>* B;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	B = A.del(11);
	EXPECT_EQ(B, nullptr);
}

TEST(TREE, correct_get_min)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	EXPECT_EQ(A.get_min()->data.first, 5);
}

TEST(TREE, correct_LVL)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	//          +-----10-----+
	//          |            |
	//          5---+       15
	//              |
	//              7
	EXPECT_EQ(A.LVL(A.head), 3);
}

TEST(TREE, correct_getlvl)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(15, 3));
	A.push(make_pair(7, 4));
	//          +-----10-----+
	//          |            |
	//          5---+       15
	//              |
	//              7
	EXPECT_EQ(A.getlvl(A.head), -1);
}

TEST(TREE, correct_rotate_right)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(4, 4));
	//          +-----10             +----5----+
	//          |                    |         |
	//      +---5         ------>    4         10
	//      |        
	//      4        
	EXPECT_EQ(A.head->data.first, 5);
	EXPECT_EQ(A.head->left->data.first, 4);
	EXPECT_EQ(A.head->right->data.first, 10);
}

TEST(TREE, correct_rotate_big_right)
{
	AWL_TREE<int> A;
	A.push(make_pair(10, 1));
	A.push(make_pair(5, 2));
	A.push(make_pair(4, 4));
	//          +-----10                +----10            +---5---+
	//          |                       |                  |       |
	//          4--+      ------>   +---5        ------>   4       10
	//             |                |                       
	//             5                4                       
	EXPECT_EQ(A.head->data.first, 5);
	EXPECT_EQ(A.head->left->data.first, 4);
	EXPECT_EQ(A.head->right->data.first, 10);
}

TEST(TREE, correct_rotate_left)
{
	AWL_TREE<int> A;
	A.push(make_pair(4, 4));
	A.push(make_pair(5, 2));
	A.push(make_pair(10, 1));
	//      4---+                    +----5----+
	//          |                    |         |
	//          5----+    ------>    4         10
	//               |
	//               10
	EXPECT_EQ(A.head->data.first, 5);
	EXPECT_EQ(A.head->left->data.first, 4);
	EXPECT_EQ(A.head->right->data.first, 10);
}

TEST(TREE, correct_rotate_big_left)
{
	AWL_TREE<int> A;
	A.push(make_pair(4, 4));
	A.push(make_pair(5, 2));
	A.push(make_pair(10, 1));
	//  4------+        4---+                    +----5----+
	//         |            |                    |         |
	//     +---5  ----->    5----+    ------>    4         10
	//     |                     |
	//     10                    10                   
	EXPECT_EQ(A.head->data.first, 5);
	EXPECT_EQ(A.head->left->data.first, 4);
	EXPECT_EQ(A.head->right->data.first, 10);
}

TEST(HASH_TABLE, correct_push_not_equal_key)
{
	HASH_TABLE<int, 0> A(10);
	A.push(make_pair(1, 2));
	EXPECT_EQ(A.mas[A.hash(1, 0)].first, 1);
	EXPECT_EQ(A.mas[A.hash(1, 0)].second, 2);

}

TEST(HASH_TABLE, correct_push_equal_key)
{
	HASH_TABLE<int, 0> A(10);
	A.push(make_pair(1, 2));
	A.push(make_pair(1, 3));
	EXPECT_EQ(A.mas[A.hash(1, 0)].first, 1);
	EXPECT_EQ(A.mas[A.hash(1, 0)].second, 3);
}

TEST(HASH_TABLE, correct_search_found_key)
{
	HASH_TABLE<int, 0> A(10);
	A.push(make_pair(1, 2));
	EXPECT_EQ(A.search(1).first, 1);
	EXPECT_EQ(A.search(1).second, 2);
}

TEST(HASH_TABLE, correct_search_not_found_key)
{
	HASH_TABLE<int, 0> A(10);
	A.push(make_pair(1, 2));
	EXPECT_EQ(A.search(2).first, -2);
}

TEST(HASH_TABLE, dont_push_more_then_size)
{
	HASH_TABLE<int, 0> A(1);
	A.push(make_pair(1, 1));
	EXPECT_ANY_THROW(A.push(make_pair(2, 2)));
}

TEST(HASH_TABLE, correct_del)
{
	HASH_TABLE<int, 0> A(2);
	A.push(make_pair(1, 1));
	A.push(make_pair(2, 2));
	A.del(2);
	EXPECT_EQ(A.search(2).first, -2);
}
