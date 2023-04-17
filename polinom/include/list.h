#pragma once
#include <stdexcept>

//Упорядоченный по возрастанию односвязный список
//Первый элемент фиктивный, последний указывает на nullptr
template <class T>
class TSortedList
{
	struct Node
	{
		T data;
		Node* next;
		Node(T data, Node* next = nullptr) :data(data), next(next) {}
	};

	Node* head = new Node(T());
	Node* tail = head;
public:
	TSortedList() {}

	TSortedList(const TSortedList& lst)
	{
		Node* current_other = lst.head->next;
		Node* current_this = head;

		while (current_other != nullptr)
		{
			current_this->next = new Node(current_other->data);

			current_this = current_this->next;
			tail = current_this;
			current_other = current_other->next;
		}
	}

	void Append(T data)
	{
		//Find the list item following which is less than the date
		Node* current = head;
		while (current->next != nullptr && current->next->data < data)
			current = current->next;

		//Append en element to list
		if (current->next == nullptr)
		{
			current->next = new Node(data);
			tail = current->next;
		}
		else
		{
			current->next = new Node(data, current->next);
		}
	}

	void Push_Back(T data)
	{
		if (tail->data > data && tail!=head)
			throw std::invalid_argument("Inserting an item at the end of the list breaks the order");

		tail->next = new Node(data);
		tail = tail->next;
	}

	T At(int indx)
	{
		int i = 0;
		Node* current = head->next;
		while (i < indx && current != nullptr)
		{
			current = current->next;
			i++;
		}

		if (i == indx)
			return current->data;
		else
			throw std::out_of_range("Index out of a range");
	}

	TSortedList operator =(const TSortedList& other)
	{
		if (this == &other)
			return *this;

		while (head != nullptr)
		{
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}

		head = new Node(T());
		tail = head;

		Node* cur_node = head;
		for (auto iter = other.begin(); iter != other.end(); iter++)
		{
			cur_node->next = new Node((*iter));
			cur_node = cur_node->next;
			tail = cur_node->next;
		}

		return *this;
	}

	~TSortedList()
	{
		while (head != nullptr)
		{
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}
	}

	class Iterator
	{
		Node* current;
	public:
		Iterator(Node* node) :current(node) {}

		Iterator(const Iterator& iter) { current = iter.current; }

		bool operator != (const Iterator& iter) { return iter.current != current; }

		bool operator == (const Iterator& iter) { return iter.current == current; }

		T& operator * () { return (*current).data; }

		Iterator operator ++(int)
		{
			Iterator tmp = *this;

			if (current != nullptr)
				current = current->next;
			else
				throw std::out_of_range("The end of the list has been reached");

			return tmp;
		}
	};

	Iterator begin() const { return head->next; }

	Iterator end() const { return nullptr; }
};