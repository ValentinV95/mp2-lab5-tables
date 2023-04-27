#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;


template <class T>
class TAVLTree
{
private:
    class Node
    {
    public:
        T data;
        Node* left;
        Node* right;
        int height;
        Node()
        {
            data = NULL;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
        Node(T data_)
        {
            data = data_;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    struct Logger
    {
        int comp;
        string log;
    };

    Node* root;
    Logger logger;

    Node* rightRotate(Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    Node* leftRotate(Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
    Node* minValueNode(Node* node) 
    {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }
    Node* maxValueNode(Node* node) 
    {
        Node* current = node;
        while (current->right != NULL)
            current = current->right;
        return current;
    }
    int getBalance(Node* n)
    {
        if (n == NULL)
            return 0;
        return getHeight(n->left) - getHeight(n->right);
    }
    int getHeight(Node* n)
    {
        if (n == NULL)
            return 0;
        return n->height;
    }
    Node* Insert(Node* node, T data)
    {
        logger.log = string("Operation Insert: ");
        logger.comp = 0;
        if (node == NULL)
            return new Node(data);

        if (data < node->data)
            node->left = Insert(node->left, data);
        else if (data > node->data)
            node->right = Insert(node->right, data);
        else
            return node;

        logger.comp++;
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        if (balance > 1 && data < node->left->data)
            return rightRotate(node);

        if (balance < -1 && data > node->right->data)
            return leftRotate(node);

        if (balance > 1 && data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        logger.comp++;

        return node;
    }
    Node* Delete(Node* root, T data)
    {
        logger.log = string("Operation Delete: ");
        logger.comp = 0;
        if (root == NULL)
            return root;

        if (data < root->data)
            root->left = Delete(root->left, data);
        else if (data > root->data)
            root->right = Delete(root->right, data);
        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                Node* temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = Delete(root->right, temp->data);
            }
        }
        logger.comp++;
        if (root == NULL)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        logger.comp++;

        return root;
    }
    void Print(Node* root, int space)
    {
        if (root == NULL)
            return;
        space += 10;
        Print(root->right, space);
        cout << endl;
        for (int i = 10; i < space; i++)
            cout << " ";
        cout << root->data << endl;
        Print(root->left, space);
    }
public:
    TAVLTree()
    {
        root = NULL;
    }
    void Insert(T data) { root = Insert(root, data); }
    void Delete(T data) { root = Delete(root, data); }
    void Print() { Print(root, 5); }
    T& Search(T data)
    {
        logger.log = string("Operation Search: ");
        logger.comp = 0;
        Node* cur = root;
        while (cur != NULL)
        {
            logger.comp++;
            if (data == cur->data)
            {
                return cur->data;
            }
            else if (data > cur->data)
            {
                cur = cur->right;
            }
            else
            {
                cur = cur->left;
            }
            logger.comp++;
        }
        throw exception("This element was not found");
    }
    string logging()
    {
        return logger.log + string("Cost: ") + to_string(logger.comp) + string(" comparisons!");
    }
    ~TAVLTree()
    {
        if (root == NULL)
        {
            return;
        }
        stack<Node*> st;
        st.push(root);
        while (!st.empty())
        {
            Node* top = st.top();
            st.pop();
            if (top->right != NULL)
            {
                st.push(top->right);
            }
            if (top->left != NULL)
            {
                st.push(top->left);
            }
            delete top;
        }
    }
};

template<class TValue>
class TAVLtable
{
private:
    struct TTableRec
    {
        TValue value;
        string key;
        TTableRec() : value(TValue()), key("") {}
        TTableRec(string _key, TValue _value) : value(_value), key(_key) {}
        const bool operator > (const TTableRec& other) const { return key > other.key; }
        const bool operator < (const TTableRec& other) const { return key < other.key; }
        const bool operator == (const TTableRec& other) const { return key == other.key; }
        const bool operator != (const TTableRec& other) const { return key != other.key; }
        friend ostream& operator<<(ostream& ostr, TTableRec& row)
        {
            ostr << row.key << ": " << row.value;
            return ostr;
        }
    };

    TAVLTree<TTableRec> table;
public:
    void Insert(string key, TValue value)
    {
        TTableRec row(key, value);
        table.Insert(row);
    }
    TValue& Search(string key)
    {
        TTableRec row(key, TValue());
        return table.Search(row).value;
    }
    void Delete(string key)
    {
        TTableRec row(key, TValue());
        table.Delete(row);
    }
    void Print() { table.Print(); }
    string logging() { return table.logging(); }
};