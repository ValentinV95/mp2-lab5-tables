#include<iostream>
#include"polinoms.h"
#include"THashTable.h"
#include"TRBtree.h"
#include"TUnorderedTable.h"
#include<locale>


void Insert(THashTable<string, Polinom>& hash,
    TUnorderedTable<string, Polinom>& arr,
    TRBTreeTable<string, Polinom>& rb,
    Polinom pol)
{
    cout << "Введите имя полинома:" << endl;
    string polName;
    cin >> polName;

    try 
    {
        hash.Insert(polName, pol);
        cout << "HashTable." << hash.log() << endl;
        arr.Insert(polName, pol);
        cout << "UnorderedTable." << arr.log() << endl;
        rb.Insert(polName, pol);
        cout << "RBTreeTable." << rb.log() << endl;
    }catch(exception& ex)
    {
        cout << ex.what();
    }
}

Polinom Find(THashTable<string, Polinom>& hash,
    TUnorderedTable<string, Polinom>& arr,
    TRBTreeTable<string, Polinom>& rb)
{
    cout << "Введите имя полинома:" << endl;
    string polName;
    cin >> polName;

    try 
    {
        auto& res = hash.Find(polName);
        cout << "HashTable." << hash.log() << endl;
        arr.Find(polName);
        cout << "UnorderedTable." << arr.log() << endl;
        rb.Find(polName);
        cout << "RBTreeTable." << rb.log() << endl;
        return res;
    }catch(exception& ex)
    {
        cout << ex.what() << endl;
    }
    return Polinom();
}


void Delete(THashTable<string, Polinom>& hash,
    TUnorderedTable<string, Polinom>& arr,
    TRBTreeTable<string, Polinom>& rb)
{
    cout << "Введите имя полинома:" << endl;
    string polName;
    cin >> polName;

    try 
    {
        hash.Delete(polName);
        cout << "HashTable." << hash.log() << endl;
        arr.Delete(polName);
        cout << "UnorderedTable." << arr.log() << endl;
        rb.Delete(polName);
        cout << "RBTreeTable." << rb.log() << endl;
    }catch(exception& ex)
    {
        cout << ex.what() << endl;
    }
}

void Arifmetic(THashTable<string, Polinom>& hash,
    TUnorderedTable<string, Polinom>& arr,
    TRBTreeTable<string, Polinom>& rb)
{
    Polinom pol1;
    Polinom pol2;
    Polinom res;
    int save = 0;

    cout << "Выберите операцию:" << endl
        << "<*> умножить два полинома" << endl
        << "<+> сложить два полинома" << endl
        << "<-> взять разность полиномов" << endl;
    char op = 0;
    cin >> op;

    cout << "Введите первый полином:" << endl;
    cin >> pol1;
    cout << "Сохранить полином? 1 - да, 0 - нет" << endl;
    cin >> save;
    if (save)
    {
        Insert(hash, arr, rb, pol1);
        save = 0;
    }
    cout << "Введите второй полином:" << endl;
    cin >> pol2;
    cout << "Сохранить полином? 1 - да, 0 - нет" << endl;
    cin >> save;
    if (save)
    {
        Insert(hash, arr, rb, pol2);
        save = 0;
    }

    switch(op)
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
        cout << "Неверная операция!" << endl;
    }
    
    cout << "\n\nРtзультат:" << res << endl;
    cout << "Сохранить полином? 1 - да, 0 - нет" << endl;
    cin >> save;
    if (save)
    {
        Insert(hash, arr, rb, res);
        save = 0;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "|Тестирование таблиц, основанных на разных структурах данных|" << endl
        << "В данном приложении возможны следующие операции над алгебраическими полиномами:" << endl
        << "Ввод, сохранение, удаление, поиск по имени и арифметичские операции (+,-,*)" << endl
        << "Операции сохраниния, удаления и поиска осуществляются одновременной работой с тремя таблицами" << endl
        << "Таблица, реализованная как неупорядоченный массив, Красно-чёрное дерево и Хэш таблица" << endl
        << "Чтобы произвести арифметическую операцию над полиномом, необходимо взять его из таблицы (найти)" << endl;

    THashTable<string, Polinom> hashTable(1000);
    TUnorderedTable<string, Polinom> arrTable;
    TRBTreeTable<string, Polinom> RBTTable;

    while(true)
    {
        cout << "Выберите операцию:" << endl
            << "<1> создать и сохранить полином." << endl
            << "<2> найти полином." << endl
            << "<3> удалить полином." << endl
            << "<4> Выполнить арифметическую операцию" << endl
            << "<5> Закрыть приложение" << endl;

        char choose = 0;
        cin >> choose;
        Polinom pol;

        switch(choose)
        {
        case '1':
            cout << "Введите полином:" << endl;
            cin >> pol;
            Insert(hashTable, arrTable, RBTTable, pol);
            break;
        case '2':
            cout << Find(hashTable, arrTable, RBTTable) << endl;
            break;
        case '3':
            Delete(hashTable, arrTable, RBTTable);
            break;
        case '4':
            Arifmetic(hashTable, arrTable, RBTTable);
            break;
        case '5':
            exit(0);
        default:
            cout << "Неверный ввод!" << endl;
        }
    }
}
