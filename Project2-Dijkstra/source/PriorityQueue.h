#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

//Wrapper class for our heap that contains many public functions
#include "Heap/heap.h"
#include "Dijkstra/Node.h"

class PriorityQueue
{
	public:
		Heap<Node*> heap;
	public:
		PriorityQueue();
		PriorityQueue(HEAP_TYPE heapType);
		~PriorityQueue();

		//Typical queue functions
		bool Insert(Node* n);
		bool Delete(Node* n);
		Node* Top();

		//Some debugging functions
		void PrintQueue();

		//Other needed functions
		bool isEmpty();


};
#endif

