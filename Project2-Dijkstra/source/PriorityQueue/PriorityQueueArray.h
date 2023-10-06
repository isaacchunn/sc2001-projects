#ifndef PRIORITY_QUEUE_ARRAY_H
#define PRIORITY_QUEUE_ARRAY_H

#include "../Dijkstra/Node.h"
#include "../Heap/heap.h"

#include <vector>
#include <set>

/// <summary>
/// Mimics the behaviour of a priority queue using an array (* TYPE DOES NOT DO ANYTHING FOR NOW, IT IS ONLY MINIMIZING REGARDLESS OF TYPE!)
/// </summary>
class PriorityQueueArray
{
	private:
		std::vector<Node*> elements;
		TYPE type;
	public:
		PriorityQueueArray();
		PriorityQueueArray(TYPE type);

		//Typical queue functions
		bool Insert(Node* n);
		bool Delete(Node* n);
		Node* GetSmallest();
		bool IsEmpty();

		//Some debugging functions
		void PrintQueue();
};
#endif

