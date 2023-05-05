#include "ARRAY.h"




int TREE_equesions = 0;
int TREE_del = 0;
int TREE_search = 0;
int TREE_push = 0;







template<typename T>
struct Node
{
	pair<int, T> data;
	int lvl;
	Node* left;
	Node* right;
	Node* parent;
};

template<typename T>
class AWL_TREE
{
public:

	Node<T>* head = nullptr;

	
	void balanse(Node<T>* &last)
	{
		Node<T>* tmp;
		fix_lvl(last);
		TREE_equesions++;
		for (Node<T>* it = last; it->parent != nullptr;)
		{
			

			it = it->parent;

			fix_lvl(it);
			TREE_equesions++;
			if (getlvl(it) > 1)
			{
				TREE_equesions++;
				if (getlvl(it->right) < 0)
				{
					tmp = it->right->left;
					rotate(it->right, 'r');
					rotate(it, 'l');
					TREE_equesions++;
					if (tmp->parent == nullptr) head = tmp;
				}
				else if (getlvl(it->right) >= 0)
				{
					TREE_equesions++;
					tmp = it->right;
					rotate(it, 'l');
					TREE_equesions++;
					if (tmp->parent == nullptr) head = tmp;
				}
				
			}
			TREE_equesions++;
			if (getlvl(it) < -1)
			{
				TREE_equesions++;
				if (getlvl(it->left) > 0)
				{
					tmp = it->left->right;
					rotate(it->left, 'l');
					rotate(it, 'r');
					TREE_equesions++;
					if (tmp->parent == nullptr) head = tmp;
				}
				else if (getlvl(it->left) <= 0)
				{
					TREE_equesions++;
					tmp = it->left;
					rotate(it, 'r');
					TREE_equesions++;
					if (tmp->parent == nullptr) head = tmp;
				}
				
			}
			TREE_equesions++;
		}
	}
	void push(pair<int, T> A)
	{
		TREE_push++;
		TREE_equesions ++;
		if (head == nullptr)
		{
			Node<T>* t = new Node<T>();
			t->data = A;
			t->lvl = 0;
			t->parent = nullptr;
			t->left = nullptr;
			t->right = nullptr;
			head = t;
		}
		else
		{
			pair<int, T> I;
			int i = 0;
			Node<T>* it = head,* itp = head;
			for (;;)
			{
				TREE_equesions ++;
				if (it!=nullptr) I = it->data;
				if (it == nullptr)
				{
					TREE_equesions ++;
					Node<T>* t = new Node<T>();
					t->data = A;
					t->lvl = 0;
					t->parent = itp;
					t->left = nullptr;
					t->right = nullptr;
					it = t;
					break;
				}
				else if (I.first == A.first)
				{
					TREE_equesions += 2;
					it->data = A;
					break;
				}
				else if (I.first < A.first)
				{
					TREE_equesions += 5;
					if (i != 0)
					{
						itp = it;
						i++;
					}
					if (it->right == nullptr)
					{
						Node<T>* t = new Node<T>();
						t->data = A;
						t->lvl = 0;
						t->parent = it;
						t->left = nullptr;
						t->right = nullptr;
						it->right = t;
						it = it->right;
						break;
					}
					it = it->right;
				}
				else if (I.first > A.first)
				{
					TREE_equesions += 6;
					if (i != 0)
					{
						itp = it;
						i++;
					}
					if (it->left == nullptr)
					{
						Node<T>* t = new Node<T>();
						t->data = A;
						t->lvl = 0;
						t->parent = it;
						t->left = nullptr;
						t->right = nullptr;
						it->left = t;
						it = it->left;
						break;
					}
					it = it->left;

				}


			}
			balanse(it);
		}
	}
	void rotate(Node<T>*& last,char rotate)
	{
		Node<T>* PARENT = last->parent;
		TREE_equesions += 1;
		if (rotate == 'l')
		{
			Node<T>* RIGHT = last->right;
			last->right = RIGHT->left;
			if (RIGHT->left != nullptr)
			RIGHT->left->parent = last;
			RIGHT->left = last;
			last->parent = RIGHT;
			RIGHT->parent = PARENT;
			if ((PARENT != nullptr))
			{
				if (PARENT->right == last) PARENT->right = RIGHT;
				if (PARENT->left == last) PARENT->left = RIGHT;
				TREE_equesions += 2;
			}
			TREE_equesions += 2;
			fix_lvl(last);
			fix_lvl(RIGHT);

		}
		TREE_equesions += 1;
		if (rotate == 'r')
		{
			Node<T>* LEFT = last->left;
			last->left = LEFT->right;
			if (LEFT->right != nullptr)
			LEFT->right->parent = last;
			LEFT->right = last;
			last->parent = LEFT;
			LEFT->parent = PARENT;
			if ((PARENT != nullptr))
			{
				if (PARENT->right == last) PARENT->right = LEFT;
				if (PARENT->left == last) PARENT->left = LEFT;
				TREE_equesions += 2;
			}
			TREE_equesions += 2;
			fix_lvl(last);
			fix_lvl(LEFT);
		}
	}
	int getlvl(Node<T>*& last)
	{
		return LVL(last->right) - LVL(last->left);
	}
	int LVL(Node<T>*& last)
	{
		TREE_equesions ++;
		if (last!=nullptr) return last->lvl;
		else return 0;
	}
	void fix_lvl(Node<T>*& last)
	{
		int l = LVL(last->left), r = LVL(last->right);
		last->lvl = (l > r) * l+ (l <= r) * r+1;
		TREE_equesions += 2;
	}
	Node<T>* search(int key)
	{
		TREE_search++;
		pair<int, T> I;
		TREE_equesions ++;
		for (Node<T>* it = head; it != nullptr;)
		{
			I = it->data;
			if (I.first == key)
			{
				TREE_equesions +=1;
				return it;
			}
			else if (I.first < key)
			{
				TREE_equesions += 2;
				it = it->right;
			}
			else if (I.first > key)
			{
				TREE_equesions += 3;
				it = it->left;
			}
			TREE_equesions ++;
		}
		return nullptr;
	}
	Node<T>* get_min()
	{
		Node<T>* it = head;
		TREE_equesions ++;
		while (it->left)
		{
			TREE_equesions ++;
			it = it->left;
		}
		return it;
	}
	Node<T>* del(int key)
	{
		TREE_del++;
		Node<T>* cur  = search(key),*LEFT = nullptr,*RIGHT = nullptr,*PARENT = nullptr,*it = nullptr;
		if (head == nullptr) return nullptr;
		if (cur == head && cur->left == nullptr && cur->right == nullptr)
		{
			TREE_equesions += 3;
			head = nullptr;
			return cur;
		}
		TREE_equesions += 4;
		if (!cur) return cur;
		if (cur != nullptr)
		{
			if (cur->left)
			LEFT = cur->left;
			if (cur->right)
			RIGHT = cur->right;
			if (cur->parent)
			PARENT = cur->parent;
			TREE_equesions += 4;
		}
		if (cur == head && head->data.first == key)
		{
			if (RIGHT)
			it = RIGHT;
			if (it)
				while (it->left != nullptr)
				{
					TREE_equesions++;
					it = it->left;
				}
			if (LEFT)
			LEFT->parent = it;
			if (it)
			it->left = LEFT;
			if (RIGHT)
			RIGHT->parent = nullptr;
			TREE_equesions += 7;
			head = RIGHT;
			balanse(RIGHT);
			return cur;
		}
		else if (PARENT->right == cur)
		{
			if (LEFT)
			it = LEFT;
			if (it)
				while (it->right != nullptr)
				{
					TREE_equesions++;
					it = it->right;
				}
			if (RIGHT)
			RIGHT->parent = it;
			if (it)
			it->right = RIGHT;
			if (LEFT)
			LEFT->parent = PARENT;
			if (PARENT)
			PARENT->right = LEFT;
			balanse(PARENT);
			TREE_equesions += 10;
			return cur;
		}
		else if (PARENT->left == cur)
		{
			if (RIGHT)
			it = RIGHT;
			if (it)
				while (it->left != nullptr) 
				{
					TREE_equesions++;
					it = it->left;
				}
			if (LEFT)
			LEFT->parent = it;
			if (it)
			it->left = LEFT;
			if (RIGHT)
			RIGHT->parent = PARENT;
			if (PARENT)
			PARENT->left = RIGHT;
			TREE_equesions += 11;
			balanse(PARENT);
			return cur;
		}
	}
	void show();
	~AWL_TREE()
	{
		while (head != nullptr)
		{
			del(get_min()->data.first);
		}
	}

};

template<typename T>

void AWL_TREE<T>::show()
{
	cout << endl << "AWL_TREE" << endl << endl;
	Node<T>* it;
	while(head!=nullptr)
	{
		it = get_min();
		it = del(it->data.first);
		cout << "Key: " << it->data.first << " Value: " << it->data.second << endl;
	}
}

void AWL_TREE<Polinom>::show()
{
	cout << endl << "AWL_TREE" << endl << endl;
	Node<Polinom>* it;
	while (head != nullptr)
	{
		it = get_min();
		it = del(it->data.first);
		cout << "Key: " << it->data.first << " Value: ";
		it->data.second << cout <<  endl;
	}
}