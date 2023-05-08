#include "gtest.h"
#include "TTable.hpp"


//create
//���� ������� �������

//insert
//���� �������� �������
TEST(TTable, can_append_data)
{
	TTable<int, std::string> tTable;

	ASSERT_NO_THROW(tTable.insert(0,"0"));
	ASSERT_NO_THROW(tTable.insert(1, "1"));
	ASSERT_NO_THROW(tTable.insert(5, "5"));
}

//�� ���� �������� ������ � ����������� �������
TEST(TTable, can_not_append_data_with_the_same_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_ANY_THROW(tTable.insert(5,"5"));
}

//finde
//���� ����� ������� �� ������������� �����
TEST(TTable, can_finde_data_by_existing_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_NO_THROW(tTable.find(5));
}

//��������� ������� ������ ������ ������
TEST(TTable, found_element_contains_correct_data)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_EQ(tTable.find(5),"5");
}

//����� �� �� ������������� ����� �������� � ������
TEST(TTable, finde_by_non_exist_key_throw_exception)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_ANY_THROW(tTable.find(6));
}

//remove
//���� ������� ������� �� ������������� �����
TEST(TTable, can_delete_data_by_key)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");

	ASSERT_NO_THROW(tTable.remove(1));
}

//��������� ������� ���������
TEST(TTable, data_really_deliting)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");
	tTable.remove(1);

	ASSERT_ANY_THROW(tTable.find(1));
}

//�������� �� �� ������������� ����� �� �������� � ������
TEST(TTable, delete_by_non_exist_key_not_throw_exception)
{
	TTable<int, std::string> tTable;

	tTable.insert(0, "0");
	tTable.insert(1, "1");
	tTable.insert(5, "5");
	tTable.remove(3);
}