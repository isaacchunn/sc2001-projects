#include "PriorityQueueArray.h"

PriorityQueueArray::PriorityQueueArray()
	: type(TYPE::MINIMISING)
{
}

PriorityQueueArray::PriorityQueueArray(TYPE type)
	: type(type)
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

	//Prevent duplicates.
	if (std::find(elements.begin(), elements.end(), n) != elements.end())
		return false;
	
	elements.push_back(n);
	return true;
}

/// <summary>
/// Gets the smallest node in the array in O(n) time
/// </summary>
/// <returns>smallest node, null if queue empty</returns>
Node* PriorityQueueArray::GetSmallest()
{
	//if the queue is empty, return null
	if (IsEmpty())
		return NULL;

	//Searches through the list and gets the smallest distance node
	//Only takes the "first smallest even if there may be multiple processes of the same weight."
	int min = INT_MAX;
	int index = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i]->GetDistanceFromSource() < min)
		{
			//Set min to be this distance and update indices
			min = elements[i]->GetDistanceFromSource();
			index = i;
		}
	}
	//Once we have index and min
	Node* n = elements[index];
	//Delete node at this point
	elements.erase(elements.begin() + index);

	return n;
}

/// <summary>
/// Checks if the queue is empty
/// </summary>
/// <returns>true if empty, false if not.</returns>
bool PriorityQueueArray::IsEmpty()
{
	return elements.size() == 0;
}

/// <summary>
/// Prints out the array in simple fashion, does nothing than to check if something is inside.
/// </summary>
void PriorityQueueArray::PrintQueue()
{
	for (auto n : elements)
		cout << n << " ";
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

	int i = 0;
	for (; i < elements.size(); i++)
	{
		if (elements[i] == n)
			break;
	}
	if (i == elements.size())
		return false;

	//Else we found it delete it at this index and return true
	elements.erase(elements.begin() + i);
	return true;

}


