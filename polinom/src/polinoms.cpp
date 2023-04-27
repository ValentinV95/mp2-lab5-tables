#include "polinoms.h"

void Polinom::Set()
{
    polinom.clear();
    int tmp = 0;
        do
        {
            cout << "Enter 1 to add a monom or 0 to finish the input" << endl;
            cin >> tmp;
            if (tmp == 1)
            {
                double coef = 0;
                int deg = 0, deg_tmp = 0;
                cout << "Enter the coef" << endl;
                cin >> coef;
                if (std::cin.fail())
                {
                    throw exception("Coef error");
                }
                cout << "x^";
                cin >> deg_tmp;
                if (std::cin.fail() || deg_tmp > 9 || deg_tmp < 0)
                {
                    throw exception("X-degree error");
                }
                deg += deg_tmp * 100;
                cout << "y^";
                cin >> deg_tmp;
                if (std::cin.fail() || deg_tmp > 9 || deg_tmp < 0)
                {
                    throw exception("Y-degree error");
                }
                deg += deg_tmp * 10;
                cout << "z^";
                cin >> deg_tmp;
                if (std::cin.fail() || deg_tmp > 9 || deg_tmp < 0)
                {
                    throw exception("Z-degree error");
                }
                deg += deg_tmp;
                if (coef != 0)
                {
                    Monom monom(deg, coef);
                    polinom.sortInsert(monom);
                }
            }
            else if (tmp != 0 && tmp != 1)
            {
                throw exception("Input error");
            }
        } while (tmp != 0);
}
void Polinom::Print()
{
    ListNode<Monom>* p = polinom.getFirst();
    if (p == NULL)
        cout << 0;
    else
    {
        cout << "(" << p->data << ")";
        p = p->next;
        while (p)
        {
            cout << " + (" << p->data << ")";
            p = p->next;
        }
        cout << endl;
    }
}
Polinom Polinom::operator+(Polinom& other)
{
    Polinom res;
    ListNode<Monom>* ptr_p1 = polinom.getFirst();
    ListNode<Monom>* ptr_p2 = other.polinom.getFirst();
    ListNode<Monom>* ptr_res;
    bool isMonomUnique;
    while (ptr_p1 && ptr_p2)
    {
        ptr_res = res.polinom.getFirst();
        isMonomUnique = true;
        if (ptr_p1->data < ptr_p2->data)
        {
            while (ptr_res && isMonomUnique)
            {
                if (ptr_res->data == ptr_p2->data)
                {
                    ptr_res->data = ptr_res->data + ptr_p2->data;
                    isMonomUnique = false;
                }
                ptr_res = ptr_res->next;
            }
            if (isMonomUnique)
                res.polinom.sortInsert(ptr_p2->data);
            ptr_p2 = ptr_p2->next;
        }
        else if (ptr_p1->data == ptr_p2->data)
        {
            if (ptr_p1->data.getCoef() + ptr_p2->data.getCoef() != 0)
            {
                while (ptr_res && isMonomUnique)
                {
                    if (ptr_res->data == ptr_p1->data + ptr_p2->data)
                    {
                        ptr_res->data = ptr_res->data + ptr_p1->data;
                        ptr_res->data = ptr_res->data + ptr_p2->data;
                        isMonomUnique = false;
                    }
                    ptr_res = ptr_res->next;
                }
                if (isMonomUnique)
                {
                    Monom tmp(ptr_p1->data.getDeg(), ptr_p1->data.getCoef() + ptr_p2->data.getCoef());
                    res.polinom.sortInsert(tmp);
                }
            }
            ptr_p1 = ptr_p1->next;
            ptr_p2 = ptr_p2->next;
        }
        else
        {
            while (ptr_res && isMonomUnique)
            {
                if (ptr_res->data == ptr_p1->data)
                {
                    ptr_res->data = ptr_res->data + ptr_p1->data;
                    isMonomUnique = false;
                }
                ptr_res = ptr_res->next;
            }
            if (isMonomUnique)
                res.polinom.sortInsert(ptr_p1->data);
            ptr_p1 = ptr_p1->next;
        }
    }
    while (ptr_p1)
    {
        ptr_res = res.polinom.getFirst();
        isMonomUnique = true;
        while (ptr_res && isMonomUnique)
        {
            if (ptr_res->data == ptr_p1->data)
            {
                ptr_res->data = ptr_res->data + ptr_p1->data;
                isMonomUnique = false;
            }
            ptr_res = ptr_res->next;
        }
        if (isMonomUnique)
            res.polinom.sortInsert(ptr_p1->data);
        ptr_p1 = ptr_p1->next;
    }
    while (ptr_p2)
    {
        ptr_res = res.polinom.getFirst();
        isMonomUnique = true;
        while (ptr_res && isMonomUnique)
        {
            if (ptr_res->data == ptr_p2->data)
            {
                ptr_res->data = ptr_res->data + ptr_p2->data;
                isMonomUnique = false;
            }
            ptr_res = ptr_res->next;
        }
        if (isMonomUnique)
            res.polinom.sortInsert(ptr_p2->data);
        ptr_p2 = ptr_p2->next;
    }
    return res;
}
Polinom Polinom::operator*(double coef)
{
    Polinom res;
    ListNode<Monom>* p = polinom.getFirst();
    while (p)
    {
        if (p->data.getCoef() * coef != 0)
        {
            Monom tmp(p->data.getDeg(), p->data.getCoef() * coef);
            res.polinom.sortInsert(tmp);
        }
        p = p->next;
    }
    return res;
}
Polinom Polinom::operator-(Polinom& other)
{
    Polinom tmp = other * (-1.0);
    return *this + tmp;
}
Polinom Polinom::operator*(Polinom& other)
{
    Polinom res;
    ListNode<Monom>* ptr_p1 = polinom.getFirst();
    ListNode<Monom>* ptr_p2 = other.polinom.getFirst();
    while (ptr_p1)
    {
        Polinom add;
        while (ptr_p2)
        {
            int fdeg = ptr_p1->data.getDeg() + ptr_p2->data.getDeg();
            if (fdeg % 10 < ptr_p1->data.getDeg() % 10)
            {
                throw exception("Z-degree error");
            }
            if (fdeg / 10 % 10 < ptr_p1->data.getDeg() / 10 % 10)
            {
                throw exception("Y-degree error");
            }
            if (fdeg / 100 % 10 < ptr_p1->data.getDeg() / 100)
            {
                throw exception("X-degree error");
            }
            Monom tmp(fdeg, ptr_p1->data.getCoef() * ptr_p2->data.getCoef());
            add.polinom.sortInsert(tmp);
            ptr_p2 = ptr_p2->next;
        }
        res = res + add;
        ptr_p2 = other.polinom.getFirst();
        ptr_p1 = ptr_p1->next;
    }
    return res;
}

ostream& operator<<(ostream& ostr, Polinom& _polinom)
{
    ListNode<Monom>* p = _polinom.getPolinom().getFirst();
    if (p == NULL)
        ostr << 0;
    else
    {
        ostr << "(" << p->data << ")";
        p = p->next;
        while (p)
        {
            ostr << " + (" << p->data << ")";
            p = p->next;
        }
        ostr << endl;
    }
    return ostr;
}
