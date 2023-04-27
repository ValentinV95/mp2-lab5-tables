#include "TAVLtable.h"
#include "THashTable.h"
#include "TUnorderedTable.h"
#include "polinoms.h"

void Insert(TAVLtable<Polinom>& avl, THashTable<Polinom>& hash, TUnorderedTable<Polinom>& arr, string polinomName, Polinom polinom)
{
    try
    {
        avl.Insert(polinomName, polinom);
        cout << endl << endl << "AVLTreeTable." << avl.logging() << endl;
        hash.Insert(polinomName, polinom);
        cout << "HashTable." << hash.logging() << endl;
        arr.Insert(polinomName, polinom);
        cout << "UnorderedTable." << arr.logging() << endl << endl;
    }
    catch (exception& ex)
    {
        cout << ex.what();
        exit(EXIT_FAILURE);
    }
}

Polinom Search(TAVLtable<Polinom>& avl, THashTable<Polinom>& hash, TUnorderedTable<Polinom>& arr, string polinomName)
{
    try
    {
        Polinom res = avl.Search(polinomName);
        cout << endl << endl << "AVLTreeTable." << avl.logging() << endl;
        arr.Search(polinomName);
        cout << "UnorderedTable." << arr.logging() << endl;
        hash.Search(polinomName);
        cout << "HashTable." << hash.logging() << endl << endl;
        return res;
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
        exit(EXIT_FAILURE);
    }
    return Polinom();
}


void Delete(TAVLtable<Polinom>& avl, THashTable<Polinom>& hash, TUnorderedTable<Polinom>& arr, string polinomName)
{
    try
    {
        avl.Delete(polinomName);
        cout << endl << endl << "AVLTreeTable." << avl.logging() << endl;
        hash.Delete(polinomName);
        cout << "HashTable." << hash.logging() << endl;
        arr.Delete(polinomName);
        cout << "UnorderedTable." << arr.logging() << endl << endl;
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void Arifmetic(TAVLtable<Polinom>& avl, THashTable<Polinom>& hash, TUnorderedTable<Polinom>& arr, string PolName1, string PolName2)
{
    try
    {
        Polinom pol1 = avl.Search(PolName1);
        Polinom pol2 = avl.Search(PolName2);;
        Polinom res;
        int save = 0;

        cout << "Choose the operation:" << endl
            << "<*> multiply two polynomials" << endl
            << "<+> add two polynomials" << endl
            << "<-> subtract two polynomials" << endl;
        char op = 0;
        cin >> op;

        switch (op)
        {
        case'*':
            res = pol1 * pol2;
            break;
        case'+':
            res = pol1 + pol2;
            break;
        case'-':
            res = pol1 - pol2;
            break;
        default:
            cout << "Wrong operation!" << endl;
        }

        cout << "\n\nResult:" << res << endl;
        cout << "Do you want to save the polynomial? 1 - yes, 0 - no" << endl;
        cin >> save;
        if (save)
        {
            string resName;
            cout << "Enter the name of the polynomial:" << endl;
            cin >> resName;
            Insert(avl, hash, arr, resName, res);
            save = 0;
        }
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
        exit(EXIT_FAILURE);
    }
}

int main()
{
    cout << "The program works with 3 types of tables at once : AVL tree, hash table, unordered table." << endl
        << "The program can create and save a polynomial, find a polynomial, delete a polynomial from a table, perform an arithmetic operation with polynomials that already exist in the table." << endl;

    TAVLtable<Polinom> AVLTable;
    THashTable<Polinom> hashTable;
    TUnorderedTable<Polinom> arrTable;

    bool exit = false;
    while (!exit)
    {
        cout << "Choose the operation:" << endl
            << "<1> create and save a polynomial." << endl
            << "<2> find a polynomial." << endl
            << "<3> delete a polynomial." << endl
            << "<4> perform an arithmetic operation" << endl
            << "<5> show the table" << endl
            << "<6> exit" << endl;

        int choose = 0;
        cin >> choose;
        Polinom polinom;
        string PolName1, PolName2;
        if (choose == 1)
        {
            cout << "Enter the polynomial:" << endl;
            polinom.Set();
            cout << "Enter the name of the polynomial:" << endl;
            cin >> PolName1;
            Insert(AVLTable, hashTable, arrTable, PolName1, polinom);
        }
        else if (choose == 2)
        {
            cout << "Enter the name of the polynomial:" << endl;
            cin >> PolName1;
            Search(AVLTable, hashTable, arrTable, PolName1).Print();
            cout << endl;
        }
        else if (choose == 3)
        {
            cout << "Enter the name of the polynomial:" << endl;
            cin >> PolName1;
            Delete(AVLTable, hashTable, arrTable, PolName1);
        }
        else if (choose == 4)
        {
            string PolName1, PolName2;
            cout << "Enter the name of the first polynomial" << endl;
            cin >> PolName1;
            cout << "Enter the name of the second polynomial" << endl;
            cin >> PolName2;
            Arifmetic(AVLTable, hashTable, arrTable, PolName1, PolName2);
        }
        else if (choose == 5)
        {
            hashTable.Print();
        }
        else if (choose == 6)
            exit = true;
        else
            cout << "Wrong enter" << endl;
    }
}