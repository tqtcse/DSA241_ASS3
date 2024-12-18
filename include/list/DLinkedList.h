
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "list/IList.h"

#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class DLinkedList : public IList<T>
{
public:
    class Node;        // Forward declaration
    class Iterator;    // Forward declaration
    class BWDIterator; // Forward declaration

protected:
    Node *head; // this node does not contain user's data
    Node *tail; // this node does not contain user's data
    int count;
    bool (*itemEqual)(T &lhs, T &rhs);        // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(DLinkedList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    DLinkedList(
        void (*deleteUserData)(DLinkedList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0);
    DLinkedList(const DLinkedList<T> &list);
    DLinkedList<T> &operator=(const DLinkedList<T> &list);
    ~DLinkedList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(DLinkedList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    bool contains(T array[], int size)
    {
        int idx = 0;
        for (DLinkedList<T>::Iterator it = begin(); it != end(); it++)
        {
            if (!equals(*it, array[idx++], this->itemEqual))
                return false;
        }
        return true;
    }

    static void free(DLinkedList<T> *list)
    {
        typename DLinkedList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }

    BWDIterator bbegin()
    {
        return BWDIterator(this, true);
    }
    BWDIterator bend()
    {
        return BWDIterator(this, false);
    }

protected:
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }
    void copyFrom(const DLinkedList<T> &list);
    void removeInternalData();
    Node *getPreviousNodeOf(int index);

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;
        friend class DLinkedList<T>;

    public:
        Node(Node *next = 0, Node *prev = 0)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next = 0, Node *prev = 0)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    //////////////////////////////////////////////////////////////////////
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *pNode;

    public:
        Iterator(DLinkedList<T> *pList = 0, bool begin = true)
        {
            if (begin)
            {
                if (pList != 0)
                    this->pNode = pList->head->next;
                else
                    pNode = 0;
            }
            else
            {
                if (pList != 0)
                    this->pNode = pList->tail;
                else
                    pNode = 0;
            }
            this->pList = pList;
        }

        Iterator &operator=(const Iterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node *pNext = pNode->prev; // MUST prev, so iterator++ will go to end
            if (removeItemData != 0)
                removeItemData(pNode->data);
            delete pNode;
            pNode = pNext;
            pList->count -= 1;
        }

        T &operator*()
        {
            return pNode->data;
        }
        bool operator!=(const Iterator &iterator)
        {
            return pNode != iterator.pNode;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            pNode = pNode->next;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };

    class BWDIterator{
    private:
        DLinkedList<T> *pList;
        Node* pNode;
    public:  
        BWDIterator(DLinkedList<T> *pList = 0, bool begin = true){
            if(begin)
            {
                if(pList != 0){
                    this->pNode = pList->tail->prev;
                } else {
                    pNode = 0;
                }
            } else {
                if(pList != 0){
                    this->pNode = pList->head;
                } else {
                    pNode = 0;
                }
            }
            this->pList = pList;
        }
        BWDIterator &operator=(const BWDIterator &iterator)
        {
            this->pNode = iterator.pNode;
            this->pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            pNode->prev->next = pNode->next;
            pNode->next->prev = pNode->prev;
            Node* pPrev = pNode->next;
            if(removeItemData){
                removeItemData(pNode->data);
            }
            delete pNode;
            pNode = pPrev;
            pList->count -= 1;
            
        }
        T &operator*()
        {
            return pNode->data;
        }

        bool operator!=(const BWDIterator &iterator)
        {
            return pNode != iterator.pNode;
        }

        BWDIterator &operator--()
        {
            pNode = pNode->prev;
            return *this;
        }

    
        BWDIterator operator--(int)
        {
            BWDIterator bwditerator = *this;
            --*this;
            return bwditerator;
        }
        BWDIterator &operator++()
        {
            pNode = pNode->prev;
            return *this;
        }
        BWDIterator operator++(int){
            BWDIterator bwditerator = *this;
            ++*this;
            return bwditerator;
        }
    };

};
//////////////////////////////////////////////////////////////////////
// Define a shorter name for DLinkedList:

template <class T>
using List = DLinkedList<T>;

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
DLinkedList<T>::DLinkedList(
    void (*deleteUserData)(DLinkedList<T> *),bool (*itemEqual)(T &, T &))
{
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
    this->count = 0;

    this->head = new Node();
    this->tail = new Node();

    head->next = tail;
    tail->prev = head;
}


template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList<T> &list)
{   
     
    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;
    this->count = 0;
    // cout<<"HIIIII"<<endl;
    this->head = new Node();
    this->tail = new Node();
    head->next = tail;
    tail->prev = head;
    // cout<<list.head->next->data;
    // cout<<"HIIIEEEEII"<<endl;

    Node* current = list.head->next;

    while(current != list.tail){
       
        this->add(current->data);
        current = current->next;
    }

}


template <class T>
DLinkedList<T> &DLinkedList<T>::operator=(const DLinkedList<T> &list)
{
    if (this == &list){
        return *this;
    }

    this->clear();

    this->deleteUserData = list.deleteUserData;
    this->itemEqual = list.itemEqual;

    Node* current = list.head->next;
    while(current != list.tail){
        this->add(current->data);
        current = current->next;
    }
    return *this;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
    if(deleteUserData){
        deleteUserData(this);
    }
    Node* current = head;
    while(current != nullptr){
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

template <class T>
void DLinkedList<T>::add(T e)
{
    Node* newNode = new Node(e);
        
        tail->prev->next = newNode;
        newNode->prev = tail->prev;
        
        newNode->next = tail;
        tail->prev = newNode;
        
        count++;
    
}
template <class T>
void DLinkedList<T>::add(int index, T e)
{
    if(index < 0 || index > count){
        throw out_of_range("Index is out of range!");
    }
    
    Node* newNode = new Node(e);
    
    if(index == 0){
        if(count == 0){

            head->next = newNode;
            newNode->prev = head;

            newNode->next = tail;
            tail->prev = newNode;
        } else {
            newNode->next = head->next;
            head->next->prev = newNode;

            head->next = newNode;
            newNode->prev = head;
        }
    }
    else if(index == count){
        
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        
        tail->prev = newNode;
        newNode->next = tail;
        
    } else {
        
        Node* prevNode = head->next;
        
        for(int i = 1; i <= index; i++){
            
            if(index == i){
                newNode->next = prevNode->next;
                prevNode->next->prev = newNode;
            
                prevNode->next = newNode;
                newNode->prev = prevNode;
            }
            
            prevNode = prevNode->next;
        }
    }
    count++;
}

template <class T>
typename DLinkedList<T>::Node *DLinkedList<T>::getPreviousNodeOf(int index)
{
    if(index < 0 || index >= count){
        throw out_of_range("Index is out of range!");
    }
    Node* current;
    if(index < count/2){
        current = head->next;
        for(int i = 0; i < index - 1; i++){
            current = current->next;
        }
    } else {
        current = tail->prev;
        for(int i = count - 1; i > index-1; i--){
            current = current->prev;
        }
    }

    return current;
}

template <class T>
T DLinkedList<T>::removeAt(int index)
{
    if(index < 0 || index >= count){
        throw out_of_range("Index is out of range!");
    }
    
    Node* deleteNode;
    T data;
    
    
    if(index == 0){
        deleteNode = head->next;
        
        head->next = deleteNode->next;
        deleteNode->next->prev = head;
        
    }
    
    else if(index == count-1){
        deleteNode = tail->prev;
        
        tail->prev = deleteNode->prev;
        deleteNode->prev->next = tail;
    } else {
        
        Node* prevNode = head->next;
        
        for(int i = 1; i <= index; i++){
            
            if(i == index){
                deleteNode = prevNode->next;
                
                prevNode->next = deleteNode->next;
                deleteNode->next->prev = prevNode;
            }
            
            prevNode = prevNode->next;
            
        }
        
    }
    
    data = deleteNode->data;
    delete deleteNode;
    count--;
    
    return data;
}

template <class T>
bool DLinkedList<T>::empty()
{
    if(count == 0){
        return true;
    } else {
        return false;
    }
}

template <class T>
int DLinkedList<T>::size()
{
    return count;
}

template <class T>
void DLinkedList<T>::clear()
{
    while(!empty()){
        removeAt(0);
    }
}

template <class T>
T &DLinkedList<T>::get(int index)
{
    if(index < 0 || index >= count){
        throw out_of_range("Index is out of range!");
    }
    Node* current = head->next;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    
    return current->data;
}

template <class T>
int DLinkedList<T>::indexOf(T item)
{
    // Node* current = head->next;
    // int i = 0;
    
    // while (current != tail){
    //     if(current->data == item){
    //         return i;
    //     }
    //     i++;
    //     current = current->next;
    // }
    // return -1;
    Node* current = head->next;
    int i = 0;

    while (current != tail) {
        if (equals(current->data, item, itemEqual)) {
            return i;
        }
        i++;
        current = current->next;
    }
    return -1;
}

template <class T>
bool DLinkedList<T>::removeItem(T item, void (*removeItemData)(T))
{
    Node* current = head->next;
    
    while(current != tail){
        
        // if(current->data == item){
        //     current->prev->next = current->next;
        //     current->next->prev = current->prev;
            
        //     if(removeItemData){
        //         removeItemData(current->data);
        //     }
            
        //     delete current;
        //     count--;
            
        //     return true;
        // }


        if(equals(current->data, item, itemEqual)){
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            count--;
            return true;
        }
        
        current = current->next;
    }
    return false;
}

template <class T>
bool DLinkedList<T>::contains(T item)
{
    if (indexOf(item) != -1){
        return true;
    } else {
        return false;
    }
}

template <class T>
string DLinkedList<T>::toString(string (*item2str)(T &))
{
    stringstream ss;
    ss << "[";
    
    Node* current = head->next;
    while(current != tail){
        if(item2str){
            ss << item2str(current->data);
        } else {
            ss << current->data;
        }
        
        current = current->next;
        if(current != tail){
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

template <class T>
void DLinkedList<T>::copyFrom(const DLinkedList<T> &list)
{

    Node* current = list.head->next;
    while(current != tail){
        this->add(current->data);
        current = current->next;
    }
}

template <class T>
void DLinkedList<T>::removeInternalData()
{
    Node* current = head->next;
    while(current != tail){
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head->next = tail;
    tail->prev = head;
    count = 0;
}

#endif /* DLINKEDLIST_H */