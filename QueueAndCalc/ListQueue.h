
#pragma once 

#include <iostream>
#include <cstdlib>
#include <assert.h> 

#include "QueueEmptyException.h"
#include "QueueOverFlowException.h"
#include "QueueInterface.h" 

#define RECURSIVE 

template<typename TN> 
class Node 
{
public:
	TN data;
	Node* next;

	Node() {
		next = 0 ; // NULL;
	}

	Node(TN data, Node* next) {
		this->data = data;
		this->next = next; 
	}

	~Node() {
		// should we destroy next node here also ?? 
	}


};

template<typename TN> 
class ListQueue : public QueueInterface<TN> 
{
private:
	Node<TN>* front;
	Node<TN>* rear;
	int count;

public:
	ListQueue() {
		front = NULL;
		rear = NULL;
		count = 0;
	}

	// enqueues an element into the list, by appending it to the rear 
	void enqueue(TN element) throw(QueueOverFlowException) {

		// value will be stored here
		// we add elements to the rear of the linked list, so there is no next pointer here 
		Node<TN>* tmp = new Node<TN>(element, NULL ); // new element for new value to queue 

		if (isEmpty()) { // first element will all be the same front and rear 
			
			front = rear = tmp;

		} else { // Append to the list
			
			rear->next = tmp;
			rear = tmp;
		}
		count++;
	}

	// we will dequeue from the front/start of the list 
	TN dequeue() throw (QueueEmptyException) {

		if (isEmpty())
			throw QueueEmptyException();

		TN ret = front->data;
		Node<TN>* tmp = front;

		count--;

		if (isEmpty()) { // first element will all be the same front and rear 
			
			front = rear = NULL;

		} else {
			// build a BUG manually: front = NULL; 
			// Move the front pointer to next node
			assert(front != NULL); 

			front = front->next;
			// rear can stay where it is.. 
		}

		delete tmp;
		return ret;
	}

	TN getFront() {

		if (isEmpty())
			throw new QueueEmptyException();

		return front->data;
	}

	int size() const {
		return count;
	}

	bool isEmpty() const { 
		return (count == 0);
	}

	void dumpList(ostream &  os ) {

#ifdef RECURSIVE

		os << "START:: now dumping list elements to cout " << endl; 
		unsigned int tmpCount = 0; 
		printlistRecursive(front, os, tmpCount); 
		os << "END :: now dumping list elements to cout: nr: [" << tmpCount << "]" << endl; 
#else

		dumpListNonRecursive(os);
#endif

	}


private:

#ifdef RECURSIVE
	void printlistRecursive(Node<TN> * pNode, ostream &  os, unsigned & tmpCount ) {

		tmpCount++; 
		os << "deep first  Node Number: [" << tmpCount <<"] value: [" << pNode->data << "] Address next: " << pNode->next  << " my node: " << pNode << endl; 
	
		if(pNode->next != NULL ) {
			printlistRecursive( pNode->next, os, tmpCount ); 
		}
	}
#endif

#ifndef RECURSIVE
	void dumpListNonRecursive(ostream &  os ) {
		os << "START:: now dumping list elements to cout " << endl; 

		Node<TN> * pIP = this->front; // iterator pointer 

		unsigned int tmpCount = 0; 
		
		while(pIP!=NULL) {
			tmpCount++; 
			os << "Node Number: [" << tmpCount <<"] value: [" << pIP->data << "] Address next: " << pIP->next  << " my node: " << pIP << endl; 
			pIP = pIP->next; 
		}

		os << "END :: now dumping list elements to cout: nr: [" << tmpCount << "]" << endl; 
	}
#endif 


	template <typename TNJ>
	friend ostream& operator<< ( ostream& out, const ListQueue<TNJ> & queue ); 

};


template <typename TNJ>
ostream& operator<<(ostream& out, const ListQueue<TNJ>& queue ) {

	out << "Queue Status count: [" << queue.size() << "] : front pos: [" <<
		queue.front << "] back pos: "<< queue.rear << "] empty: [" << queue.isEmpty() 
		<< "] size: [" << queue.size() << "]" 
		<< endl;

	return out; 
}
