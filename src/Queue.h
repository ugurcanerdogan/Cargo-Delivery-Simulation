#ifndef ASG3_QUEUE_H
#define ASG3_QUEUE_H

#include <iostream> // Including necessary library files.
#include <string>
using namespace std;

template<typename T>
class Queue {
	public:
	Queue(){
        _lastNode = nullptr;
        _size = 0;
	}
	~Queue(){
	}
	bool isEmpty() const{
        return _size == 0;
	}
	int size() const{
        return _size;
	}
	//Enqueue: Items are added to the back of the queue
	void enqueue(const T& newItem){
        if (_size!=0){
            struct QueueNode* temp;
            temp = new QueueNode;
            temp->next = _lastNode->next;
            temp->item = newItem;
            _lastNode->next = temp;
            _lastNode = temp;
            _size++;
        }
        else{
            struct QueueNode* temp;
            temp = new QueueNode;
            temp->item = newItem;
            temp->next = temp;
            _lastNode = temp;
            _size++;
        }
	}
	//Dequeue: Items are removed from the front of the queue
	void dequeue(){
        if (_size > 1){
            struct QueueNode* temp;
            temp = _lastNode->next;
            _lastNode->next = temp->next;
            delete temp;
            _size--;
        }
        else if (_size == 1){
            struct QueueNode* temp;
            temp = _lastNode->next;
            _lastNode = nullptr;
            delete temp;
            _size--;
        }
	}
	//Get Front: Take a look at the first item
	void getFront(T& queueTop) const{
        struct QueueNode* start;
        if(isEmpty())
        {
            throw string("Queue is empty on front");
        }
        else
        {
            start = _lastNode->next;
            queueTop = start->item;
        }
	}
	private:
	struct QueueNode {
		T item;
		QueueNode *next;
		};

	int _size;
	/* to avoid the traversal to the last node, 
	 an additional pointer to the last node is defined*/
	QueueNode *_lastNode;
};

#endif //ASG3_QUEUE_H