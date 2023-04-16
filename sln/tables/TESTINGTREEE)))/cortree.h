#pragma once
#include <iostream>

namespace Cormen
{
	enum Color
	{
		black = 0,
		red = 1
	};

	template <class T>
	struct Node
	{
		T data;
		Node<T>* left;
		Node<T>* right;
		Node<T>* parent;
		char color;

		Node() : data(T()), left(nullptr), right(nullptr), parent(nullptr), color(red)
		{}

		Node(const T& var) : data(var), left(nullptr), right(nullptr), parent(nullptr), color(red)
		{}

		void getNode() const
		{
			std::cout << "(" << data << ", " << (color ? "red" : "black") << ")";
		}
	};

	template<class T>
	class Tree
	{
	private:
		Node<T>* root;
		size_t tsize;
		std::vector<int> map_of_tree;
	public:
		Tree() : root(nullptr), tsize(0)
		{}

		size_t size() const
		{
			return tsize;
		}

		bool isEmpty() const
		{
			return root == nullptr;
		}

		Node<T>* begin() const
		{
			return this->root;
		}

		void show()
		{
			map_of_tree.clear();
			print(this->root, 0);
			std::cout << std::endl << std::endl;
		}

		void print(Node<T>* cur, int n)
		{
			if (cur)
			{
				for (size_t i = 0; i < n; i++)
				{
					if (i == (n - 1))
					{
						std::cout << "|---";
					}

					else
					{
						std::cout << (map_of_tree[i] ? "|" : "  ") << "   ";
					}
				}

				cur->getNode();
				std::cout << std::endl;
				map_of_tree.push_back(1);
				print(cur->left, n + 1);
				map_of_tree[n] = 0;
				print(cur->right, n + 1);
			}
		}

		bool isValidRBTree()
		{
			// ѕустые деревь€ также €вл€ютс€ красными и черными деревь€ми
			if (nullptr == this->root)
				return  true;
			if (this->root->color != black) {
				std::cout << "ѕрирода 1: корневой узел не черный";
				return false;
			}
			// ѕолучаем количество узлов на одном пути
			int blackCount = 0;
			Node<T>* cur = this->root;
			while (nullptr != cur) {
				if (cur->color == black)
					blackCount++;
				cur = cur->left;
			}
			// ќсобый метод проверки
			return _isValidRBtree(this->root, 0, blackCount);
		}

		bool _isValidRBtree(Node<T>* temp, int pathCount, int blackCount) {
			if (nullptr == temp)
				return true;
			// ¬стречаем черный узел, подсчитываем количество черных узлов на текущем пути
			if (temp->color == black)
				pathCount++;
			// характер проверки три
			Node<T>* parent = temp->parent;
			if (parent != nullptr && parent->color == red && temp->color == red) {
				std::cout << "Ќарушение природы 3: красные узлы соединены вместе";
				return true;
			}
			// ѕроверка 4
			// ≈сли это листовой узел, путь дошел до конца, провер€ем, совпадает ли общее количество черных узлов в пути с предыдущей статистикой
			if (temp->left == nullptr && temp->right == nullptr) {
				if (pathCount != blackCount) {
					std::cout << "ѕрирода 4: Ќесогласованный формат черных узлов на пути";
					return false;
				}
			}
			// –екурсивное определение левого и правого поддеревьев корн€
			return _isValidRBtree(temp->left, pathCount, blackCount) &&
				_isValidRBtree(temp->right, pathCount, blackCount);
		}

		void leftRotate(Node<T>* cur)
		{
			if (cur->right)
			{
				Node<T>* temp = cur->right;
				cur->right = temp->left;
				if (temp->left) temp->left->parent = cur;
				temp->parent = cur->parent;
				if (!cur->parent) this->root = temp;
				else if (cur == cur->parent->left) cur->parent->left = temp;
				else cur->parent->right = temp;
				temp->left = cur;
				cur->parent = temp;
			}
		}

		void rightRotate(Node<T>* cur)
		{
			if (cur->left)
			{
				Node<T>* temp = cur->left;
				cur->left = temp->right;
				if (temp->right) temp->right->parent = cur;
				temp->parent = cur->parent;
				if (!cur->parent) this->root = temp;
				else if (cur == cur->parent->right) cur->parent->right = temp;
				else cur->parent->left = temp;
				temp->right = cur;
				cur->parent = temp;
			}
		}

		void insert(const T& var)
		{
			Node<T>* newNode = new Node<T>(var);
			Node<T>* ptr1 = this->root;
			Node<T>* ptr2 = nullptr;

			while (ptr1)
			{
				ptr2 = ptr1;
				if (var < ptr1->data) ptr1 = ptr1->left;
				else ptr1 = ptr1->right;
			}
			
			newNode->parent = ptr2;

			if (!ptr2) this->root = ptr2;
			else if (var < ptr2->data) ptr2->left = newNode;
			else ptr2->right = newNode;
		}

		void insertBalance(Node<T>* cur)
		{
			while (cur->parent->color == red)
			{
				if (cur->parent == cur->parent->parent->left) {}
			}
		}
	};
};