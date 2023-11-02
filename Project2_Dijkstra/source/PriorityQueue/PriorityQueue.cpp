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

#ifdef DEBUG
    cout << "Inserting vertex " << n->GetName() << " into the queue." << endl;
#endif

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
//	//If the heap is empty
//	if (IsEmpty())
//	{
//#ifdef DEBUG
//		cout << "Empty heap" << endl;
//#endif
//		return NULL;
//	}
	
	//Else we can get the heap's first index and call delete
	Node* n = heap.GetElements()[0];
	heap.Delete();

	return n;
}

/// <summary>
/// Function to print the queue=
/// </summary>
void PriorityQueue::PrintQueue()
{
	heap.PrintHeap();
	cout << endl;
	heap.PrintElements();
}

/// <summary>
/// Checks if the queue is empty
/// </summary>
/// <returns></returns>
bool PriorityQueue::IsEmpty()
{
	//return heap size is 0
	return heap.GetElements().empty();
}
