#pragma once
#include <exception>
#include <stack>
#include <iomanip>
#include <utility>
#include <vector>
#include <string.h>

#include "Logger.hpp"

template <typename T>
class TRbTree
{
	enum Color { COLOR_RED, COLOR_BLACK };

	struct Node
	{
		unsigned char color;

		T data;

		Node* parent;
		Node* right; //������ ��������
		Node* left; //������ ��������

		Node() :parent(nullptr), right(nullptr), left(nullptr), color(COLOR_BLACK) {};//����
		Node(T data, Color color, Node* parent, Node* left, Node* right) : data(data), color(color), parent(parent), left(left), right(right) {}
	};

	Node* sheet = new Node();//��������� ������� ������� �����, ����� � ������ ������� nullptr. 
	Node* root = sheet;

	unsigned int compareCount = 1;

	Node* findeNode(const T& data)
	{
		Node* current = root;

		while (current != sheet && current->data != data)
		{
			compareCount++;
			if (current->data > data)
				current = current->left;
			else
				current = current->right;
		}

		return current;
	}

	Node* getUncle(Node* node)
	{
		Node* gParent = getGrandParent(node);

		if (gParent == nullptr)
			return nullptr;

		if (gParent->right == node->parent)
			return gParent->left;
		else
			return gParent->right;
	}

	Node* getGrandParent(Node* node)
	{
		if (node->parent != sheet && node->parent->parent != sheet)
			return node->parent->parent;
		else
			return nullptr;
	}

	void rightRotate(Node* node)
	{
		if (node->left != sheet)
		{
			Node* lChild = node->left;
			node->left = lChild->right;

			if (lChild->right != sheet)
				lChild->right->parent = node;

			lChild->parent = node->parent;

			if (node->parent == sheet)
				root = lChild;
			else if (node == node->parent->left)
				node->parent->left = lChild;
			else
				node->parent->right = lChild;

			lChild->right = node;
			node->parent = lChild;
		}
	}

	void leftRotate(Node* node)
	{
		if (node->right != sheet)
		{
			Node* rChild = node->right;
			node->right = rChild->left;

			if (rChild->left != sheet)
				rChild->left->parent = node;

			rChild->parent = node->parent;

			if (node->parent == sheet)
				root = rChild;
			else if (node == node->parent->left)
				node->parent->left = rChild;
			else
				node->parent->right = rChild;

			rChild->left = node;
			node->parent = rChild;
		}
	}

	Node* getMin(Node* start)
	{
		Node* current = start;
		while (current->left != sheet)
			current = current->left;

		return current;
	}

	void transplant(Node* node1,Node* node2)
	{
		if (node1->parent == sheet)
			root = node2;
		else if (node1->parent->left == node1)
			node1->parent->left = node2;
		else
			node1->parent->right = node2;

		node2->parent = node1->parent;
	}

	void treeRecovery(Node* current)
	{
		while (current != root && current->color != COLOR_BLACK)
		{
			if (current == current->parent->left)
			{
				Node* brother = current->parent->right;
				if (brother->color == COLOR_RED)
				{
					brother->color = COLOR_BLACK;
					current->parent->color = COLOR_RED;

					leftRotate(current->parent);

					brother = current->parent->right;
				}

				if (brother->left->color == COLOR_BLACK && brother->right->color == COLOR_BLACK)
				{
					brother->color = COLOR_RED;
					current = current->parent;
				}
				else
				{
					if (brother->right->color == COLOR_BLACK)
					{
						brother->left->color = COLOR_BLACK;
						brother->color = COLOR_RED;

						rightRotate(brother);

						brother = current->parent->right;
					}

					brother->color = current->parent->color;
					current->parent->color = COLOR_BLACK;
					brother->right->color = COLOR_BLACK;

					leftRotate(current->parent);

					current = root;
				}
			}
			else
			{
				Node* brother = current->parent->left;
				if (brother->color == COLOR_RED)
				{
					brother->color = COLOR_BLACK;
					current->parent->color = COLOR_RED;

					rightRotate(current->parent);

					brother = current->parent->left;
				}

				if (brother->right->color == COLOR_BLACK && brother->left->color == COLOR_BLACK)
				{
					brother->color = COLOR_RED;
					current = current->parent;
				}
				else
				{
					if (brother->left->color == COLOR_BLACK)
					{
						brother->right->color = COLOR_BLACK;
						brother->color = COLOR_RED;

						leftRotate(brother);

						brother = current->parent->left;
					}

					brother->color = current->parent->color;
					current->parent->color = COLOR_BLACK;
					brother->left->color = COLOR_BLACK;

					rightRotate(current->parent);

					current = root;
				}
			}
		}

		current->color = COLOR_BLACK;
	}

public:
	T find(const T& key)
	{
		Node* node = findeNode(key);
		if (node != sheet)
		{
			Logger::log(CONTEXT(), "RbTree : The number of comparisons in the search - " + std::to_string(compareCount),Info);
			compareCount = 1;
			return node->data;
		}
		else
		{
			throw std::invalid_argument("Key was not found");
		}
	}

	void insert(T key)
	{
		if (findeNode(key) != sheet)
			throw std::invalid_argument("Such key olready exists");

		compareCount = 1;
		if (root == sheet)
		{
			Logger::log(CONTEXT(), "RbTree : The number of comparisons in the insert - 1", Info);
			root = new Node(key, COLOR_BLACK, sheet, sheet, sheet);
		}
		else
		{
			Node* current = root;
			int i = 0;

			while (current->right != sheet && current->data < key || current->left != sheet && current->data > key)
			{
				compareCount++;
				if (current->data < key)
					current = current->right;
				else
					current = current->left;
			}

			Logger::log(CONTEXT(), "RbTree : The number of comparisons in the insert - " + to_string(compareCount), Info);
			compareCount = 1;

			if (current->data < key)
			{
				current->right = new Node(key, COLOR_RED,current, sheet, sheet);
				current = current->right;
			}
			else
			{
				current->left = new Node(key, COLOR_RED, current, sheet, sheet);
				current = current->left;
			}

			while (current->parent->color == COLOR_RED)
			{
				if (current->parent == getGrandParent(current)->left)
				{
					if (getUncle(current)->color == COLOR_RED)
					{
						current->parent->color = COLOR_BLACK;
						getUncle(current)->color = COLOR_BLACK;
						getGrandParent(current)->color = COLOR_RED;
						current = getGrandParent(current);
					}
					else
					{
						if (current == current->parent->right)
						{
							leftRotate(current->parent);
						}
						
						current->parent->color = COLOR_BLACK;
						getGrandParent(current)->color = COLOR_RED;
						rightRotate(getGrandParent(current));
					}
				}
				else
				{
					if (getUncle(current)->color == COLOR_RED)
					{
						current->parent->color = COLOR_BLACK;
						getUncle(current)->color = COLOR_BLACK;
						getGrandParent(current)->color = COLOR_RED;
						current = getGrandParent(current);
					}
					else
					{
						if (current == current->parent->left)
						{
							rightRotate(current->parent);
						}

						current->parent->color = COLOR_BLACK;
						getGrandParent(current)->color = COLOR_RED;
						leftRotate(getGrandParent(current));
					}
				}
			}
			root->color = COLOR_BLACK;
		}
	}

	//������� �������
	void remove(const T& key)
	{
		Node* current = findeNode(key);
		Logger::log(CONTEXT(), "RbTree : The number of comparisons in the delete - " + to_string(compareCount), Info);
		compareCount = 1;

		if (current != sheet)
		{
			unsigned char color = current->color;
			Node* changedNode;

			if (current->left == sheet)
			{
				changedNode = current->right;
				transplant(current, current->right);
			}
			else if (current->right == sheet)
			{
				changedNode = current->left;
				transplant(current, current->left);
			}
			else
			{
				Node* min = getMin(current->right);
				color = min->color;
				changedNode = min->right;

				if (min->parent == current)
				{
					changedNode->parent = min;
				}
				else
				{
					transplant(min,min->right);

					min->right = current->right;
					min->right->parent = min;
				}

				transplant(current,min);
				min->left = current->left;
				min->left->parent = min;
				min->color = current->color;
			}

			delete current;

			if (color == COLOR_BLACK)
				treeRecovery(changedNode);
		}
	}

	bool isEmpty() const noexcept{ return root == sheet; }

	void show()
	{
		if (!isEmpty())
		{
			std::stack<Node*> nodePtrs;
			nodePtrs.push(root);

			while (!nodePtrs.empty())
			{
				Node* top = nodePtrs.top();
				nodePtrs.pop();

				if (top->right != sheet)
					nodePtrs.push(top->right);

				if (top->left != sheet)
					nodePtrs.push(top->left);
			}
		}
	}

	~TRbTree()
	{
		if (!isEmpty())
		{
			std::stack<Node*> nodePtrs;
			nodePtrs.push(root);

			while (!nodePtrs.empty())
			{
				Node* top = nodePtrs.top();
				nodePtrs.pop();

				if (top->right != sheet)
					nodePtrs.push(top->right);

				if (top->left != sheet)
					nodePtrs.push(top->left);

				delete top;
			}
		}

		delete sheet;
	}

	vector<T> vectorize() const
	{
		vector<T> dataVec;

		if (!isEmpty())
		{
			std::stack<Node*> nodePtrs;
			nodePtrs.push(root);

			while (!nodePtrs.empty())
			{
				Node* top = nodePtrs.top();
				nodePtrs.pop();

				dataVec.push_back(top->data);

				if (top->right != sheet)
					nodePtrs.push(top->right);

				if (top->left != sheet)
					nodePtrs.push(top->left);
			}
		}

		return dataVec;
	}

	//class WideIterator:iterator
	//{
	//public:
	//	WideIterator()
	//	{

	//	}

	//	const T& operator *()
	//	{

	//	}

	//	void operator ++(int)
	//	{

	//	}
	//};

	//class DeepIterator:iterator
	//{
	//public:
	//
	//};
};