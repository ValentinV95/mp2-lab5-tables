#pragma once

#include <iostream>
#include <queue>
#include "pair.h"

enum Color
{
	black = 0,
	red = 1
};

template<class T>
struct RBNode
{
	unsigned char color;                                                       // 0 - black, 1 - red
	T data;
	RBNode* left;
	RBNode* right;
	RBNode* parent;

	RBNode() : color(red), data(T()), left(nullptr), right(nullptr), parent(nullptr)
	{}

	RBNode(const T& var) : color(red), data(var), left(nullptr), right(nullptr), parent(nullptr)
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
	RBNode<T>* root;
	size_t tsize;
	std::vector<int> map_of_tree;
public:
	void swapData(RBNode<T>* one, RBNode<T>* other)
	{
		T temp = one->data;
		one->data = other->data;
		other->data = temp;
	}

	void swapColor(RBNode<T>* one, RBNode<T>* other)
	{
		unsigned char temp = one->color;
		one->color = other->color;
		other->color = temp;
	}

	Tree() : root(nullptr), tsize(0)
	{}

	Tree(const T& var) : root(new RBNode<T>(var)), tsize(1)
	{}

	~Tree()
	{
		this->clear();
		this->root = nullptr;
	}

	void push(const T& var)
	{
		RBNode<T>* cur = new RBNode<T>(var);

		if (this->isEmpty())                                                   // Вставка корня
		{
			this->root = cur;
		}

		else                                                                   // Вставка не корня
		{
			RBNode<T>* fast = this->root;
			RBNode<T>* slow = nullptr;

			while (fast)
			{
				slow = fast;

				if (var > fast->data)
				{
					if (fast->right)
					{
						fast = fast->right;
					}

					else
					{
						slow->right = cur;
						cur->parent = slow;
						break;
					}
				}

				else if (var < fast->data)
				{
					if (fast->left)
					{
						fast = fast->left;
					}

					else
					{
						slow->left = cur;
						cur->parent = slow;
						break;
					}
				}

				else
				{
					return;
				}
			}
		}

		balancePush(cur);
		this->tsize++;
	}

	RBNode<T>* search(const T& var) const
	{
		RBNode<T>* temp = this->root;

		while (temp)
		{
			if (temp->data > var) temp = temp->left;
			else if (temp->data < var) temp = temp->right;
			else return temp;
		}

		return nullptr;
	}

	void deleteNode(const T& var)
	{
		RBNode<T>* cur = search(var);

		if (cur)
		{
			//balanceDelete(cur);

			RBNode<T>* father = cur->parent;
			this->tsize--;

			if (cur->right == nullptr && cur->left == nullptr)                 // Удаляемый узел не имеет детей
			{
				if (father == nullptr) this->root = nullptr;                   // Удаляемый узел корень
				else if (father->right == cur) father->right = nullptr;        // Удаляемый узел правый ребенок 
				else father->left = nullptr;                                   // Удаляемый узел левый ребенок
			}

			else if (cur->right == nullptr || cur->left == nullptr)            // У удаляемого узла один ребенок
			{
				if (cur->right == nullptr)                                     // У удаляемого узла только левый ребенок
				{
					if (father == nullptr)                                     // Удаляемый узел корень
					{
						this->root = cur->left;
						this->root->parent = nullptr;
					}

					else                                                       // Удаляемый узел есть отец
					{
						cur->left->parent = father;

						if (father->left == cur) father->left = cur->left;
						else father->right = cur->left;
					}
				}

				else                                                           // У удаляемого узла только правый ребенок
				{
					if (father == nullptr)                                     // Удаляемый узел корень
					{
						this->root = cur->right;
						this->root->parent = nullptr;
					}

					else                                                       // У удаляемого узла есть отец
					{
						cur->right->parent = father;

						if (father->left == cur) father->left = cur->right;
						else father->right = cur->right;
					}
				}
			}

			else                                                               // Удаляемый узел имеет двух детей
			{
				RBNode<T>* fast = cur->right;
				RBNode<T>* slow = cur;

				while (fast)
				{
					slow = fast;
					fast = fast->left;
				}

				cur->left->parent = slow;
				slow->left = cur->left;

				if (slow->parent == cur)                                       // Заменяем удаляемый узел на правого ребенка 
				{
					if (father == nullptr)                                     // Удаляемый узел корень
					{
						this->root = slow;
						this->root->parent = nullptr;
					}

					else                                                       // Удаляемый узел не корень
					{
						slow->parent = father;

						if (father->left == cur) father->left = slow;
						else father->right = slow;
					}
				}

				else                                                           // Заменяем на минимального правого потомка
				{
					cur->right->parent = slow;
					slow->parent->left = slow->right;
					if (slow->right) slow->right->parent = slow->parent;
					slow->right = cur->right;

					if (father == nullptr)                                     // Удаляемый узел корень
					{
						this->root = slow;
						this->root->parent = nullptr;
					}

					else                                                       // Удаляемый узел не корень
					{
						slow->parent = father;

						if (father->left == cur) father->left = slow;
						else father->right = slow;
					}
				}
			}

			delete cur;
			cur = nullptr;
		}
	}

	void rightRotate(RBNode<T>* cur)
	{
		RBNode<T>* temp = cur->left;
		temp->parent = cur->parent;

		if (cur == this->root)
		{
			this->root = temp;
		}

		else
		{
			if (cur == cur->parent->left) cur->parent->left = temp;
			else cur->parent->right = temp;
		}

		cur->parent = temp;
		cur->left = temp->right;
		if (temp->right) temp->right->parent = cur;
		temp->right = cur;
	}

	void leftRotate(RBNode<T>* cur)
	{
		RBNode<T>* temp = cur->right;
		temp->parent = cur->parent;

		if (cur == this->root)
		{
			this->root = temp;
		}

		else
		{
			if (cur == cur->parent->left) cur->parent->left = temp;
			else cur->parent->right = temp;
		}

		cur->parent = temp;
		cur->right = temp->left;
		if (temp->left) temp->left->parent = cur;
		temp->left = cur;
	}

	bool isValidRBTree()
	{
		// Пустые деревья также являются красными и черными деревьями
		if (nullptr == this->root)
			return  true;
		if (this->root->color != black) {
			std::cout << "Природа 1: корневой узел не черный";
			return false;
		}
		// Получаем количество узлов на одном пути
		int blackCount = 0;
		RBNode<T>* cur = this->root;
		while (nullptr != cur) {
			if (cur->color == black)
				blackCount++;
			cur = cur->left;
		}
		// Особый метод проверки
		return _isValidRBtree(this->root, 0, blackCount);
	}

	bool _isValidRBtree(RBNode<T>* temp, int pathCount, int blackCount) {
		if (nullptr == temp)
			return true;
		// Встречаем черный узел, подсчитываем количество черных узлов на текущем пути
		if (temp->color == black)
			pathCount++;
		// характер проверки три
		RBNode<T>* parent = temp->parent;
		if (parent != nullptr && parent->color == red && temp->color == red) {
			std::cout << "Нарушение природы 3: красные узлы соединены вместе";
			return true;
		}
		// Проверка 4
		// Если это листовой узел, путь дошел до конца, проверяем, совпадает ли общее количество черных узлов в пути с предыдущей статистикой
		if (temp->left == nullptr && temp->right == nullptr) {
			if (pathCount != blackCount) {
				std::cout << "Природа 4: Несогласованный формат черных узлов на пути";
				return false;
			}
		}
		// Рекурсивное определение левого и правого поддеревьев корня
		return _isValidRBtree(temp->left, pathCount, blackCount) &&
			_isValidRBtree(temp->right, pathCount, blackCount);
	}

	void balancePush(RBNode<T>* cur)
	{
		if (cur->parent == nullptr)                                             // Вставка корня
		{
			this->root->color = black;
			return;
		}

		if (cur->parent->color == red)                                         // Отец вставляемого узла красный
		{
			RBNode<T>* father = cur->parent;
			RBNode<T>* grandpa = father->parent;
			RBNode<T>* uncle = father->data > grandpa->data ? grandpa->left : grandpa->right;
			RBNode<T>* temp = cur;

			if (uncle && uncle->color == red)                                  // Дядя вставляемого узла красный
			{
				father->color = black;
				uncle->color = black;
				grandpa->color = red;
				balancePush(grandpa);
			}

			else                                                               // Дядя вставляемого узла черный
			{
				if (father == grandpa->left && cur == father->right)           // Отец левый сын дедушки и удаляемый узел правый сын
				{
					leftRotate(father);
					temp = father;
					father = cur;
				}

				if (father == grandpa->right && cur == father->left)           // Отец правый сын дедушки и удаляемый узел левый сын
				{
					rightRotate(father);
					temp = father;
					father = cur;
				}

				father->color = black;
				grandpa->color = red;

				if (grandpa->left == father) rightRotate(grandpa);             // Отец удаляемого узла левый сын дедушки
				else leftRotate(grandpa);                                      // Отец удаляемого узла правый сын дедушки
			}
		}
	}

	void balanceDelete(RBNode<T>*& cur)
	{
		//if (this->root == cur) return;                                         // Удаляемый узел корень
		if (cur->color == red /* && !cur->left && !cur->right*/) return;            // Удаляемый узел красный без детей

		RBNode<T>* temp;

		if (cur->color == black && cur->left && cur->right)                    // Удаляемый узел любого цвета с двумя детьми 
		{
			temp = minRight(cur);
			//if (this->root == cur) temp->color = red;
			swapData(temp, cur);
			cur = temp;
			balanceDelete(cur);
		}

		else if (cur->color == black && (cur->left || cur->right))             // Удаляемый узел черный с одним ребенком
		{
			if (cur->left) temp = cur->left;
			else temp = cur->right;
			swapData(temp, cur);
			cur = temp;
		}

		else if (cur->color == black && !cur->left && !cur->right)             // Удаляемый узел черный без детей
		{
			RBNode<T>* father = cur->parent;
			RBNode<T>* brother = father->right == cur ? father->left : father->right;
			RBNode<T>* nephewleft = brother->left;
			RBNode<T>* nephewright = brother->right;

			if (brother->color == black)                                       // Брат удаляемого узла черный
			{
				if (nephewright && nephewright->color == red)                  // Правый ребенок брата удаляемого узла красный
				{
					if (father->left == cur)                                   // Случай, когда удаляемый узел левый сын
					{
						brother->color = father->color;
						father->color = black;
						if (nephewright)nephewright->color = black;
						leftRotate(father);
					}

					else                                                       // Случай, когда удаляемый узел правый сын
					{
						if (nephewleft && nephewright) swapColor(nephewleft, nephewright);
						else if (nephewright) nephewright->color = black;
						else if (nephewleft) nephewleft->color = black;
						leftRotate(brother);
						balanceDelete(cur);
					}
				}

				else if (nephewleft && nephewleft->color == red)               // Левый ребенок брата удаляемого узла красный
				{
					if (father->left == cur)                                   // Случай, когда удаляемый узел левый сын
					{
						if (nephewleft && nephewright) swapColor(nephewleft, nephewright);
						else if (nephewright) nephewright->color = black;
						else if (nephewleft) nephewleft->color = black;
						rightRotate(brother);
						balanceDelete(cur);
					}

					else                                                       // Случай, когда удаляемый узел правый сын
					{
						brother->color = father->color;
						father->color = black;
						if (nephewright)nephewright->color = black;
						rightRotate(father);
					}
				}

				else if ((!nephewleft || nephewleft->color == black) &&
					(!nephewright || nephewright->color == black))             // Оба ребенка брата удаляемого узла черные
				{
					brother->color = red;
					if (father->color == black) balanceDelete(father);
					else father->color = black;
				}
			}

			else                                                               // Брат удаляемого узла красный         
			{
				father->color = red;
				//brother->color = red;
				cur == father->left ? leftRotate(father) : rightRotate(father);// левый или правый удаляемый узел
				balanceDelete(cur);
			}
		}
	}

	RBNode<T>* maxLeft(RBNode<T>* cur)
	{
		RBNode<T>* temp = cur->left;

		while (temp->right)
			temp = temp->right;

		return temp;
	}

	RBNode<T>* minRight(RBNode<T>* cur)
	{
		RBNode<T>* temp = cur->right;

		while (temp->left)
			temp = temp->left;

		return temp;
	}

	RBNode<T>* begin() const
	{
		return this->root;
	}

	bool isEmpty() const
	{
		return this->root == nullptr;
	}

	size_t size() const
	{
		return  this->tsize;
	}

	void clear()
	{
		while (this->tsize)
		{
			this->deleteNode(this->root->data);
		}
	}

	void show()
	{
		map_of_tree.clear();
		print(this->root, 0);
		std::cout << std::endl << std::endl;
	}

	void print(RBNode<T>* cur, int n)
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

	/*void getTree() const
	{
		if (!isEmpty())
		{
			std::queue<RBNode<T>*> cont;
			RBNode<T>* temp;
			cont.push(this->root);

			while (!cont.empty())
			{
				cont.front()->getNode();
				if (cont.front()->left) cont.push(cont.front()->left);
				if (cont.front()->right) cont.push(cont.front()->right);
				cont.pop();
			}
		}
	}*/
};