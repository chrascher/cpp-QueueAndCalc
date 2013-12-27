#include <iostream>
#include <cstdlib>

#include "QueueEmptyException.h"
#include "QueueOverFlowException.h"


using namespace std;

const int DEF_MAX_SIZE = 100;

// QUEUE FRONT == where the elements will be taken out again 
// QUEUE back  == wehere the elements are filled in again

// QUEUE  END ->  EL, EL , EL <- FRONT

template<typename T, int sizeT > // = DEF_MAX_SIZE 
class ArrayQueue
{
private:
	T  data[sizeT];
	int frontE;
	int back;

	int getMaxSizeIntern(T(&)[sizeT]) {
		return sizeT;
	}

public:

	ArrayQueue() {
		frontE = 0;
		back = 0;
	}

	int getMaxSize() {
		return	getMaxSizeIntern(data);
	}

	void enqueue(T element) {
		// Don't allow the queue to grow more
		// than MAX_SIZE - 1
		if (size() == getMaxSize() - 1)
			throw new QueueOverFlowException();

		data[back] = element;

		// MOD will wrapp around e.g. max = 1000 end = 1001 1001 % 1000 -->  1
		back = ++back % getMaxSize();
	}

	T  dequeue()
	{
		if (isEmpty())
			throw new QueueEmptyException();

		T ret = data[frontE];

		// MOD will wrapp around e.g. max = 1000 end = 1001 1001 % 1000 -->  1
		frontE = ++frontE % getMaxSize();

		return ret;
	}

	int front()
	{
		if (isEmpty())
			throw new QueueEmptyException();

		return data[frontE];
	}

	int size()
	{
		return abs(back - frontE);
	}

	bool isEmpty()
	{
		return (frontE == back) ? true : false;
	}
};
