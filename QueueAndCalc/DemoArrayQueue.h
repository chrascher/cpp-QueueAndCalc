
#pragma once

#include <iostream>
#include <cstdlib>

#include "QueueEmptyException.h"
#include "QueueOverFlowException.h"
#include "QueueInterface.h" 

using namespace std; 

#define DEF_MAX_SIZE = 100;

template<typename TN> 
class DemoArrayQueue : public QueueInterface<TN> {

private:
	// unser werte buffer im ringsystem
	TN  data[100];

	// Die position von der aus gelesen wird 
	// lesen
	int front; 

	// die position des nächsten einzufuegenden elements
	// schreibend: 
	int back;

	// int elementCount; 

public:
	DemoArrayQueue( ) {
		front = 0;
		back = 0;
	}

	~DemoArrayQueue(void) {
	}

	bool isEmpty() const {
		return (front == back) ? true : false;
	}

	int size() const {
		return size2(); 
	}

	int size2() const {
		
		int size = 0;

		if(back >= front ) {
			size =(back - front); // abs
		} else { 
			size = (100-front) + back ; // wenn back < front dann von front bis max plus 0 bis back == size 
		}

		return size; 
	}


	// enqueue new object 
	// Don't allow the queue to grow more than MAX_SIZE - 1
	void enqueue(TN element) {

		if ( size() == (100-1) ) { // todo maxsize
			throw 1; // TODO exeption
		}
		data[back] = element;

		// ++elementCount;  // manually use extra element number count 

		// MOD will wrapp around e.g. max = 1000 end = 1001 1001 % 1000 -->  1
		back = ++back % 100; // TODO impl max size getMaxSize();
		// or use manuellen überlauf if(back == 100) back = 0;
	}

	TN dequeue() {

		if (isEmpty())
			throw 1;

		TN ret = data[front];

		data[front] = 0; // we set empty values to 0 for now... 

		// --elementCount;  // manually use extra element number count 

		// MOD will wrapp around e.g. max = 1000 end = 1001 1001 % 1000 -->  1
		front = ++front % 100; // getMaxSize();

		return ret;
	}

	template <typename TNJ>
	friend ostream& operator<<(ostream& out, const DemoArrayQueue<TNJ> &x);

};

template <typename TN>
ostream& operator<<(ostream& out, const DemoArrayQueue<TN>& queue ) {

	out << "Queue Status count: [" << queue.size() << "] : front pos: [" <<
		queue.front << "] back pos: "<< queue.back << "] empty: [" << queue.isEmpty() 
		<< "] size: [" << queue.size() << "]" 
		<< endl;

	return out; 
}
