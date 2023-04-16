#pragma once

#include <iostream>

using namespace std;

template<class T>
struct Node
{
	T data;
	Node<T>* next;

	Node() : data(T()), next(nullptr) {}

	Node(T var) : data(var), next(nullptr) {}
};

template<class T>
class List
{
private:
	Node<T>* head;
	size_t tsize;

public:

	List() : head(new Node<T>()), tsize(0)
	{}

	List(const T& var) : head(new Node<T>()), tsize(1)
	{
		head->next = new Node<T>(var);
	}

	List(const List& other) : head(new Node<T>()), tsize(other.tsize)
	{
		Node<T>* o = other.head->next;
		Node<T>* t = this->head;

		while (o)
		{
			t->next = new Node<T>(o->data);
			t = t->next;
			o = o->next;
		}
	}

	~List()
	{
		clear();

		delete head;
		head = nullptr;
	}

	Node<T>* begin() const
	{
		return head->next;
	}

	bool isEmpty() const
	{
		return head->next == nullptr;
	}

	size_t size() const
	{
		return tsize;
	}

	void push(const T& var)
	{
		if (isEmpty())
		{ 
			head->next = new Node<T>(var);
		}

		else
		{
			Node<T>* temp = head;

			while (temp->next && temp->next->data < var)
			{
				temp = temp->next;
			}

			if (temp->next == nullptr)
			{
				temp->next = new Node<T>(var);
			}

			else
			{
				Node<T>* cont = temp->next;
				temp->next = new Node<T>(var);
				temp->next->next = cont;
			}
		}

		tsize++;
	}

	void deleteNode(Node<T>* node)
	{
		if (!isEmpty())
		{
			Node<T>* temp = head;

			while (temp && temp->next != node)
			{
				temp = temp->next;
			}

			if (temp)
			{
				Node<T>* cont = node->next;
				delete temp->next;
				temp->next = cont;
				tsize--;
			}
		}
	}

	void clear()
	{
		if (!isEmpty())
		{
			Node<T>* pointer = head->next;
			Node<T>* temp;

			while (pointer)
			{
				temp = pointer;
				pointer = pointer->next;
				delete temp;
			}

			head->next = nullptr;
			tsize = size_t(0);
		}
	}

	bool operator ==(const List& other) const 
	{
		if (this->tsize == other.tsize)
		{
			if (this->isEmpty())
			{
				return true;
			}

			else
			{
				Node<T>* t = this->head->next;
				Node<T>* o = other.head->next;

				while (t)
				{
					if (t->data != o->data) return false;
					t = t->next;
					o = o->next;
				}

				return true;
			}
		}

		return false;
	}

	bool operator !=(const List& other) const
	{
		return !(*this == other);
	}

	const List& operator =(const List& other)
	{
		if (*this != other)
		{	
			this->clear();

			Node<T>* o = other.head->next;
			Node<T>* t = this->head;

			while (o)
			{
				t->next = new Node<T>(o->data);
				this->tsize++;
				o = o->next;
				t = t->next;
			}
		}

		return *this;
	}

	void merge(const List& other)
	{
		if (other.isEmpty()) return;

		List<T> third;
		Node<T>* t = this->head->next;
		Node<T>* o = other.head->next;
		Node<T>* th = third.head;

		while (t || o)
		{
			if (t && ((o == nullptr) || (t->data <= o->data)))
			{
				th->next = new Node<T>(t->data);
				t = t->next;
			}

			else
			{
				th->next = new Node<T>(o->data);
				o = o->next;
			}

			th = th->next;
			third.tsize++;
		}

		*this = third;
	}
};