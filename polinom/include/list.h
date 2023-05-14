#pragma once

#include <iostream>

using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node() :data()
	{
		next = nullptr;
		prev = nullptr;
	}
};

template<class T>
class List
{
public:
	Node<T>* head;
	int size;
	List() :head(nullptr), size(0) {}
	friend ostream& operator<<(ostream& os, const List& p)
	{
		Node<T>* tmp = p.head;
		for (; tmp != nullptr; tmp = tmp->next)
		{
			cout << tmp->data << " + ";
		}
		return os;
	}
	~List()
	{
		Node<T>* ptr = head;
		while (ptr != nullptr)
		{
			head = ptr->next;
			delete ptr;
			ptr = head;
		}
	}
	void Delete_el()
	{
		Node<T>* ptr = head;
		while (ptr != nullptr)
		{
			head = ptr->next;
			delete ptr;
			ptr = head;
		}
		head = nullptr;
		size = 0;
	}
	Node<T>* Root()
	{
		return head;
	}
	int Size()
	{
		return size;
	}
	void Insert(T M)
	{
		Node<T>* A = new Node<T>;
		A->data = M;
		if (size == 0)
		{
			head = A;
		}
		else
		{
			Node<T>* pos = nullptr;
			Node<T>* ptr = head;
			if (M > head->data)
			{
				head->prev = A;
				A->next = head;
				head = A;
			}
			else
			{
				while ((ptr->data >= M) && (ptr->next != nullptr))
				{
					ptr = ptr->next;
				}
				if (ptr->next != nullptr)
				{
					pos = ptr->prev;
					A->next = pos->next;
					pos->next->prev = A;
					pos->next = A;
					A->prev = pos;
				}
				else
				{
					ptr->next = A;
					A->prev = ptr;
				}
			}
		}
		size++;
	}
	void Delete(T M)
	{
		int k = 0;
		Node<T>* temp;
		Node<T>* _temp;
		temp = head;
		while (k < size)
		{
			if (k == 0)
			{
				if (temp->data == M)
				{
					temp->next->prev = nullptr;
					temp = temp->next;
					delete head;
					head = temp;
					size--;
					return;
				}
			}
			else
			{
				if (temp->data == M)
				{
					_temp = temp;
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
					delete _temp;
					size--;
					return;
				}
			}
			temp = temp->next;
			k++;
		}
	}
	void Sort(Node<T>* p1, Node<T>* p2)
	{
		p1->data = p1->data + p2->data;
		p1->next = p2->next;
		if (p2->next != nullptr)
		{
			p2->next->prev = p1;
		}
		delete p2;
		size--;
	}
};