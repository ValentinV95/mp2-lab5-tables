#pragma once



#include "../polinom/include/polinom_functions.h"






template <class T>
class R_B_Tree
{
public:

	struct Node
	{
		char colour;

		T data;
		string key;
		

		Node* left;
		Node* right;

		Node* parent;
	};
	int numbers;

	Node* Root;
	Node* nil;

	R_B_Tree()
	{
		nil = new Node{ 'b' };
		Root = nil;
		numbers = 0;
	}

	int get_numbers() 
	{
		return numbers;
	}

	string show_colour(char c)
	{
		if (c == 'r') return "red";
		else if (c == 'b') return "black";
		else throw exception("No colour");
	}

		Node* find(string tmp_key)
		{
			numbers = 0;
			if (Root == nil) 
			{
				numbers++;
				return nullptr;
			}

			Node* t = Root;

			while (t != nil)
			{
				numbers++;
				if (tmp_key < t->key)
				{
					t = t->left;
				}
				else if (tmp_key > t->key)
				{
					t = t->right;
				}
				else return t;
			}
			return nullptr;
		}
	

	void rotateLeft(Node* t)
	{
		Node* Parent = t->parent;

		numbers++;
		if (Parent == Root)
		{
		 Root = t;
		}
		else
		{

			if (Parent == Parent->parent->left)
			{
				Parent->parent->left = t;
			}
			else Parent->parent->right = t;
		}
		
		Parent->right = t->left;

		if (t->left)
		{
			t->left->parent = Parent;
		}

		t->left = Parent;
		t->parent = Parent->parent;

		Parent->parent = t;
	}


	void rotateRight(Node* t)
	{
		Node* Parent = t->parent;

		numbers++;
		if (Parent == Root)
		{
			Root = t;
		}
		else 
		{
			if (Parent == Parent->parent->left)
			{
				Parent->parent->left = t;
			}
			else Parent->parent->right = t;
		}

		Parent->left = t->right;                     //не перепутать ('-'  )

		if (t->right)
		{
			t->right->parent = Parent;
		}

		t->right = Parent;
		t->parent = Parent->parent;

		Parent->parent = t;
	}


	
////////////////////////////////////////////////////////////////[ INSERT ]////////////////////////////////////////////////////
	
	void input()
	{

		cout << endl << "Ввод полинома:" << endl << endl;

		cout << "Введите количество мономов в полиноме:  ";
		int n = amount_of_monoms();

		polinom A = create_polinom(n);

		cout << endl << endl << endl << endl;
		system("pause");
		cout << endl;

		show_polinom(A);

		cout << endl << endl;

		cout << " Придумайте свой уникальный ключ для данного полинома (первый символ - латинская маленькая буква). ";
		cout << endl << " Ввод ключа: ";


		string bad;
		cin >> bad;

		if (bad != "no!")
		{
			while (find(bad))
			{
				cout << endl << "Данный ключ уже используется, введите другой" << endl;
				cin >> bad;
				if (bad == "no!")
					return;
			}

			insert(bad, A);

			cout << endl << endl << "Создан элемент: " << endl << "Ключ: " << bad << endl;
			show_polinom(A);
		}
	}
	


	void insert(string tmp_key, T tmp_data)
	{
		numbers = 0;
		
		if (Root == nil)
		{
			numbers++;
			Root = new Node{ 'b',tmp_data, tmp_key,  nil, nil, nullptr };
			return;
		}
		else
		{
			Node* t = Root;
			while (t)
			{
				numbers++;
				if (t->key > tmp_key)
				{
					if (t->left == nil)
					{
						t->left = new Node{ 'r',tmp_data, tmp_key,  nil, nil, t };
						fix_insert(t->left);
						return;
					}
					else t = t->left;
				}
				else if( t->key < tmp_key)
				{
					if (t->right == nil)
					{
						t->right = new Node{ 'r', tmp_data,tmp_key,  nil, nil, t };
						fix_insert(t->right);
						return;
					}
					else t = t->right;
				}
			}
		}
	}//_____________________
	 //			/|\			
	 //		   / | \		
	 //		  /  |  \		
	 //			 |			
	 //			 |			
	 //			 |			
 	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //	      \  |  /		
	 //		   \ | /		
	 //_________\|/_________
	void fix_insert(Node* t)
	{
		Node* Parent = nullptr;
		Node* Grandfather = nullptr;
		Node* Uncle = nullptr;

		
		if (t == Root)
		{
			numbers++;
			t->colour = 'b';
			return;
		}

		while (t != Root && t->colour == 'r' && t->parent->colour == 'r')
		{
			numbers++;
			Parent = t->parent;
			Grandfather = Parent->parent;


			if (Parent == Grandfather->left) //   ( <-- )
			{
				Uncle = Grandfather->right;

				
				if (Uncle->colour == 'r')
				{
					numbers++;
					Parent->colour = 'b';
					Grandfather->colour= 'r';
					Uncle->colour = 'b';
					t = Grandfather;
				}
				else 
				{
					if (t == Parent->right)
					{
						rotateLeft(t);
						t = t->left;
						Parent = t->parent;
						Grandfather = Parent->parent;
					}
					numbers++;
					Parent->colour = 'b';
					Grandfather->colour = 'r';
					rotateRight(Parent);
				}
			}
			else //   ( --> )
			{
				Uncle = Grandfather->left;

				
				if (Uncle->colour == 'r') 
				{
					numbers++;
					Parent->colour = 'b';
					Grandfather->colour = 'r';
					Uncle->colour = 'b';
					t = Grandfather;
				}
				else 
				{
					
					if (t == Parent->left)
					{
						rotateRight(t);
						t = t->right;
						Parent = t->parent;
						Grandfather = Parent->parent;
					}
					numbers++;
					Parent->colour = 'b';
					Grandfather->colour = 'r';
					rotateLeft(Parent);
				}
			}
		}
		Root->colour= 'b';
	}



////////////////////////////////////////////////////////////////[ REMOVE ]////////////////////////////////////////////////////


	void remove(const string& tmp_key)
	{
		Node* t = find(tmp_key);

		numbers = 0;
		numbers++;

		if (t->left == nil && t->right == nil)      //  (   0_/    \_0   )
		{
			numbers++;
			if (t != Root)
			{
				numbers++;
				if (t->parent->left == t)
				{
					t->parent->left = nil;
				}
				else t->parent->right = nil;
				fix_remove(t);
			}
			else Root = nil;
		}
		else if (++numbers && t->left != nil && t->right == nil)    // (   1_/    \_0   )
		{
			numbers++;
			if (t != Root)
			{
				numbers++;
				if (t->parent->left == t)
				{
					t->parent->left = t->left;
				}
				else t->parent->right = t->left;
				t->left->parent = t->parent;
			}
			else Root = t->left;
			fix_remove(t->left);
		}
		else if (++numbers && t->left == nil && t->right != nil)    // (   0_/    \_1   )
		{
			numbers++;
			if (t != Root)
			{
				numbers++;
				if (t->parent->right == t)
				{
					t->parent->right = t->right;
				}
				else t->parent->left = t->right;
				t->right->parent = t->parent;
			}
			else Root = t->right;
			fix_remove(t->right);
		}
		else if(++numbers && t->left != nil && t->right != nil)    //   (   1_/    \_1   )
		{
			Node* NKO = t->right;

			numbers++;
			while (NKO->left != nil)
			{
				numbers++;

				NKO = NKO->left;
			}

			Node* NKO_Parent = NKO->parent;
			Node* NKO_Child = NKO->right;

			numbers++;
			if (NKO->parent != t)
			{
				numbers++;
				if (NKO->right != nil)
				{
					NKO->right->parent = NKO->parent;
				}
				NKO->parent->left = NKO->right;
				NKO->right = t->right;
				t->right->parent = NKO;
			}
			NKO->left = t->left;
			t->left->parent = NKO;
			NKO->parent, t->parent;

			numbers++;
			if (t != Root)
			{
				numbers++;
				if (t->parent->right == t)
				{
					t->parent->right = NKO;
				}
				else t->parent->left = NKO;
			}
			else Root = NKO;


			char tmp = NKO->colour;
			NKO->colour= t->colour;
			t->colour = tmp;

			numbers++;
			if (NKO_Child != nil)
			{
				fix_remove(NKO_Child);
			}
			else
			{
				numbers++;
				if (t != NKO_Parent)
				{
					t->parent = NKO_Parent;
				}
				else t->parent = NKO;
				fix_remove(t);
			}
		}
		delete t;
	}//_____________________
	 //			/|\			
	 //		   / | \		
	 //		  /  |  \		
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //			 |			
	 //	      \  |  /		
	 //		   \ | /		
	 //_________\|/_________
	void fix_remove(Node* t)
	{
		numbers++;
		if (t->colour == 'r')
		{
			t->colour = 'b';
			return;
		}

		Node* Parent = nullptr;
		Node* Brother = nullptr;

		numbers++;
		while (t != Root && t->colour == 'b')
		{
			numbers++;

			Parent = t->parent;

			numbers++;
			if (t == Parent->left || Parent->left == nil) //    (  <--  )
			{
				Brother = Parent->right;

				numbers++;
				if (Brother->colour == 'r' ) 
				{
					Parent->colour = 'r';
					Brother->colour = 'b'; 
					rotateLeft(Brother);
				}
				else 
				{
					numbers++;
					if (Brother->right->colour == 'b' && Brother->left->colour == 'b')
					{
						Brother->colour = 'r';

						numbers++;
						if (Parent->colour == 'r')
						{
							Parent->colour = 'r';
							break;
						}
						t = Parent;
					}
					else if (++numbers && Brother->right->colour == 'r')
					{
						Brother->colour = Parent->colour;
						Brother->right->colour = 'b';
						Parent->colour = 'b';
						rotateLeft(Brother);
						break;
					}
					else if (++numbers && Brother->left->colour == 'r')
					{
						Brother->left->colour = 'b'; 
						Brother->colour = 'r';
						rotateRight(Brother->left);
					}
					
				}
			}
			else //    (  -->  )
			{
				Brother = Parent->left;

				numbers++;
				if (Brother->colour =='r') 
				{
					Parent->colour = 'r';
					Brother->colour = 'b';
					rotateRight(Brother);
				}
				else 
				{

					numbers++;
					if (Brother->left->colour == 'b' && Brother->right->colour == 'b')
					{
						Brother->colour = 'r';

						numbers++;
						if (Parent->colour == 'r')
						{
							Parent->colour='b';
							break;
						}
						t = Parent;
					}
					else if (++numbers && Brother->left->colour == 'r')
					{
						Brother->colour = Parent->colour;
						Brother->left->colour = 'b';
						Parent->colour = 'b';
						rotateRight(Brother);
						break;
					}
					else if (++numbers && Brother->right->colour == 'r' )
					{
						Brother->right->colour = 'b'; 
						Brother->colour = 'r'; 
						rotateLeft(Brother->right);
					}
					
				}
			}
		}
		Root->colour = 'b';
	}
	


};