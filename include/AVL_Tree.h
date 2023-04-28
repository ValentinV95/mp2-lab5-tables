#pragma once
#include <iostream>
#include <stack>
#include <iomanip>
#include "../polinom/include/polinom.h"
#define uchar unsigned char

template <typename T>
class Sorting_table {
private:
	struct Node
	{
		std::string key;
		T value;
		Node* parent;
		Node* left;
		Node* right;
		uchar height;

		Node(std::string key, T data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, uchar dsb = '0')
		{
			this->key = key;
			this->value = data;
			this->parent = parent;
			this->left = left;
			this->right = right;
			this->height = dsb;
		}
	};

	Node *root;
	int size;

public:
	/*--------------------����� � �������-----------------------*/
	class iterator {
	private:
		Node* ptr;
	public:
		iterator() {}

		iterator(Node* p)
		{
			ptr = p;
		}

		iterator& operator++(int) {
			if (ptr->right != nullptr) {
				ptr = ptr->right;
				while (ptr->left != nullptr)
				{
					ptr = ptr->left;
				}
			}
			else {
				Node* tmp = ptr->parent;
				while (tmp != nullptr && ptr == tmp->right) {
					ptr = tmp;
					tmp = tmp->parent;
				}
				ptr = tmp;
			}
			return *this;
		}

		Node* operator*()
		{
			return ptr;
		}

		bool operator==(const Node* second) const
		{
			return ((ptr->key == second->key) && (ptr->value == second->value));
		}

		bool operator!=(const Node* second) const
		{
			return !(ptr == second);
		}

		~iterator() { delete ptr; }
	};

	Node* begin() const
	{
		if (root == nullptr)
			return nullptr;
		Node* a = root;
		while (a->left != nullptr)
			a = a->left;
		return a;
	}

	Node* end() const
	{
		return nullptr;
	}
	/*----------------------------------------------------------*/

	Sorting_table()
	{
		root = nullptr;
		size = 0;
		std::cout << "LOG: Sorting table construct" << std::endl;
	}

	Node* getRoot()
	{
		return root;
	}

	void insert(std::string key, T data, int& log_count)  //right - max, left - min
	{
		Node* prev = root;
		bool flag_right = true;
		Node *tmp = root;
		if (root == nullptr)
		{
			log_count++;
			root = new Node(key, data);
		}
		else
		{
			while (tmp != nullptr)
			{
				log_count++;
				if (tmp->left != nullptr || tmp->right != nullptr)
				{
					log_count++;
					tmp->height = tmp->height + 1;
				}
				if (key > tmp->key)
				{
					log_count++;
					prev = tmp;
					tmp = tmp->right;
				}
				else if (key < tmp->key)
				{
					log_count++;
					prev = tmp;
					tmp = tmp->left;
					flag_right = false;
				}
				else
				{
					throw std::exception("ERROR: this name already used");
				}
			}

			tmp = new Node(key, data, prev);

			balance(root, log_count);

			if (flag_right)
			{
				log_count++;
				prev->right = tmp;
			}
			else
			{
				log_count++;
				prev->left = tmp;
			}
		}
		size++;
	}

	/*-------------------------������������ ������---------------------------------*/
	int balanceFactor(Node* ptr)
	{
		int hl;
		int hr;
		if (ptr->left == nullptr)
			hl = 0;
		else
			hl = ptr->left->height;

		if (ptr->right == nullptr)
			hr = 0;
		else
			hr = ptr->right->height;

		return (hl - hr);
	}

	void balance(Node* ptr, int& log_count)
	{
		if (balanceFactor(ptr) == 2)
		{
			std::cout << "RotateLeft";
			log_count++;
			if (balanceFactor(ptr->left) > 0)
			{
				log_count++;
				rotateLeft(ptr->left);
			}
			return rotateRight(ptr);
		}
		else if (balanceFactor(ptr) == -2)
		{
			std::cout << "RotateRight";
			log_count++;
			if (balanceFactor(ptr->right) < 0)
			{
				log_count++;
				rotateRight(ptr->right);
			}
			return rotateLeft(ptr);
		}
		else {}
	}

	void fixHeight(Node* ptr)
	{
		uchar h_left = ptr->left ? ptr->left->height : 0;
		uchar h_right = ptr->right ? ptr->right->height : 0;
		if (h_left > h_right)
			ptr->height = h_left + 1;
		else
			ptr->height = h_right + 1;
	}

	void rotateRight(Node* ptr)
	{
		Node* new_root = ptr->left;
		if (ptr->parent == nullptr)
			root = new_root;
		ptr->parent = new_root;
		ptr->left = new_root->right;
		new_root->right = ptr;
		fixHeight(ptr);
		fixHeight(new_root);
	}

	void rotateLeft(Node* ptr)
	{
		Node* new_root = ptr->right;
		if (ptr->parent == nullptr)
			root = new_root;
		ptr->parent = new_root;
		ptr->right = new_root->left;
		new_root->left = ptr;
		fixHeight(ptr);
		fixHeight(new_root);
	}

	void bigRotateRight(Node* ptr)
	{
		rotateRight(ptr->right);
		rotateLeft(ptr);
	}

	void bigRotateLeft(Node* ptr)
	{
		rotateLeft(ptr->left);
		rotateRight(ptr);
	}
	/*--------------------------------------------------------------------------------*/

	/*----------------------------------�������������� � ��������--------------------------------------------*/
	void Add(std::string key, T value)
	{
		if (Search(key) != nullptr)
			throw std::exception("this name already using");
		int log_comparison = 0;
		this->insert(key, value, log_comparison);
		std::cout << "LOG: polinom  ";
		value.show();
		std::cout << " with name '" << key << "' added in non sort table" << std::endl;
		std::cout << "LOG: made " << log_comparison << " comparison in AVL Tree(if)" << std::endl;
	}

	Node* AVLSearch(std::string current_key, int& log_count) //������������ �������
	{
		Node* tmp = root;
		while (tmp != nullptr)
		{
			log_count++;
			if (current_key > tmp->key)
			{
				log_count++;
				tmp = tmp->right;
			}
			else if (current_key < tmp->key)
			{
				log_count++;
				tmp = tmp->left;
			}
			else
				return tmp;
		}
		return nullptr;
	}

	Node* Search(std::string current_key)
	{
		int log_comparison = 0;
		Node* tmp = AVLSearch(current_key, log_comparison);
		if (tmp == nullptr)
		{
			std::cout << "LOG: This key not in table" << std::endl;
			std::cout << "LOG: made " << log_comparison << " comparison in AVL Tree(if)" << std::endl;
			return nullptr;
		}
		std::cout << "LOG: polinom ";
		tmp->value.show();
		std::cout << " with name " << tmp->key << "found" << std::endl;
		std::cout << "LOG: made " << log_comparison << " transition in array(++)" << std::endl;
		return tmp;
	}

	Node* minNode(Node* root_subtree)
	{
		Node* i = root_subtree;
		for (; i != nullptr; i = i->left) {}

		return i;
	}

	void Extract(std::string current_key)
	{
		int log_comparison = 0;
		Node* curr_ptr = AVLSearch(current_key, log_comparison);
		Node* p = curr_ptr->parent;
		if (curr_ptr != nullptr)
		{
			log_comparison++;
			if (curr_ptr->left == nullptr && curr_ptr->right == nullptr)
			{
				log_comparison++;
				delete curr_ptr;
				curr_ptr = nullptr;
			}
			else if (curr_ptr->left == nullptr || curr_ptr->right == nullptr)
			{
				log_comparison++;
				Node* p = curr_ptr->parent;
				Node* child = curr_ptr->left;
				if (curr_ptr->left == nullptr)
					child = curr_ptr->right;
				log_comparison++;
				if (child->key > p->key)
					p->right = child;
				else
					p->left = child;

				log_comparison++;
				child->parent = p;

				delete curr_ptr;
			}
			else
			{
				log_comparison++;
				Node* p = curr_ptr->parent;
				Node* child_r = curr_ptr->right;
				Node* child_l = curr_ptr->left;
				Node* minimum = minNode(child_r);
				if (minimum->key > p->key)
					p->right = minimum;
				else
					p->left = minimum;
				minimum->parent = p;
				minimum->left = child_l;
				minimum->right = child_r;
				log_comparison++;
				delete curr_ptr;
			}

			for (Node* tmp = p->parent; p->parent != nullptr; tmp = tmp->parent)
			{
				log_comparison++;
				fixHeight(p);
			}

			balance(p, log_comparison);
		}
	}
	/*-------------------------------------------------------------------------------------------------------*/

	/*---------------------------------����� ������� � �������-----------------------------------------------*/
	void show()
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(20) << std::left << "| NAME" << "| POLINOM" << std::endl;
		for (iterator it = begin(); it != end(); it++)
		{
			show(*it);
		}
	}

	void show(Node* t)
	{
		std::cout << std::string(60, '-') << std::endl;
		std::cout << std::setw(20) << std::left << "| " + t->key;
		std::cout << "| ";
		t->value.show();
		//std::cout << '\t' << t->height << '\n';
		std::cout << std::string(60, '-') << std::endl;
	}

	~Sorting_table()
	{
		for (iterator it = begin(); it != end(); )
			if ((*it)->left == nullptr && (*it)->right == nullptr)
			{
				Node* tmp = (*it);
				it++;
				delete tmp;
			}
			else
			{
				it++;
			}
	}
};