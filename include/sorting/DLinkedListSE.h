/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list){
        this->copyFrom(list);
    }
    
   void sort(int (*comparator)(T&, T&) = 0) {
    cout<<"a";
    this->head = mergeSort(this->head, comparator);

    // Cập nhật tail và count
    this->tail = this->head;
    this->count = 0;
    typename DLinkedList<T>::Node* current = this->head;

    while (current != nullptr) {
        this->count++;
        if (current->next == nullptr) this->tail = current;
        current = current->next;
    }
}
private:
typename DLinkedList<T>::Node* split(typename DLinkedList<T>::Node* head) {
    if (!head || !head->next) return nullptr;

    typename DLinkedList<T>::Node* slow = head;
    typename DLinkedList<T>::Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    typename DLinkedList<T>::Node* secondHalf = slow->next;
    slow->next = nullptr;
    if (secondHalf) secondHalf->prev = nullptr; // Đảm bảo prev của nửa sau là nullptr

    return secondHalf;
}

typename DLinkedList<T>::Node* merge(typename DLinkedList<T>::Node* left,
                                     typename DLinkedList<T>::Node* right,
                                     int (*comparator)(T&, T&) = 0) {
    typename DLinkedList<T>::Node dummy;
    typename DLinkedList<T>::Node* current = &dummy;

    while (left && right) {
        if (compare(left->data, right->data, comparator) <= 0) {
            current->next = left;
            left->prev = current;
            left = left->next;
        } else {
            current->next = right;
            right->prev = current;
            right = right->next;
        }
        current = current->next;
    }

    if (left) {
        current->next = left;
        left->prev = current;
    }
    if (right) {
        current->next = right;
        right->prev = current;
    }

    return dummy.next;
}

typename DLinkedList<T>::Node* mergeSort(typename DLinkedList<T>::Node* head,
                                         int (*comparator)(T&, T&) = 0) {
    if (!head || !head->next) return head;

    typename DLinkedList<T>::Node* second = split(head);

    typename DLinkedList<T>::Node* leftSorted = mergeSort(head, comparator);
    typename DLinkedList<T>::Node* rightSorted = mergeSort(second, comparator);

    return merge(leftSorted, rightSorted, comparator);
}   
protected:
    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */
