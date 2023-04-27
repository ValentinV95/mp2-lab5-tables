#pragma once

#include <iostream>

using namespace std;

template <class T>
struct ListNode
{
    T data;
    ListNode* next;
    ListNode() : next(nullptr) {};
    ListNode(T val) : data(val), next(nullptr) {};
};

template <class T>
class List
{
private:
    ListNode<T>* head;
public:
    List() : head(new ListNode<T>) {}
    List(const List& other) : head(new ListNode<T>)
    {
        ListNode<T>* p = other.head->next;
        while (p)
        {
            this->sortInsert(p->data);
            p = p->next;
        }
    }
    List& operator=(const List& other)
    {
        if (this == &other)
            return *this;
        this->~List();
        head = new ListNode<T>;
        ListNode<T>* p = other.head->next;
        while (p)
        {
            this->sortInsert(p->data);
            p = p->next;
        }
        return *this;
    }
    bool isEmpty() { return head->next == NULL; }
    ListNode<T>* getFirst() { return head->next; }
    void sortInsert(const T& val)
    {
        ListNode<T>* elem = new ListNode<T>(val);
        ListNode<T>* p = head;
        if (isEmpty())
        {
            p->next = elem;
            p = elem;
        }
        else
        {
            ListNode<T>* p_next = head->next;
            while (p_next && elem->data < p_next->data)
            {
                p = p->next;
                p_next = p_next->next;
            }
            elem->next = p_next;
            p->next = elem;
        }
    }
    void clear()
    {
        ListNode<T>* p = head;
        while (p->next)
        {
            ListNode<T>* nextNode = p->next;
            delete p;
            p = nextNode;
        }
        delete p;
        head = new ListNode<T>;
    }
    ~List()
    {
        ListNode<T>* p = head;
        while (p->next)
        {
            ListNode<T>* nextNode = p->next;
            delete p;
            p = nextNode;
        }
        delete p;
    }
};