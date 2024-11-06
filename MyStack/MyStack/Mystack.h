#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
using namespace std;

template <class _TY>
class mystack
{
public:
    mystack<_TY>();
    mystack<_TY>(mystack<_TY> &s);
    ~mystack();
    bool isEmpty();
    bool push(_TY item);
    bool pop(_TY &item);
    bool top(_TY &item);
    int size();
private:
    int count;
    struct node
    {
        node *next;
        _TY item;
    };
    node *headptr;
    node *tailptr;
};

template <class _TY>
mystack::mystack<_TY>()
{
    headptr = new (nothrow)node;
    if (headptr == nullptr)
        return;
    headptr = nullptr;
    headptr->next = nullptr;
    headptr->item = 0;
    tailptr = new (nothrow)node;
    if (tailptr == nullptr)
        return;
    tailptr = nullptr;
    tailptr->next = nullptr;
    tailptr->item = 0;
    count = 0;

}

//template <class _TY>
//mystack::mystack<_TY>(mystack<_TY> &s)
//{
//    node *src;
//    node *dest;
//    headptr = nullptr;
//    if (s.isEmpty)
//    {
//        return;
//    }
//    headptr = new (nothrow)node;
//    if (headptr == nullptr)
//        return;
//    headptr->item = s.headptr->item;
//    headptr->next = nullptr;
//    src = s.headptr->next;
//    dest = headptr;
//    while (src != nullptr)
//    {
//        dest->next = new (nothrow)node;
//        if (dest->next == nullptr)
//            return;
//        dest = dest->next;
//        dest->next = nullptr;
//        dest->item = src->item;
//        src = src->next;
//    }
//}

template <class _TY>
mystack::~mystack()
{
    delete [] headptr;
    headptr = nullptr;
    headptr->next = nullptr;
    tailptr = nullptr;
    tailptr->next = nullptr;
}

template <class _TY>
bool mystack::isEmpty()
{
    return(headptr == nullptr ? true : false);
}

template <class _TY>
bool mystack::push(_TY item)
{
    node *temp;
    node *curr;
    node *prev;
    temp = new (nothrow)node;
    if (temp == nullptr)
        return false;
    temp->next = nullptr;
    temp->item = item;
    if (headptr == nullptr)
    {
        headptr = temp;
        tailptr = temp;
        count += 1;
        return true;
    }
    tailptr->next = temp;
    tailptr = temp;
    count += 1;
    return true;
}

template <class _TY>
bool mystack::pop(_TY &item)
{
    node *temp;
    node *prev;
    node *curr;
    if (headptr == nullptr)
        return false;
    prev = headptr;
    curr = headptr;
    while (curr != tailptr)
    {
        prev = curr;
        curr = curr->next;
    }
    temp = tailptr;
    tailptr = prev;
    item = temp->item;
    delete[] temp;
    count -= 1;
    return true;

}

template <class _TY>
bool mystack::top(_TY &item)
{
    if (headptr == nullptr)
        return false;
    item = tailptr->item;
    return true;

}

template <class _TY>
int mystack::size()
{
    return count;
}