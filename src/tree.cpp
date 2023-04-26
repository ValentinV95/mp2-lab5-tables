#include "tree.hpp"
#include "pair.hpp"
#include "polynomial.h"

template<class T>
void Tree<T>::DFS(RBNode<T>* cur) const
{
	if (cur)
	{
		DFS(cur->left);
		std::cout << cur->data << std::endl;
		DFS(cur->right);
	}
}

template<>
void Tree<Pair<Polynomial>>::DFS(RBNode<Pair<Polynomial>>* cur) const
{
	if (cur)
	{
		DFS(cur->left);
		cur->data.getPair();
		DFS(cur->right);
	}
}