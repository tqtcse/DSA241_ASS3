/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 * Author: LTSACH
 *
 * Created on 19 August 2020, 22:01
 */

#ifndef STACK_H
#define STACK_H

#include <list>

#include "list/DLinkedList.h"
#include "stacknqueue/IDeck.h"

template<class T>
class Stack: public IDeck<T>{
public:
    class Iterator; //forward declaration
    
protected:
    DLinkedList<T> list; //internal list
    void (*deleteUserData)(DLinkedList<T>*); //function pointer: be called to remove items (if they are pointer type)
    bool (*itemEqual)(T& lhs, T& rhs); //function pointer: test if two items (type: T&) are equal or not
    
public:
    Stack(  void (*deleteUserData)(DLinkedList<T>*)=0, 
            bool (*itemEqual)(T&, T&)=0){
        this->itemEqual = itemEqual;
        this->deleteUserData = deleteUserData;
    }
    void push(T item){
         list.add(item);
    }
    T pop(){
        if (empty()) throw std::out_of_range("Stack is empty!");
    T topItem = list.get(list.size() - 1); // Get the last element
    list.removeAt(list.size() - 1);       // Remove it from the list
    return topItem;
    }
    T& peek(){
        if (empty()) throw std::out_of_range("Stack is empty!");
    return list.get(list.size() - 1);
    }    
    bool empty(){
       return list.size() == 0;
    }
    int size(){
        return list.size();
    }
    void clear(){
        list.clear();
    }
    bool remove(T item){
       int index = list.indexOf(item);
    if (index >= 0) {
        list.removeAt(index);
        return true;
    }
    return false;
    }
    bool contains(T item){
        return list.contains(item);
    }
    string  toString(string (*item2str)(T&)=0 ){
        stringstream os;
        os << "FROM TOP: " << list.toString(item2str);
        return os.str();
    }
    void println(string (*item2str)(T&)=0 ){
        cout << toString(item2str) << endl;
    }
    ///
    Iterator top(){
        return Iterator(this, true);
    }
    Iterator bottom(){
        return Iterator(this, false);
    }
    
    
private:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T& )){
        if(itemEqual == 0) return lhs == rhs;
        else return itemEqual(lhs, rhs);
    }
    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
    
public:
    
//Iterator: BEGIN
    class Iterator{
    private:
        Stack<T>* stack;
        typename DLinkedList<T>::Iterator listIt;
    public:
        Iterator(Stack<T>* stack=0, bool begin=true){
            this->stack = stack;
            if(begin){
                if(stack != 0) this->listIt = stack->list.begin();
                else this->listIt = 0;
            }
            else{
                if(stack != 0) this->listIt = stack->list.end();
                else this->listIt = 0;
            }
        }
        Iterator& operator=(const Iterator& iterator ){
            this->stack = iterator.stack;
            this->listIt = iterator.listIt;
            return *this;
        }
        
        T& operator*(){
            return *(this->listIt);
        }
        bool operator!=(const Iterator& iterator){
            return this->listIt != iterator.listIt;
        }
        // Prefix ++ overload 
        Iterator& operator++(){
            listIt++;
            return *this; 
        }
        // Postfix ++ overload 
        Iterator operator++(int){
            Iterator iterator = *this; 
            ++*this; 
            return iterator; 
        }
        void remove(void (*removeItem)(T)=0){
            listIt.remove(removeItem);
        }
    };
    //Iterator: END
};


#endif /* STACK_H */
