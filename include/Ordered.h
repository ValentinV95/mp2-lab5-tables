#include <iostream>

using namespace std;

template <typename T>
struct NodeO
{
	int key;
	T data;
	NodeO<T>* left, * right, * parent;
	int height;
	NodeO(T d, int k)
	{
		data = d;
		key = k;
		height = 0;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	NodeO() {}
};

template <typename T>
size_t get_h(NodeO<T>* t)
{
	if (t == nullptr)
	{
		return 0;
	}
	return t->height;
}

template <typename T>
class Ordered
{
public:
	Ordered()
	{
		first = nullptr;
	}
	void rotateL(NodeO<T>* t)
	{
		if (t->parent != nullptr)
		{
			if (t->parent->left == t)
			{
				t->parent->left = t->right;
			}
			else
			{
				t->parent->right = t->right;
			}
		}
		t->right->parent = t->parent;
		t->parent = t->right;
		NodeO<T>* temp = t->right->left, * tmp = t->right;
		t->right->left = t;
		t->right = temp;
		t->height = max(get_h(t->left), get_h(t->right)) + 1;
		tmp->height = max(get_h(tmp->left), get_h(tmp->right)) + 1;
	}
	void rotateR(NodeO<T>* t)
	{
		if (t->parent != nullptr)
		{
			if (t->parent->left == t)
			{
				t->parent->left = t->left;
			}
			else
			{
				t->parent->right = t->left;
			}
		}
		t->left->parent = t->parent;
		t->parent = t->left;
		NodeO<T>* temp = t->left->left, * tmp = t->left;
		t->left->left = t;
		t->left = temp;
		t->height = max(get_h(t->left), get_h(t->right)) + 1;
		tmp->height = max(get_h(tmp->left), get_h(tmp->right)) + 1;
	}
	void add(int key, T data)
	{
		if (first == nullptr)
		{
			cout << "Ordered add " << 1 << endl;
			NodeO<T>* t = new NodeO<T>(data, key);
			first = t;
			return;
		}
		size_t ct = 1;
		bool r;
		NodeO<T>* t = first, * p = nullptr;
		while (t != nullptr)
		{
			ct++;
			p = t;
			if (key > t->key)
			{
				r = 1;
				t = t->right;
			}
			else
			{
				r = 0;
				t = t->left;
			}
		}
		ct++;
		t = new NodeO<T>(data, key);
		if (p != nullptr)
		{
			t->parent = p;
			if (r)
			{
				p->right = t;
			}
			else
			{
				p->left = t;
			}
		}
		ct += this->rebalance(t);
		cout << "Ordered add " << ct << endl;
	}
	size_t rebalance(NodeO<T>* t)
	{
		size_t ct = 1;
		while (t != nullptr)
		{
			ct++;
			int hh = get_h(t->right) - get_h(t->left);
			if (abs(hh) == 2)
			{
				if (hh > 0)
				{
					if (get_h(t->right->left) - get_h(t->right->right) == -1)
					{
						this->rotateL(t);
					}
					else
					{
						this->rotateR(t->right);
						this->rotateL(t);
					}
				}
				else
				{
					if (get_h(t->left->right) - get_h(t->left->left) == -1)
					{
						this->rotateR(t);
					}
					else
					{
						this->rotateL(t->left);
						this->rotateR(t);
					}
				}
			}
			t->height = max(get_h(t->right), get_h(t->left)) + 1;
			first = t;
			t = t->parent;
		}
		return ct;
	}
	void del(int key)
	{
		size_t ct = 1;
		NodeO<T>* t = first;
		while ((t != nullptr) && (t->key != key))
		{
			ct++;
			if (key > t->key)
			{
				t = t->right;
			}
			else
			{
				t = t->left;
			}
		}
		if (t != nullptr)
		{
			if (t == first)
			{
				first = nullptr;
				cout << "Ordered delete " << 1 << endl;
				return;
			}
			NodeO<T>* p = t->parent, * l = t->left;
			t = t->right;
			NodeO<T>* temp;
			while (t != nullptr)
			{
				ct++;
				temp = t->left;
				t->left = l;
				l->parent = t;
				l = temp;
				t->parent = p;
				p = t;
				if ((t->right == nullptr) && (l != nullptr))
				{
					t->right = l;
					break;
				}
				t = t->right;
			}
			ct += this->rebalance(p);
		}
		else
		{
			throw exception("Nothing to delete");
		}
		cout << "Ordered delete " << ct << endl;
	}
	T& find(int key)
	{
		size_t ct = 1;
		NodeO<T>* t = first;
		while ((t != nullptr) && (t->key != key))
		{
			ct++;
			if (key > t->key)
			{
				t = t->right;
			}
			else
			{
				t = t->left;
			}
		}
		if (t == nullptr)
		{
			throw exception("Cant find key");
		}
		cout << "Ordered find " << ct << endl;
		return t->data;
	}
private:
	NodeO<T>* first;
};