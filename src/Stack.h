#ifndef ASG3_STACK_H
#define ASG3_STACK_H

#include <iostream> // Including necessary library files.
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Stack {
	public:
	Stack(){
        _head = nullptr;
        _size = 0;
	}
	~Stack(){
	}
	bool isEmpty() const{
        return _size == 0;
	}
	int size() const{
        return _size;
	}
	//Push: Place item on top of the stack
	void push(const T& newItem){
        // Create new node temp and allocate memory
        struct ListNode* temp;
        temp = new ListNode;
        // Initialize data into temp data field
        temp->item = newItem;
        // Put top pointer reference into temp link
        temp->next = _head;
        // Make temp as top of Stack
        _head = temp;
        _size = _size+1;
	}
	//Top: Take a look at the topmost item without removing it
	void getTop(T& stackTop) const{

        // Check for stack underflow
        if (isEmpty())
        {
            throw string("Stack is empty on top");
        }
        else
        {
            stackTop = _head->item;
        }
	}
	//Pop: Remove item from the top of the stack
	void pop(){
        if (isEmpty()){
            throw string("Stack is empty on pop()");
        }
        else{
            ListNode* cur;
            cur = _head;
            _head = _head->next;
            delete cur;
            cur = nullptr;
            _size--;
        }
	}
	private:
	struct ListNode {
		T item;
		ListNode* next;
		};
	// Head pointer for the first item in the stack.
	ListNode* _head;
	int _size;
};

#endif //ASG3_STACK_H