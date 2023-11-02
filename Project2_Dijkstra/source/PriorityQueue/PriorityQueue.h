#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

//#define DEBUG

//Wrapper class for our heap that contains many public functions
#include "../Heap/heap.h"
#include "../Dijkstra/Node.h"

class PriorityQueue
{
	public:
		Heap heap;
	public:
		PriorityQueue();
		PriorityQueue(TYPE heapType);
		~PriorityQueue();

		//Typical queue functions
		bool Insert(Node* n);
		bool Delete(Node* n);
		Node* Top();
		//Some debugging functions
		void PrintQueue();
		//Other needed functions
		bool IsEmpty();


};
#endif

