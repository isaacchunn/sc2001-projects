#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
	heap.SetHeapType(MAXIMISING);
}

PriorityQueue::PriorityQueue(TYPE heapType)
{
	//Set our heap type
	heap.SetHeapType(heapType);
}

PriorityQueue::~PriorityQueue()
{
}

/// <summary>
/// Inserts a node into the heap
/// </summary>
/// <param name="n"></param>
bool PriorityQueue::Insert(Node* n)
{
	if (n == NULL)
		return false;
    cout << "Inserting vertex " << n->GetName() << endl;
	heap.Insert(n);
	return true;
}

/// <summary>
/// Removes a specific node from the heap
/// </summary>
/// <param name="n"></param>
bool PriorityQueue::Delete(Node* n)
{
	if (n == NULL)
		return false;
	//We have to reconstruct a heap each time we do this as it does not guarantee the completeness of the tree
	heap.Delete(n);
	return true;
}

/// <summary>
/// Gets the top node of the priority queue and removes that element from the queue
/// </summary>
/// <returns></returns>
Node* PriorityQueue::Top()
{
	//If the heap is empty
	if (isEmpty())
	{
		cout << "Empty heap" << endl;
		return NULL;
	}
	

	//Else we can get the heap's first index and call delete
	Node* n = heap.GetElements()[0];
	heap.Delete();

	return n;
}

void PriorityQueue::PrintQueue()
{
	heap.PrintHeap();
	cout << endl;
	heap.PrintElements();
}

bool PriorityQueue::isEmpty()
{
	//return heap size is 0
	return heap.GetElements().size() == 0;
}
