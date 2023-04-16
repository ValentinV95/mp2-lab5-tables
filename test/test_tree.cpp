#include <gtest.h>
//#include "tree.h"

//TEST(Tree, can_create_tree)
//
    //ASSERT_NO_THROW(Tree<int> tree);
//}

/*TEST(Tree, can_create_tree_with_one_element)
{
    ASSERT_NO_THROW(Tree<int> tree(1));
}

TEST(Tree, created_tree_with_true_one_element)
{
    Tree<int> tree(1);
    EXPECT_EQ(1, tree.begin()->data);
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
}*/

/*TEST(Tree, can_copy_empty_list)
{
    List<int> list;
    ASSERT_NO_THROW(List<int> list1(list));
}

TEST(List, can_copy_list_with_one_element)
{
    List<int> list(1);
    ASSERT_NO_THROW(List<int> list1(list));
}

TEST(List, copied_list_with_one_element_has_true_size)
{
    List<int> list(1);
    List<int> list1(list);
    EXPECT_EQ(1, list1.size());
}

TEST(List, copied_list_with_one_element_is_true)
{
    List<int> list(1);
    List<int> list1(list);
    EXPECT_EQ(1, list1.begin()->data);
}

TEST(List, copied_list_with_one_element_with_own_memory)
{
    List<int> list(1);
    List<int> list1(list);
    list1.begin()->data = 2;
    EXPECT_EQ(1, list.begin()->data);
}

TEST(List, can_copy_list_with_elements)
{
    List<int> list;
    for (int i = 0; i < 10; i++)
    {
        list.push(i);
    }
    ASSERT_NO_THROW(List<int> list1(list));
}

TEST(List, copied_list_with_elements_has_true_size)
{
    List<int> list;

    for (int i = 10; i > -1; i--)
        list.push(i);

    List<int> list1(list);
    EXPECT_EQ(11, list1.size());
}

TEST(List, copied_list_with_elements_is_true)
{
    List<int> list;

    for (int i = 10; i > -1; i--)
        list.push(i);

    List<int> list1(list);
    Node<int>* temp = list1.begin();
    for (size_t i = 0; i < list.size(); i++, temp = temp->next)
        EXPECT_EQ(i, temp->data);
}

TEST(List, copied_list_with_elements_with_own_memory)
{
    List<int> list;

    for (int i = 10; i > -1; i--)
        list.push(i);

    List<int> list1(list);
    Node<int>* o = list1.begin();
    Node<int>* t = list.begin();

    for (size_t i = 0; i < list.size(); i++, o = o->next, t = t->next)
    {
        t->data = 5;
        EXPECT_EQ(i, o->data);
    }
}
*/
/*TEST(List, can_use_method_clear)
{
    List<int> list(1);
    ASSERT_NO_THROW(list.clear());
}

TEST(List, method_clear_changes_size_to_zero)
{
    List<int> list(1);
    list.clear();
    EXPECT_EQ(0, list.size());
}

TEST(List, method_clear_changes_tail_to_nullptr)
{
    List<int> list(1);
    list.clear();
    EXPECT_EQ(1, list.isEmpty());
}
*/
/*TEST(List, can_use_operator_equal_list_to_itself)
{
    List<int> list(2);
    ASSERT_NO_THROW(list == list);
}

TEST(List, using_operator_equal_list_to_itself_true)
{
    List<int> list(2);
    EXPECT_EQ(1, list == list);
}

TEST(List, can_use_operator_equal_empty_list)
{
    List<int> list;
    List<int> list1;
    ASSERT_NO_THROW(list == list1);
}

TEST(List, using_operator_equal_empty_list_true)
{
    List<int> list;
    List<int> list1;
    EXPECT_EQ(1, list == list1);
}

TEST(List, can_use_operator_equal_list_with_one_element)
{
    List<int> list(2);
    List<int> list1(2);
    ASSERT_NO_THROW(list == list1);
}

TEST(List, using_operator_equal_list_with_one_element_true)
{
    List<int> list(2);
    List<int> list1(2);
    EXPECT_EQ(1, list == list1);
}

TEST(List, using_operator_equal_list_with_one_element_false)
{
    List<int> list(3);
    List<int> list1(2);
    EXPECT_EQ(0, list == list1);
}

TEST(List, can_use_operator_equal_list)
{
    List<int> list(2);
    list.push(3);
    List<int> list1(2);
    list1.push(3);
    ASSERT_NO_THROW(list == list1);
}

TEST(List, using_operator_equal_list_true)
{
    List<int> list(2);
    list.push(3);
    List<int> list1(2);
    list1.push(3);
    EXPECT_EQ(1, list == list1);
}

TEST(List, using_operator_equal_list_false)
{
    List<int> list(2);
    list.push(5);
    List<int> list1(2);
    list1.push(3);
    EXPECT_EQ(0, list == list1);
}

TEST(List, using_operator_equal_list_with_other_size_false)
{
    List<int> list(2);
    list.push(3);
    list.push(3);
    List<int> list1(2);
    list1.push(3);
    EXPECT_EQ(0, list == list1);
}

TEST(List, can_use_operator_not_equal_list)
{
    List<int> list(2);
    list.push(3);
    List<int> list1(2);
    list1.push(3);
    ASSERT_NO_THROW(list == list1);
}

TEST(List, using_operator_not_equal_list_true)
{
    List<int> list(2);
    list.push(4);
    List<int> list1(2);
    list1.push(3);
    EXPECT_EQ(1, list != list1);
}

TEST(List, can_assign_list_to_itself)
{
    List<int> list(2);
    ASSERT_NO_THROW(list = list);
}

TEST(List, assign_list_to_itself_do_not_change_data)
{
    List<int> list(2);
    list = list;
    EXPECT_EQ(2, list.begin()->data);
}

TEST(List, can_assign_equal_size_list_with_one_element)
{
    List<int> list(3);
    List<int> list1(2);
    ASSERT_NO_THROW(list = list1);
}

TEST(List, assign_equal_size_list_with_one_element_true)
{
    List<int> list(2);
    List<int> list1(3);
    list = list1;
    EXPECT_EQ(true, list == list1);
}

TEST(List, can_assign_equal_size_list)
{
    List<int> list(3);
    List<int> list1(2);
    ASSERT_NO_THROW(list = list1);
}

TEST(List, assign_equal_size_list_true)
{
    List<int> list(2);
    list.push(4);
    List<int> list1(2);
    list1.push(3);
    list = list1;
    EXPECT_EQ(true, list == list1);
}

TEST(List, can_assign_not_equal_size_list_when_other_list_is_empty)
{
    List<int> list(3);
    List<int> list1;
    ASSERT_NO_THROW(list = list1);
}

TEST(List, assign_not_equal_size_list_when_other_list_is_empty_true)
{
    List<int> list(2);
    List<int> list1;
    list = list1;
    EXPECT_EQ(true, list == list1);
}

TEST(List, can_assign_not_equal_size_list_when_other_list_with_one_element)
{
    List<int> list(2);
    list.push(3);
    List<int> list1(2);
    ASSERT_NO_THROW(list = list1);
}

TEST(List, assign_not_equal_size_list_when_other_list_with_one_element_true)
{
    List<int> list(2);
    list.push(3);
    List<int> list1(2);
    list = list1;
    EXPECT_EQ(true, list == list1);
}

TEST(List, can_assign_not_equal_size_list)
{
    List<int> list(3);
    List<int> list1(2);
    list1.push(4);
    ASSERT_NO_THROW(list = list1);
}

TEST(List, assign_not_equal_size_list_true)
{
    List<int> list(2);
    List<int> list1(2);
    list1.push(3);
    list = list1;
    EXPECT_EQ(true, list == list1);
}

TEST(List, can_merge_two_lists)
{
    List<int> list(2);
    List<int> list1(2);
    ASSERT_NO_THROW(list.merge(list1));
}

TEST(List, merge_two_lists_true)
{
    List<int> list(1);
    list.push(3);
    list.push(4);
    List<int> list1(0);
    list1.push(2);
    list.merge(list1);
    Node<int>* temp = list.begin();
    for (size_t i = 0; i < 5; i++, temp = temp->next)
        EXPECT_EQ(i, temp->data);
}
*/
/*TEST(Tree, can_push_elements)
{
    Tree<int> tree;
    ASSERT_NO_THROW(tree.push(2));
}*/

/*TEST(Tree, push_adds_elements_in_true_order)
{
    Tree<int> tree;
    for (int i = 10; i > -1; i--)
        list.push(i);
    Node<int>* temp = list.begin();
    for (size_t i = 0; i < 10; i++, temp = temp->next)
        EXPECT_EQ(i, temp->data);
}*/

/*TEST(List, can_delete_node)
{
    List<int> list(1);
    list.push(1);
    ASSERT_NO_THROW(list.deleteNode(list.begin()->next));
}

TEST(List, no_throw_if_delete_node_in_empty_list)
{
    List<int> list;
    ASSERT_NO_THROW(list.deleteNode(list.begin()));
}

TEST(List, no_throw_if_delete_node_in_list_with_one_element)
{
    List<int> list;
    ASSERT_NO_THROW(list.deleteNode(list.begin()));
}

TEST(List, true_deleting_first_node_in_list)
{
    List<int> list(1);
    list.deleteNode(list.begin());
    EXPECT_EQ(nullptr, list.begin());
}

TEST(List, true_deleting_node_in_list)
{
    List<int> list(0);
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);
    list.deleteNode(list.begin()->next->next);
    Node<int>* temp = list.begin();
    for (int i = 0; i < list.size(); i++, temp = temp->next)
    {
        if (i < 2) EXPECT_EQ(i, temp->data);
        else EXPECT_EQ(i + 1, temp->data);
    }
}

TEST(List, deleting_node_change_true_size)
{
    List<int> list(1);
    list.deleteNode(list.begin());
    EXPECT_EQ(0, list.size());
}*/