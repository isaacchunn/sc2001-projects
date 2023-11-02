#include "PriorityQueueArray.h"

PriorityQueueArray::PriorityQueueArray()
	: type(TYPE::MINIMISING), size(0)
{
}

PriorityQueueArray::PriorityQueueArray(TYPE type)
	: type(type) ,size(0)
{
}

/// <summary>
/// Inserts a node into the back of a vector.
/// </summary>
/// <param name="n">node</param>
bool PriorityQueueArray::Insert(Node* n)
{
	if (n == NULL)
		return false;
	elements.push_back(n);
	size++;
	return true;
}

/// <summary>
/// Gets the smallest node in the array in O(n) time
/// </summary>
/// <returns>smallest node, null if queue empty</returns>
Node* PriorityQueueArray::GetSmallest()
{
	//Searches through the list and gets the smallest distance node
	//Only takes the "first smallest even if there may be multiple processes of the same weight."
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		int dist = elements[i]->GetDistanceFromSource();
		if (dist < min)
		{
			//Set min to be this distance and update indices
			min = dist;
			index = i;
		}
	}
	//Once we have index and min
	Node* n = elements[index];
	elements[index] = elements[size - 1];
	elements.pop_back();
	size--;
	return n;
}

/// <summary>
/// Checks if the queue is empty
/// </summary>
/// <returns>true if empty, false if not.</returns>
bool PriorityQueueArray::IsEmpty()
{
	return size == 0;
}

/// <summary>
/// Prints out the array in simple fashion, does nothing than to check if something is inside.
/// </summary>
void PriorityQueueArray::PrintQueue()
{
	for (auto n : elements)
		cout << n << " ";
	cout << endl;
}

/// <summary>
/// Loops through the queue to find if said node exists
/// </summary>
/// <param name="n"></param>
/// <returns></returns>
bool PriorityQueueArray::Delete(Node* n)
{
	if (n == NULL)
		return false;

	for (int i = 0; i < size; i++)
	{
		if (elements[i] == n)
		{
			//Update elements[i] to be last element, then pop back
			elements[i] = elements[size-1];
			elements.pop_back();
			size--;
			break;
		}
	}
	return true;
}

bool PriorityQueueArray::Delete(int vertex)
{
	for (int i = 0; i < size; i++)
	{
		if (elements[i]->GetVertex() == vertex)
		{
			//Update elements[i] to be last element, then pop back
			elements[i] = elements[size-1];
			elements.pop_back();
			size--;
			break;
		}
	}
	return true;
}


