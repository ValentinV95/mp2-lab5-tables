#include <iostream>
#include <locale.h>
#include "tree.h"
#include <random>
#include <ctime>
#include "cortree.h"

using namespace std;

void func(RBNode<int>* one, RBNode<int>* other)
{
    one = other;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Cormen::Tree<int> tree;
 
    tree.insert(20);
    tree.insert(30);
    tree.insert(53);
    tree.insert(423);
    tree.insert(523);
    tree.insert(63);
    tree.insert(2);
    tree.insert(7454);
    tree.insert(25);
    tree.insert(26);
    tree.insert(1);
    tree.insert(54);
    Cormen::Node<int>* t = tree.begin();
    tree.show();
    cout << tree.isValidRBTree() << endl;
    //tree.balanceDelete(t->left->left);
    //tree.show();
    //cout << tree.isValidRBTree() << endl;
}
