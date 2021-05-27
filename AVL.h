#pragma once

template<class T>
class AVL {
public:
    int key;
    T value;
    AVL* left;
    AVL* right;
    int height;

    int getHeight(AVL<T>* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    AVL<T>* newNode(int key, T val) {
        AVL<T>* node = new AVL<T>();
        node->value = val;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        node->key = key;

        return (node);
    }

    AVL<T>* rightRotate(AVL<T>* y) {
        AVL<T>* x = y->left;
        AVL<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left),
            getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left),
            getHeight(x->right)) + 1;

        return x;
    }

    AVL<T>* leftRotate(AVL<T>* x) {
        AVL<T>* y = x->right;
        AVL<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left),
            getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left),
            getHeight(y->right)) + 1;
        return y;
    }

    int getBalance(AVL<T>* N) {
        if (N == nullptr)
            return 0;
        return getHeight(N->left) -
            getHeight(N->right);
    }

    AVL<T>* balance(AVL<T>* node, int key) {
        node->height = 1 + max(getHeight(node->left),
            getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVL<T>* insert(AVL<T>* node, int key, T data) {
        if (node == nullptr)
            return (newNode(key,data));

        if (key < node->key)
            node->left = insert(node->left, key, data);
        else if (key > node->key)
            node->right = insert(node->right, key, data);
        else
            return node;

        return balance(node, key);
    }

    AVL<T>* minValueNode(AVL<T>* node) {
        AVL<T>* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    T find(AVL<T>* node, int key) {
        if (node == nullptr) {
            return T();
        }
        else {
            if (node->key > key) {
                return node->left->find(node->left, key);
            }
            else {
                if (node->key < key) {
                    return node->right->find(node->right, key);
                }
                else {
                    return node->value;
                }
            }
        }
    }

    AVL<T>* deleteNode(AVL<T>* tree, int key) {
        if (tree == nullptr)
            return tree;

        if (key < tree->key)
            tree->left = deleteNode(tree->left, key);

        else if (key > tree->key)
            tree->right = deleteNode(tree->right, key);

        else {
            if ((tree->left == nullptr) ||
                (tree->right == nullptr)) {
                AVL<T>* temp = tree->left ?
                    tree->left :
                    tree->right;

                // No child case
                if (temp == nullptr) {
                    temp = tree;
                    tree = nullptr;
                }
                else
                    *tree = *temp;
                delete(temp);
            }
            else {
                AVL<T>* temp = minValueNode(tree->right);
                tree->value = temp->value;
                tree->key = temp->key;
                tree->right = deleteNode(tree->right,temp->value);
            }
        }

        if (tree == nullptr)
            return tree;

        tree->height = 1 + max(getHeight(tree->left),
            getHeight(tree->right));

        int balance = getBalance(tree);
        if (balance > 1 &&
            getBalance(tree->left) >= 0)
            return rightRotate(tree);

        // Left Right Case
        if (balance > 1 &&
            getBalance(tree->left) < 0) {
            tree->left = leftRotate(tree->left);
            return rightRotate(tree);
        }

        // Right Right Case
        if (balance < -1 &&
            getBalance(tree->right) <= 0)
            return leftRotate(tree);

        // Right Left Case
        if (balance < -1 &&
            getBalance(tree->right) > 0) {
            tree->right = rightRotate(tree->right);
            return leftRotate(tree);
        }

        return tree;
    }

    void printTree(AVL<T>* tree) {
        if (tree != nullptr) {
            std::cout << tree->value << " ";
            printTree(tree->left);
            printTree(tree->right);
        }
    }

};
