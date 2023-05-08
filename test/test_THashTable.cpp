#include "gtest.h"
#include "THashTable.hpp"

//create
//Могу создать таблицу

//insert
//Могу добавить элемент
TEST(THashTable, can_append_data)
{
	THashTable<string, int> tbl(11);
	ASSERT_NO_THROW(tbl.insert("1",1));
}

//Не могу добавить элемент в заполненную таблицу
TEST(THashTable, can_not_append_data_to_full_table)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));
	ASSERT_NO_THROW(tbl.insert("5", 5));

	ASSERT_ANY_THROW(tbl.insert("5", 5));
}

//Не могу добавить данные с одинаковыми ключами
TEST(THashTable, can_not_append_data_with_the_same_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_ANY_THROW(tbl.insert("1", 5));
}

//finde
//Могу найти элемент по существующему ключу
TEST(THashTable, can_finde_data_by_existing_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.find("2"));
}

//Найденный элемент хранит верные данные
TEST(THashTable, found_element_contains_correct_data)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_EQ(tbl.find("1"), 1);
	ASSERT_EQ(tbl.find("2"),2);
	ASSERT_EQ(tbl.find("3"), 3);
	ASSERT_EQ(tbl.find("4"), 4);
}

//Поиск по не существующему ключу приводит к ошибке
TEST(THashTable, finde_by_non_exist_key_throw_exception)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_ANY_THROW(tbl.find("5"));
}

//remove
//Могу удалить элемент по существующему ключу
TEST(THashTable, can_delete_data_by_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.remove("3"));
}

//Удаляемый элемент удаляется
TEST(THashTable, data_really_deliting)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.remove("3"));
	ASSERT_ANY_THROW(tbl.find("3"));
}

//Удаление по не существующему ключу не приводит к ошибке
TEST(THashTable, delete_by_non_exist_key_not_throw_exception)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.remove("5"));
}