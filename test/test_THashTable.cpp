#include "gtest.h"
#include "THashTable.hpp"

//create
//���� ������� �������

//insert
//���� �������� �������
TEST(THashTable, can_append_data)
{
	THashTable<string, int> tbl(11);
	ASSERT_NO_THROW(tbl.insert("1",1));
}

//�� ���� �������� ������� � ����������� �������
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

//�� ���� �������� ������ � ����������� �������
TEST(THashTable, can_not_append_data_with_the_same_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_ANY_THROW(tbl.insert("1", 5));
}

//finde
//���� ����� ������� �� ������������� �����
TEST(THashTable, can_finde_data_by_existing_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.find("2"));
}

//��������� ������� ������ ������ ������
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

//����� �� �� ������������� ����� �������� � ������
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
//���� ������� ������� �� ������������� �����
TEST(THashTable, can_delete_data_by_key)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.remove("3"));
}

//��������� ������� ���������
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

//�������� �� �� ������������� ����� �� �������� � ������
TEST(THashTable, delete_by_non_exist_key_not_throw_exception)
{
	THashTable<string, int> tbl(5);

	ASSERT_NO_THROW(tbl.insert("1", 1));
	ASSERT_NO_THROW(tbl.insert("2", 2));
	ASSERT_NO_THROW(tbl.insert("3", 3));
	ASSERT_NO_THROW(tbl.insert("4", 4));

	ASSERT_NO_THROW(tbl.remove("5"));
}