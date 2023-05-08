#include "gtest.h"
#include "TTable.hpp"


//create
//Могу создать таблицу

//insert
//Могу добавить элемент
TEST(TTable, can_append_data)
{
	TTable<int, std::string> tTable;

	ASSERT_NO_THROW(tTable.insert(0,"0"));
	ASSERT_NO_THROW(tTable.insert(1, "1"));
	ASSERT_NO_THROW(tTable.insert(5, "5"));
}

//Не могу добавить данные с одинаковыми ключами
TEST(TTable, can_not_append_data_with_the_same_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_ANY_THROW(tTable.insert(5,"5"));
}

//finde
//Могу найти элемент по существующему ключу
TEST(TTable, can_finde_data_by_existing_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_NO_THROW(tTable.find(5));
}

//Найденный элемент хранит верные данные
TEST(TTable, found_element_contains_correct_data)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_EQ(tTable.find(5),"5");
}

//Поиск по не существующему ключу приводит к ошибке
TEST(TTable, finde_by_non_exist_key_throw_exception)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_ANY_THROW(tTable.find(6));
}

//remove
//Могу удалить элемент по существующему ключу
TEST(TTable, can_delete_data_by_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_NO_THROW(tTable.remove(1));
}

//Удаляемый элемент удаляется
TEST(TTable, data_really_deliting)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");
	tTable.remove(1);

	ASSERT_ANY_THROW(tTable.find(1));
}

//Удаление по не существующему ключу не приводит к ошибке
TEST(TTable, delete_by_non_exist_key_not_throw_exception)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");
	tTable.remove(3);
}