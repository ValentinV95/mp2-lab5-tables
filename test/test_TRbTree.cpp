#include "gtest.h"
#include "TRbTree.hpp"
#include "TRbTreeTable.hpp"

//TREE TESTS
//create
//Могу создать таблицу
TEST(TRbTree, can_create_tree)
{
	ASSERT_NO_THROW(TRbTree<int> rbTree);
}

//insert
//Могу добавить элемент
TEST(TRbTree, can_append_data)
{
	TRbTree<int> rbTree;

	ASSERT_NO_THROW(rbTree.insert(1));
	ASSERT_NO_THROW(rbTree.insert(7));
	ASSERT_NO_THROW(rbTree.insert(11));
	ASSERT_NO_THROW(rbTree.insert(42));
	ASSERT_NO_THROW(rbTree.insert(9));
	ASSERT_NO_THROW(rbTree.insert(0));
	ASSERT_NO_THROW(rbTree.insert(18));
	ASSERT_NO_THROW(rbTree.insert(21));
	ASSERT_NO_THROW(rbTree.insert(3));
	ASSERT_NO_THROW(rbTree.insert(14));
}

//Не могу добавить данные с одинаковыми ключами
TEST(TRbTree, can_not_append_data_with_the_same_key)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	ASSERT_ANY_THROW(rbTree.insert(1));
}

//finde
//Могу найти элемент по существующему ключу
TEST(TRbTree, can_finde_data_by_existing_key)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(5);

	ASSERT_NO_THROW(rbTree.find(1));
}

//Найденный элемент хранит верные данные
TEST(TRbTree, found_element_contains_correct_data)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(2);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_EQ(rbTree.find(3),3);
}

//Поиск по не существующему ключу приводит к ошибке
TEST(TRbTree, finde_by_non_exist_key_throw_exception)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_ANY_THROW(rbTree.find(5));
}

//remove
//Могу удалить элемент по существующему ключу
TEST(TRbTree, can_delete_data_by_key)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.remove(5));
}

//Удаляемый элемент удаляется
TEST(TRbTree, data_really_deliting)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	rbTree.remove(5);
	ASSERT_ANY_THROW(rbTree.find(5));
}

//Удаление по не существующему ключу не приводит к ошибке
TEST(TRbTree, delete_by_non_exist_key_not_throw_exception)
{
	TRbTree<int> rbTree;

	rbTree.insert(1);
	rbTree.insert(3);
	rbTree.insert(10);

	ASSERT_NO_THROW(rbTree.remove(6));
}

//TABLE TESTS

//create
//Могу создать таблицу

//insert
//Могу добавить элемент
TEST(TRbTreeTable, can_append_data)
{
	TRbTreeTable<int, std::string> tbl;

	ASSERT_NO_THROW(tbl.insert(0,"0"));
	ASSERT_NO_THROW(tbl.insert(1, "1"));
	ASSERT_NO_THROW(tbl.insert(2, "2"));
	ASSERT_NO_THROW(tbl.insert(6, "6"));
}

//Не могу добавить данные с одинаковыми ключами
TEST(TRbTreeTable, can_not_append_data_with_the_same_key)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_ANY_THROW(tbl.insert(0, "0"));
	ASSERT_ANY_THROW(tbl.insert(6, "6"));
}

//finde
//Могу найти элемент по существующему ключу
TEST(TRbTreeTable, can_finde_data_by_existing_key)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_NO_THROW(tbl.find(2));
}

//Найденный элемент хранит верные данные
TEST(TRbTreeTable, found_element_contains_correct_data)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_EQ(tbl.find(2),"2");
}

//Поиск по не существующему ключу приводит к ошибке
TEST(TRbTreeTable, finde_by_non_exist_key_throw_exception)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_ANY_THROW(tbl.find(5));
}

//remove
//Могу удалить элемент по существующему ключу
TEST(TRbTreeTable, can_delete_data_by_key)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_NO_THROW(tbl.remove(1));
}

//Удаляемый элемент удаляется
TEST(TRbTreeTable, data_really_deliting)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");
	tbl.remove(1);

	ASSERT_ANY_THROW(tbl.find(1));
}

//Удаление по не существующему ключу не приводит к ошибке
TEST(TRbTreeTable, delete_by_non_exist_key_not_throw_exception)
{
	TRbTreeTable<int, std::string> tbl;

	tbl.insert(0, "0");
	tbl.insert(1, "1");
	tbl.insert(2, "2");
	tbl.insert(6, "6");

	ASSERT_NO_THROW(tbl.remove(7));
}