//Linked List implementation

#ifndef ASG3_LINKEDLIST_H
#define ASG3_LINKEDLIST_H

#include <iostream> // Including necessary library files.
#include <string>
using namespace std;

template<class T>
class LinkedList {
public:
    LinkedList(){
        _lastNode = NULL;
        _size = 0;
    }
    ~LinkedList(){

    }
    // Function for checking the whether list is empty or not
    bool isEmpty() const{
        return _size == 0;
    }
    // Function to return the size of the linked list
    int size() const{
        return _size;
    }
    // Insert package method
    void insert(const T& newItem){
        if (_size!=0){      // Code block for inserting to non-empty list
            struct LinkedListNode* temp;
            temp = new LinkedListNode;
            temp->next = _lastNode->next;
            temp->item = newItem;
            _lastNode->next = temp;
            temp->prev = _lastNode;
            _lastNode = temp;
            _size++;
        }
        else{               // Code block for inserting to empty list
            struct LinkedListNode* temp;
            temp = new LinkedListNode;
            temp->item = newItem;
            temp->next = NULL;
            _lastNode = temp;
            _firstNode = temp;
            _size++;
        }
    }
    // Function for returning first package of the list
    T& getFirst(){
        struct LinkedListNode* startPackage;
        if (_lastNode != NULL && _size > 1){
            startPackage = _firstNode->next;
            if (_size == 2){
                _firstNode->next = NULL;
                _size--;
                return startPackage->item;
            }
            else if (_size > 2){
                _firstNode->next = startPackage->next;
                startPackage->next->prev=_firstNode;
                _size--;
                return startPackage->item;
            }
        }
    }
    // Function for emptying the list
    void freeList(){
        _firstNode = NULL;
        _size = 0;
    }
    // Function for returning the package at the given index of the list
    T& getItem(const int index){
        struct LinkedListNode* startPackage,temp;
        if (_lastNode != NULL && _size > 1){    // Function works only if it is not empty or has 1 package at least
            startPackage = _firstNode->next;
            int recIndex = 0;
            while (recIndex < index){           // Iterating to given index
                startPackage = startPackage->next;
                recIndex++;
            }
            if (startPackage != _lastNode){     // Unlink the package
                startPackage->prev->next = startPackage->next;
                startPackage->next->prev = startPackage->prev;
            }
            else{                               // Unlink the last package
                startPackage->prev->next = NULL;
                _lastNode = startPackage->prev;
            }
            _size--;
            return startPackage->item;
        }
    }
    // Function for returning first element(truck) of list
    T& getTruck(){
        return _firstNode->item;
    }

private:
    struct LinkedListNode {
        T item;
        LinkedListNode *next;
        LinkedListNode *prev;
    };
    int _size;
    LinkedListNode *_lastNode;
    LinkedListNode *_firstNode;
};

#endif //ASG3_LINKEDLIST_H
