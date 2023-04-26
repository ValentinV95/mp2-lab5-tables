#pragma once

#include <iostream>
#include <queue>
#include "logger.h"
#include "pair.hpp"

static LogTable treeTable("transitions");

enum TreeColor
{
	black = 0,
	red = 1
};

template<class T>
struct RBNode
{
	unsigned char tcolor;                                  // 0 - black, 1 - red
	T data;                                                // Данные 
	RBNode* left;                                          // Указатель на левого потомка
	RBNode* right;                                         // Указатель на правого потомка
	RBNode* parent;                                        // Указатель на родителя

	RBNode() : tcolor(red), data(T()), left(nullptr), right(nullptr), parent(nullptr)
	{}

	RBNode(const T& var) : tcolor(red), data(var), left(nullptr), right(nullptr), parent(nullptr)
	{}

	void getNode() const
	{
		std::cout << "(" << data << ", " << (tcolor ? "red" : "black") << ")";
	}
};

template<class T>
class Tree
{
private:
	RBNode<T>* root;                                       // Указатель на корень
	int tsize;                                             // Количество узлов в данный момент
	std::vector<int> map_of_tree;

	void swapData(RBNode<T>*, RBNode<T>*);                 // Обмен данными
	void swapColor(RBNode<T>*, RBNode<T>*);                // Обмен цветами
	void rightRotate(RBNode<T>*);                          // Правое вращение
    void leftRotate(RBNode<T>*);                           // Левое вращение
    void balancePush(RBNode<T>*);                          // Балансировка вставки
	void balanceDelete(RBNode<T>*);                        // Балансировка удаления
	RBNode<T>* maxLeft(RBNode<T>*);                        // Максимальный левый потомок
	RBNode<T>* minRight(RBNode<T>*);                       // Минимальный правый потомок

public:
	Tree();                                                // Конструктор по умолчанию
	Tree(const T&);                                        // Конструктор инициализации корня
	~Tree();                                               // Деструктор
	RBNode<T>* search(const T&) const;                     // Поиск
	void push(const T&);                                   // Вставка
	void deleteNode(RBNode<T>*);                           // Удаление узла
	RBNode<T>* begin() const;                              // Получение корня
	bool isEmpty() const;                                  // Проверка пустоты дерева
	int size() const;                                      // Получение количества узлов в данный момент
	void clear();                                          // Удаление всех узлов в дереве
	void getTree() const;                                  // Функция вызова поиска в глубину
	void DFS(RBNode<T>*) const;                            // Поиск в глубину

};

template<class T>
void Tree<T>::swapData(RBNode<T>* one, RBNode<T>* other)
{
	T temp = one->data;
	one->data = other->data;
	other->data = temp;
}

template<class T>
void Tree<T>::swapColor(RBNode<T>* one, RBNode<T>* other)
{
	unsigned char temp = one->tcolor;
	one->tcolor = other->tcolor;
	other->tcolor = temp;
}

template<class T>
void Tree<T>::rightRotate(RBNode<T>* cur)
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

template<class T>
void Tree<T>::leftRotate(RBNode<T>* cur)
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

template<class T>
void Tree<T>::balancePush(RBNode<T>* cur)
{
	++treeTable;

	if (cur->parent == nullptr)                                             // Вставка корня
	{
		this->root->tcolor = black;
		return;
	}

	if (cur->parent->tcolor == red)                                         // Отец вставляемого узла красный
	{
		RBNode<T>* father = cur->parent;
		RBNode<T>* grandpa = father->parent;
		RBNode<T>* uncle = father->data > grandpa->data ? grandpa->left : grandpa->right;
		RBNode<T>* temp = cur;

		if (uncle && uncle->tcolor == red)                                  // Дядя вставляемого узла красный
		{
			father->tcolor = black;
			uncle->tcolor = black;
			grandpa->tcolor = red;
			balancePush(grandpa);
		}

		else                                                               // Дядя вставляемого узла черный(или его нет)
		{
			if (father == grandpa->left && cur == father->right)           // Отец левый сын дедушки и вставляемый узел правый сын
			{
				leftRotate(father);
				temp = father;
				father = cur;
			}

			if (father == grandpa->right && cur == father->left)           // Отец правый сын дедушки и вставляемый узел левый сын
			{
				rightRotate(father);
				temp = father;
				father = cur;
			}

			father->tcolor = black;
			grandpa->tcolor = red;

			if (grandpa->left == father) rightRotate(grandpa);             // Отец вставляемого узла левый сын дедушки
			else leftRotate(grandpa);                                      // Отец вставляемого узла правый сын дедушки
		}
	}
}

template<class T>
void Tree<T>::balanceDelete(RBNode<T>* cur)
{  
	if (cur->tcolor == red) return;   // Удаляемый узел красный

	RBNode<T>* temp;

	++treeTable;

	if (cur->left || cur->right)            // Удаляемый узел черный с одним ребенком
	{
		//if (cur == this->root) cur->left ? cur->left->tcolor = black : cur->right->tcolor = black;
		//else 
		cur->left ? swapColor(cur->left, cur) : swapColor(cur->right, cur);
	}

	else if (cur->parent && !cur->left && !cur->right)            // Удаляемый узел черный без детей
	{
		RBNode<T>* father = cur->parent;
		RBNode<T>* brother = father->right == cur ? father->left : father->right;
		RBNode<T>* nephewleft = brother->left;
		RBNode<T>* nephewright = brother->right;

		if (brother->tcolor == black)                                      // Брат удаляемого узла черный
		{
			if (nephewright && nephewright->tcolor == red)                 // Правый ребенок брата удаляемого узла красный
			{
				if (father->left == cur)                                   // Случай, когда удаляемый узел левый сын
				{
					brother->tcolor = father->tcolor;
					father->tcolor = black;
					if (nephewright)nephewright->tcolor = black;
					leftRotate(father);
				}

				else                                                       // Случай, когда удаляемый узел правый сын
				{
					if (nephewleft && nephewright) swapColor(nephewleft, nephewright);
					else if (nephewright) nephewright->tcolor = black;
					else if (nephewleft) nephewleft->tcolor = black;
					leftRotate(brother);
					balanceDelete(cur);
				}
			}

			else if (nephewleft && nephewleft->tcolor == red)              // Левый ребенок брата удаляемого узла красный
			{
				if (father->left == cur)                                   // Случай, когда удаляемый узел левый сын
				{
					if (nephewleft && nephewright) swapColor(nephewleft, nephewright);
					else if (nephewright) nephewright->tcolor = black;
					else if (nephewleft) nephewleft->tcolor = black;
					rightRotate(brother);
					balanceDelete(cur);
				}

				else                                                       // Случай, когда удаляемый узел правый сын
				{
					brother->tcolor = father->tcolor;
					father->tcolor = black;
					if (nephewright)nephewright->tcolor = black;
					rightRotate(father);
				}
			}

			else if ((!nephewleft || nephewleft->tcolor == black) &&
				(!nephewright || nephewright->tcolor == black))             // Оба ребенка брата удаляемого узла черные
			{
				brother->tcolor = red;
				if (father->tcolor == black) balanceDelete(father);
				else father->tcolor = black;
			}
		}

		else                                                               // Брат удаляемого узла красный         
		{
			father->tcolor = red;
			//brother->tcolor = red;
			cur == father->left ? leftRotate(father) : rightRotate(father);// левый или правый удаляемый узел
			balanceDelete(cur);
		}
	}
}

template<class T>
RBNode<T>* Tree<T>::maxLeft(RBNode<T>* cur)
{
	RBNode<T>* temp = cur->left;

	while (temp->right)
	{
		++treeTable;
		temp = temp->right;
	}

	return temp;
}

template<class T>
RBNode<T>* Tree<T>::minRight(RBNode<T>* cur)
{
	RBNode<T>* temp = cur->right;

	while (temp->left)
	{
		++treeTable;
		temp = temp->left;
	}


	return temp;
}

template<class T>
Tree<T>::Tree() : root(nullptr), tsize(0)
{}

template<class T>
Tree<T>::Tree(const T& var) : root(new RBNode<T>(var)), tsize(1)
{
	this->root->tcolor = black;
}

template<class T>
Tree<T>::~Tree()
{
	this->clear();
	this->root = nullptr;
}

template<class T>
RBNode<T>* Tree<T>::search(const T& var) const
{
	RBNode<T>* temp = this->root;

	while (temp)
	{
		++treeTable;

		if (temp->data > var) temp = temp->left;
		else if (temp->data < var) temp = temp->right;
		else
		{
			treeTable.Logmsg("Tree<T>::search()");
			return temp;
		}
	}

	treeTable.Logmsg("Tree<T>::search()");

	return nullptr;
}

template<class T>
void Tree<T>::push(const T& var)
{
	RBNode<T>* cur = new RBNode<T>(var);

	if (this->isEmpty())                                      // Вставка корня
	{
		this->root = cur;
	}

	else                                                      // Вставка не корня
	{
		RBNode<T>* fast = this->root;
		RBNode<T>* slow = nullptr;

		while (fast)
		{
			slow = fast;
			++treeTable;

			if (var == fast->data)
			{
				treeTable.Logmsg("Tree<T>::push()");
				return;
			}

			else if (var > fast->data)
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

			else
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
		}

		treeTable.Logmsg("Tree<T>::push()");
	}

	balancePush(cur);
	this->tsize++;
}

template<class T>
void Tree<T>::deleteNode(RBNode<T>* cur)
{
	if (cur)
	{
		++treeTable;
		RBNode<T>* temp;
		RBNode<T>* father = cur->parent;

		if (cur->left && cur->right)
		{
			temp = minRight(cur);
			
			swapData(temp, cur);
			deleteNode(temp);
		}

		else
		{
			//balanceDelete(cur);

			if (cur->left || cur->right)
			{
				if (cur->left) temp = cur->left;
				else temp = cur->right;

				temp->parent = father;

				if (!father) this->root = temp;
				else father->left == cur ? father->left = temp : father->right = temp;

			}

			else
			{
				if (!father) this->root = nullptr;
				else father->left == cur ? father->left = nullptr : father->right = nullptr;
			}

			delete cur;
			cur = nullptr;
			tsize--;
			treeTable.Logmsg("Tree<T>::deleteNode()");
		}
	}
}

template<class T>
RBNode<T>* Tree<T>::begin() const
{
	return this->root;
}

template<class T>
bool Tree<T>::isEmpty() const
{
	return this->root == nullptr;
}

template<class T>
int Tree<T>::size() const
{
	return  this->tsize;
}

template<class T>
void Tree<T>::clear()
{
	while (this->tsize)
	{
		this->deleteNode(this->root);
	}
}

template<class T>
void Tree<T>::getTree() const
{
	if (!isEmpty())
	{
		DFS(this->root);
	}

	std::cout << std::endl;
}