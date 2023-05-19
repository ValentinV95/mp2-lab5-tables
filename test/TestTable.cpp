#define _CRT_SECURE_NO_WARNIGNS
#pragma warning(disable : 4996)
#pragma warning(disable : 4002)


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
/*

TEST(HASH_TABLE,hash_function_work_properly )
{
	int a1 = h("a");     //a=97   0
	int b = h("b");		//b=98   1
	int v = h("v");		//v=118  21
	int a2 = h("a");	//a=97   0



	EXPECT_EQ(a1, 0);
	EXPECT_EQ(b, 1);
	EXPECT_EQ(v, 21);
	EXPECT_EQ(a2, 0);
}

TEST(HASH_TABLE, constructor_work_properly)
{

	polinom e;
	Hash<polinom> H;
	string empty;
	empty = "no!";

	for (int i = 0; i < 99; i++)
	{
		EXPECT_EQ(H.vec[i].first, "no!");
	}

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



TEST(HASH_TABLE, polinom_delete_work_properly)
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



//================================================[ Unordered-Table ]===============================================================================

TEST(UNORDERED_TABLE, empty_constructor_work_properly)
{

	unordered_table<polinom> U;

	EXPECT_EQ(U.vec, nullptr);
	EXPECT_EQ(U.size, 0);
}


TEST(UNORDERED_TABLE, constructor_with_size_work_properly)
{

	unordered_table<polinom> U(14);
	EXPECT_EQ(U.size, 14);

	polinom a;
	for (int i = 0; i < U.size; i++)
	{
		EXPECT_EQ(U.vec[i].first, "no!");
		EXPECT_EQ(U.vec[i].second, a);
	}

}

TEST(UNORDERED_TABLE, set_size_work_properly)
{
	unordered_table<polinom> U;
	EXPECT_EQ(U.size, 0);

	U.set_size(27);

	EXPECT_EQ(U.size, 27);
}

TEST(UNORDERED_TABLE, insert_work_properly)
{
	unordered_table<polinom> U(5);
	polinom a;

	a.push(12.43, 123422);  // a= 12.43 x^12 y^34 z^22

	U.insert("a", a);
	U.insert("b", a);
	U.insert("c", a);

	EXPECT_EQ(U.vec[0].first,"a");
	EXPECT_EQ(U.vec[0].second, a);

	EXPECT_EQ(U.vec[1].first, "b");
	EXPECT_EQ(U.vec[1].second, a);

	EXPECT_EQ(U.vec[2].first, "c");
	EXPECT_EQ(U.vec[2].second, a);

}


TEST(UNORDERED_TABLE, find_work_properly)
{
	unordered_table<polinom> U(5);
	polinom a;

	a.push(12.43, 123422);  // a= 12.43 x^12 y^34 z^22

	U.insert("a", a);
	U.insert("b", a);
	U.insert("c", a);


	int f_b = U.find("b");
	int f_v = U.find("v");

	EXPECT_EQ(f_b, 1);
	EXPECT_EQ(f_v, -1);

	EXPECT_EQ(U.vec[f_b].first, "b");
	EXPECT_EQ(U.vec[f_b].second, a);
}

TEST(UNORDERED_TABLE, polinom_delete_work_properly)
{
	unordered_table<polinom> U(5);
	polinom a;

	a.push(12.43, 123422);  // a= 12.43 x^12 y^34 z^22

	U.insert("a", a);
	U.insert("b", a);
	U.insert("c", a);

	EXPECT_EQ(U.vec[2].first, "c");
	EXPECT_EQ(U.vec[2].second, a);

	polinom pol;

	U.vec[U.find("c")].second = pol;
	U.vec[U.find("c")].first = "no!";

	EXPECT_EQ(U.find("c"), -1);
	EXPECT_EQ(U.vec[2].first, "no!");
	EXPECT_EQ(U.vec[2].second, pol);

}

TEST(UNORDERED_TABLE, logger_work_properly)
{
	unordered_table<polinom> U(5);
	polinom a;

	U.insert("a", a);
	EXPECT_EQ(U.get_numbers(), 1);
	U.find("a");
	EXPECT_EQ(U.get_numbers(), 1);

	U.insert("b", a);

	U.insert("c", a);
	EXPECT_EQ(U.get_numbers(), 3);
	U.find("c");
	EXPECT_EQ(U.get_numbers(), 3);

}
*/

//================================================[ Red_Black-Table ]===============================================================================


TEST(RED_BLACK_TREE, no_colour_exception)
{
	R_B_Tree<polinom> T;	
	EXPECT_ANY_THROW(T.show_colour('a'););
	EXPECT_ANY_THROW(T.show_colour('h'););
	EXPECT_ANY_THROW(T.show_colour('q'););
	EXPECT_ANY_THROW(T.show_colour('3'););
	EXPECT_ANY_THROW(T.show_colour('%'););

}

TEST(RED_BLACK_TREE, empty_constructor_work_properly)
{
	R_B_Tree<polinom> T;

	EXPECT_EQ(T.Root, T.nil);
	EXPECT_EQ(T.Root->colour, 'b');
	EXPECT_EQ(T.nil->colour, 'b');
	EXPECT_EQ(T.Root->right, nullptr);
	EXPECT_EQ(T.nil->left, nullptr);
	EXPECT_EQ(T.nil->parent, nullptr);
}

TEST(RED_BLACK_TREE, Root_allways_black)
{
	R_B_Tree<polinom> T;
	EXPECT_EQ(T.Root, T.nil);

	polinom pol;
	T.insert("a", pol);
	EXPECT_FALSE(T.Root == T.nil);   // Root поменялся
	EXPECT_EQ(T.Root->colour, 'b');  // но остался чёрным
}

TEST(RED_BLACK_TREE, elements_get_right_colour)
{
	R_B_Tree<polinom> T;
	polinom pol; 

	EXPECT_EQ(T.Root->colour, 'b');

	T.insert("a", pol);
	EXPECT_EQ(T.Root->colour, 'b');

	T.insert("b", pol);
	T.insert("c", pol);

	EXPECT_EQ(T.Root->colour, 'b');
	EXPECT_EQ(T.Root->right->colour, 'r');
	EXPECT_EQ(T.Root->left->colour, 'r');

	T.insert("d", pol);
	EXPECT_EQ(T.Root->colour, 'b');
	EXPECT_EQ(T.Root->right->colour, 'b');
	EXPECT_EQ(T.Root->left->colour, 'b');
}

TEST(RED_BLACK_TREE, Big_check_insert_example)
{
	R_B_Tree<polinom> T;
	polinom pol;

	T.insert("a", pol);
	T.insert("b", pol);
	T.insert("c", pol);
	T.insert("d", pol);
	T.insert("e", pol);
	T.insert("f", pol);
	T.insert("g", pol);
	T.insert("h", pol);
	T.insert("i", pol);
	T.insert("j", pol);
	T.insert("k", pol);


	EXPECT_EQ(T.Root->colour, 'b');
	EXPECT_EQ(T.Root->key, "d");

//------- Left subtree --------

	EXPECT_EQ(T.Root->left->colour, 'b');
	EXPECT_EQ(T.Root->left->key, "b");

	EXPECT_EQ(T.Root->left->left->colour, 'b');
	EXPECT_EQ(T.Root->left->left->key, "a");

	EXPECT_EQ(T.Root->left->right->colour, 'b');
	EXPECT_EQ(T.Root->left->right->key, "c");

	//------- Right subtree --------

	EXPECT_EQ(T.Root->right->colour, 'b');
	EXPECT_EQ(T.Root->right->key, "f");

	EXPECT_EQ(T.Root->right->left->colour, 'b');
	EXPECT_EQ(T.Root->right->left->key, "e");

	EXPECT_EQ(T.Root->right->right->colour, 'r');
	EXPECT_EQ(T.Root->right->right->key, "h");

	EXPECT_EQ(T.Root->right->right->left->colour, 'b');
	EXPECT_EQ(T.Root->right->right->left->key, "g");

	EXPECT_EQ(T.Root->right->right->right->colour, 'b');
	EXPECT_EQ(T.Root->right->right->right->key, "j");

	EXPECT_EQ(T.Root->right->right->right->left->colour, 'r');
	EXPECT_EQ(T.Root->right->right->right->left->key, "i");

	EXPECT_EQ(T.Root->right->right->right->right->colour, 'r');
	EXPECT_EQ(T.Root->right->right->right->right->key, "k");


}



TEST(RED_BLACK_TREE, Big_check_remove_example)
{
	R_B_Tree<polinom> A;
	polinom POL;

	A.insert("a", POL);
	A.insert("b", POL);
	A.insert("c", POL);
	A.insert("d", POL);

	A.insert("e", POL);
	A.insert("f", POL);
	A.insert("g", POL);
	A.insert("h", POL);
	A.insert("i", POL);
	A.insert("j", POL);
	A.insert("k", POL);

	A.remove("a");
	A.remove("b");
	A.remove("c");
	A.remove("d");


	EXPECT_EQ(A.Root->colour, 'b');
	EXPECT_EQ(A.Root->key, "f");

	EXPECT_EQ(A.Root->left->colour, 'b');
	EXPECT_EQ(A.Root->left->key, "e");

	EXPECT_EQ(A.Root->right->colour, 'r');
	EXPECT_EQ(A.Root->right->key, "h");

	EXPECT_EQ(A.Root->right->left->colour, 'b');
	EXPECT_EQ(A.Root->right->left->key, "g");

	EXPECT_EQ(A.Root->right->right->colour, 'b');
	EXPECT_EQ(A.Root->right->right->key, "j");

	EXPECT_EQ(A.Root->right->right->left->colour, 'r');
	EXPECT_EQ(A.Root->right->right->left->key, "i");

	EXPECT_EQ(A.Root->right->right->right->colour, 'r');
	EXPECT_EQ(A.Root->right->right->right->key, "k");


}

TEST(RED_BLACK_TREE, find_work_properly)
{
	R_B_Tree<polinom> A;
	polinom POL;

	A.insert("a", POL);
	A.insert("b", POL);
	A.insert("c", POL);
	A.insert("d", POL);
	A.insert("e", POL);
	A.insert("f", POL);
	A.insert("g", POL);
	A.insert("h", POL);
	A.insert("i", POL);
	A.insert("j", POL);
	A.insert("k", POL);


	EXPECT_EQ(A.find("g")->colour, 'b');
	EXPECT_EQ(A.find("h")->colour, 'r');
	EXPECT_EQ(A.find("a")->colour, 'b');
	EXPECT_EQ(A.find("i")->colour, 'r');
	EXPECT_EQ(A.find("j")->colour, 'b');


}


TEST(RED_BLACK_TREE, logger_work_properly)
{
	R_B_Tree<polinom> A;
	polinom POL;

	A.insert("a", POL);
	A.insert("b", POL);
	A.insert("c", POL);
	A.insert("d", POL);
	A.insert("e", POL);
	A.insert("f", POL);
	A.insert("g", POL);
	A.insert("h", POL);
	A.insert("i", POL);
	A.insert("j", POL);
	A.insert("k", POL);

	A.find("g");
	EXPECT_EQ(A.get_numbers(), 4);

	A.find("a");
	EXPECT_EQ(A.get_numbers(), 3);

	A.find("i");
	EXPECT_EQ(A.get_numbers(), 5);
}


