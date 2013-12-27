#pragma once 

#include <iostream>
#include <cstdlib>
#include <assert.h> 

#include "QueueEmptyException.h"
#include "QueueOverFlowException.h"

using namespace std; 

template<typename TN> 
class QueueInterface
{
public:
	// ~ListQueue(); 

	// enqueues an element into the list, by appending it to the rear 
	virtual void enqueue(TN element) throw(QueueOverFlowException) = 0; 

	// we will dequeue from the front/start of the list 
	virtual TN dequeue() throw (QueueEmptyException) = 0;

	virtual TN getFront() = 0; 

	virtual int size() const = 0 ;

	virtual bool isEmpty() const = 0 ;

	virtual void dumpList(ostream &  os ) = 0;

	template <typename TNJ>
	friend ostream& operator<<(ostream& out, const QueueInterface<TNJ> &x);

};

template <typename TN>
ostream& operator<<(ostream& out, const QueueInterface<TN>& queue ) {

	out << "Queue Status count: [" << queue.size() << "] : front pos: [" << "] size: [" << queue.size() << "]" 
		<< endl;

	return out; 
}



