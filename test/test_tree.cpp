#include <gtest.h>
#include "tree.hpp"

TEST(Tree, can_create_tree)
{
    ASSERT_NO_THROW(Tree<int> tree);
}

TEST(Tree, can_create_tree_with_one_element)
{
    ASSERT_NO_THROW(Tree<int> tree(1));
}

TEST(Tree, created_tree_with_true_one_element)
{
    Tree<int> tree(1);
    EXPECT_EQ(1, tree.begin()->data);
}

TEST(Tree, created_element_has_black_color)
{
    Tree<int> tree(1);
    EXPECT_EQ(black, tree.begin()->tcolor);
}

TEST(Tree, true_when_tree_is_empty)
{
    Tree<int> tree;
    EXPECT_EQ(true, tree.isEmpty());
}

TEST(Tree, false_when_tree_is_not_empty)
{
    Tree<int> tree(1);
    EXPECT_NE(true, tree.isEmpty());
}

TEST(Tree, begin_is_nullptr_if_tree_is_empty)
{
    Tree<int> tree;
    EXPECT_EQ(nullptr, tree.begin());
}

TEST(Tree, begin_is_first_node_when_tree_is_not_empty)
{
    Tree<int> tree(1);
    EXPECT_EQ(1, tree.begin()->data);
}

TEST(Tree, can_use_method_size)
{
    Tree<int> tree(1);
    ASSERT_NO_THROW(tree.size());
}

TEST(Tree, method_size_gets_true_size)
{
    Tree<int> tree(1);
    EXPECT_EQ(1, tree.size());
}

TEST(Tree, pushing_increase_size_on_one)
{
    Tree<int> tree(10);
    tree.push(11);
    EXPECT_EQ(2, tree.size());
}

TEST(Tree, pushing_duplicate_dont_increase_size)
{
    Tree<int> tree(10);
    tree.push(10);
    EXPECT_EQ(1, tree.size());
}

TEST(Tree, can_push_root)
{
    Tree<int> tree;
    ASSERT_NO_THROW(tree.push(1));
}

TEST(Tree, pushing_root_true)
{
    Tree<int> tree;
    tree.push(1);
    EXPECT_EQ(1, tree.begin()->data);
}

TEST(Tree, can_push_left_element_with_root_parent)
{
    Tree<int> tree(2);
    ASSERT_NO_THROW(tree.push(1));
}

TEST(Tree, pushing_left_element_with_root_parent_true)
{
    Tree<int> tree(2);
    tree.push(1);
    EXPECT_EQ(1, tree.begin()->left->data);
}

TEST(Tree, pushing_left_element_with_root_parent_true_color)
{
    Tree<int> tree(2);
    tree.push(1);
    EXPECT_EQ(red, tree.begin()->left->tcolor);
}

TEST(Tree, can_push_right_element_with_root_parent)
{
    Tree<int> tree(2);
    ASSERT_NO_THROW(tree.push(3));
}

TEST(Tree, pushing_right_element_with_root_parent_true)
{
    Tree<int> tree(2);
    tree.push(3);
    EXPECT_EQ(3, tree.begin()->right->data);
}

TEST(Tree, pushing_right_element_with_root_parent_true_color)
{
    Tree<int> tree(2);
    tree.push(3);
    EXPECT_EQ(red, tree.begin()->right->tcolor);
}

TEST(Tree, can_push_left_element_with_red_parent_and_red_uncle)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    ASSERT_NO_THROW(tree.push(1));
}

TEST(Tree, pushing_left_element_with_red_parent_and_red_uncle_true)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    tree.push(1);
    EXPECT_EQ(1, tree.begin()->left->left->data);
}

TEST(Tree, pushing_left_element_with_red_parent_and_red_uncle_true_color)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    tree.push(1);
    EXPECT_EQ(red, tree.begin()->left->left->tcolor);
    EXPECT_EQ(black, tree.begin()->right->tcolor);
    EXPECT_EQ(black, tree.begin()->left->tcolor);
}

TEST(Tree, can_push_right_element_with_red_parent_and_red_uncle)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    ASSERT_NO_THROW(tree.push(10));
}

TEST(Tree, pushing_right_element_with_red_parent_and_red_uncle_true)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    tree.push(10);
    EXPECT_EQ(10, tree.begin()->right->right->data);
}

TEST(Tree, pushing_right_element_with_red_parent_and_red_uncle_true_color)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(7);
    tree.push(10);
    EXPECT_EQ(red, tree.begin()->right->right->tcolor);
    EXPECT_EQ(black, tree.begin()->right->tcolor);
    EXPECT_EQ(black, tree.begin()->left->tcolor);
}

TEST(Tree, can_push_left_element_with_red_parent_and_black_uncle)
{
    Tree<int> tree(5);
    tree.push(3);
    ASSERT_NO_THROW(tree.push(1));
}

TEST(Tree, pushing_left_element_with_red_parent_and_black_uncle_true)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(1);
    EXPECT_EQ(1, tree.begin()->left->data);
}

TEST(Tree, pushing_left_element_with_red_parent_and_black_uncle_true_color)
{
    Tree<int> tree(5);
    tree.push(3);
    tree.push(1);
    EXPECT_EQ(black, tree.begin()->tcolor);
    EXPECT_EQ(red, tree.begin()->right->tcolor);
    EXPECT_EQ(red, tree.begin()->left->tcolor);
}

TEST(Tree, can_push_right_element_with_red_parent_and_black_uncle)
{
    Tree<int> tree(5);
    tree.push(7);
    ASSERT_NO_THROW(tree.push(10));
}

TEST(Tree, pushing_right_element_with_red_parent_and_black_uncle_true)
{
    Tree<int> tree(5);
    tree.push(7);
    tree.push(10);
    EXPECT_EQ(10, tree.begin()->right->data);
}

TEST(Tree, pushing_right_element_with_red_parent_and_black_uncle_true_color)
{
    Tree<int> tree(5);
    tree.push(7);
    tree.push(10);
    EXPECT_EQ(black, tree.begin()->tcolor);
    EXPECT_EQ(red, tree.begin()->right->tcolor);
    EXPECT_EQ(red, tree.begin()->left->tcolor);
}

TEST(Tree, can_use_method_search_in_empty_tree)
{
    Tree<int> tree;
    ASSERT_NO_THROW(tree.search(32));
}

TEST(Tree, method_search_in_empty_tree_return_nullptr)
{
    Tree<int> tree;
    EXPECT_EQ(nullptr, tree.search(32));
}

TEST(Tree, can_use_method_search_in_tree)
{
    Tree<int> tree(5);
    ASSERT_NO_THROW(tree.search(5));
}

TEST(Tree, method_search_in_tree_return_true)
{
    Tree<int> tree(5);
    EXPECT_EQ(5, tree.search(5)->data);
}

TEST(Tree, method_search_in_tree_return_nullptr)
{
    Tree<int> tree(5);
    EXPECT_EQ(nullptr, tree.search(50));
}

TEST(Tree, can_delete_node_in_empty_tree)
{
    Tree<int> tree;
    ASSERT_NO_THROW(tree.deleteNode(tree.begin()));
}

TEST(Tree, can_delete_node_in_tree)
{
    Tree<int> tree(4);
    ASSERT_NO_THROW(tree.deleteNode(tree.begin()));
}

TEST(Tree, deleting_node_in_tree_decrease_size_on_one)
{
    Tree<int> tree(5);
    tree.deleteNode(tree.begin());
    EXPECT_EQ(0, tree.size());
}