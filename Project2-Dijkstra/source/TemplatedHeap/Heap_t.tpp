//#include "heap.h"
#include <string>
#include <iostream>

//#define DEBUG

using namespace std;

template<class T>
Heap<T>::Heap()
	: heapType(MAXIMISING),
	last_ptr(0),
	heapName("Default")
{

}

template<class T>
Heap<T>::Heap(TYPE type, string name)
	: heapType(type),
	last_ptr(0),
	heapName(name)
{
}

template<class T>
Heap<T>::~Heap()
{

}

template<class T>
void Heap<T>::SetHeapType(TYPE type)
{
	this->heapType = type;
}

template<class T>
TYPE Heap<T>::GetHeapType()
{
	return this->heapType;
}

template<class T>
string Heap<T>::GetName()
{
	return this->heapName;
}

template<class T>
vector<T> Heap<T>::GetElements()
{
	return this->elements;
}

template<class T>
void Heap<T>::SetName(string name)
{
	this->heapName = name;
}

/// <summary>
/// Prints the elements in the heap
/// </summary>
template<class T>
void Heap<T>::PrintElements()
{
	if (elements.size() == 0)
	{
		cout << "There are no elements in this heap!" << endl;
		return;
	}
	//Else just print out normally
	cout << "Heap Elements: [ ";
	for (int i = 0; i < elements.size(); i++)
	{
		cout << elements[i] << " ";
	}
	cout << "]" << endl;
}

/// <summary>
/// https://stackoverflow.com/questions/36385868/java-how-to-print-heap-stored-as-array-level-by-level
/// </summary>
template<class T>
void Heap<T>::PrintHeap()
{
	int max = 0;
	for (int i = 0; i < elements.size(); i++) {
		for (int j = 0; j < pow(2, i) && j + pow(2, i) <= elements.size(); j++) {

			if (j > max) {
				max = j;
			}
		}
	}
	for (int i = 0; i < elements.size(); i++) {
		for (int j = 0; j < pow(2, i) && j + pow(2, i) <= elements.size(); j++) {

			for (int k = 0; (k < max / ((int)pow(2, i))); k++) {
				cout << " ";
			}
			//Do error handling of printing as we go
			cout << elements[j + (int)pow(2, i) - 1];
			cout << " ";
		}
		//prevent overprinting by using height as print lines
		if (i < log2(elements.size()) - 1)
			cout << endl;
	}
	cout << endl;
}

template<class T>
void Heap<T>::PrintHeapArray()
{
	for (int i = 0; i < elements.size(); i++)
	{
		cout << elements[i] << " ";
	}
	cout << endl;
}

/// <summary>
/// Constructs the heap based on the elements in the heap
/// </summary>
/// <returns>True if heap was constrtucted, false if elements in heap is 0</returns>
template <class T>
bool Heap<T>::ConstructHeap()
{
	//Check if the size of vector isnt 0, or has already constructed
	if (elements.size() == 0)
	{
	#ifdef DEBUG
		std::cout << "===Construct Heap===\n There are no elements to construct a heap!" << std::endl;
	#endif
		return false;
	}
	//Reset last_ptr to elements.size
	last_ptr = (int)elements.size() - 1;
	//Reset key comparisons
	keyComparisons = 0;
	//Else just call heapify
	Heapify(0);

	//Print out the key comparisons
	//std::cout << "Key Comparisons: " << keyComparisons << endl;
	return true;
}

/// <summary>
/// Sets the elements of our current heap based on another vector
/// </summary>
/// <param name="other">other vector</param>
/// <returns>True by default.</returns>
template <class T>
bool Heap<T>::SetElements(vector<T>& other)
{
	//Clear the current vector first
	elements.clear();
	elements = other;
	//Store the last ptr of the heap
	int size = elements.size();
	last_ptr = size == 0 ? 0 : size - 1;
	return true;
}

/// <summary>
/// Inserts an element into the heap
/// </summary>
/// <param name="element">new element</param>
/// <returns>True by default.</returns>
template <class T>
bool Heap<T>::Insert(T element)
{
    if(std::find(elements.begin(), elements.end(), element) != elements.end())
        return false;
        
	//Insert at the back and then reconstruct heap
	this->elements.push_back(element);
	//Reconstruct our heap
	ConstructHeap();
	return true;
}

/// <summary>
/// Deletes the max node of an already constructed heap and reconstructs the heap by FixHeap()
/// </summary>
template <class T>
void Heap<T>::Delete()
{
	//Return if nothing to Delete
	if (this->elements.size() == 0)
	{
	#ifdef DEBUG
		std::cout << "===Delete===\n There are no elements to delete!" << std::endl;
	#endif
		return;
	}

	//Store the last element of heap into temp variable and decrement last ptr
	T k = elements[last_ptr--];
	

	//Then fix heap based on first index and k up to the last ptr index
	FixHeap(0, k, last_ptr);

	//Then remove last index variable in heap
	elements.pop_back();
}

/// <summary>
/// Deletes an element from the heap, usually used with pointers and not int, if its not a reference type then it deletes the first found instance.
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="element">element to delete</param>
template<class T>
void Heap<T>::Delete(T element)
{
	//Return if nothing to Delete
	if (this->elements.size() == 0)
	{	
	#ifdef DEBUG
		std::cout << "===Delete===\n There are no elements to delete!" << std::endl;
	#endif
		return;
	}

	//Update last_ptr only if element deleting is < last_ptr
	int i;
	for (i = 0; i < elements.size(); i++)
	{
		if (elements[i] == element)
		{
			break;
		}
	}
	//Then just erase at that element
	elements.erase(elements.begin() + i);
	//and reconstruct the entire heap
	ConstructHeap();
}


/// <summary>
/// Uses the heap to sort a list of numbers
/// </summary>
/// <param name="result">result vector</param>
/// <returns>True if sorting was done, false if there are no elements to sort</returns>
template <class T>
bool Heap<T>::HeapSort(vector<T>& result)
{
	//This assumes that the array has already been heapified, and the sorting is just deletions and fixing the heap
	//Check if current elements is empty
	int size = (int)this->elements.size();
	if (size == 0)
	{
	#ifdef DEBUG
		std::cout << "===Heap Sort===\n There are no elements to sort!" << std::endl;
	#endif
		return false;
	}
	std::cout << "===Heap Sort===" << std::endl;
	PrintElements();
	std::cout << "===After Heap Sort===" << std::endl;
	//Else populate result based on our heap sort
	result.clear();
	//Resize the result vector into n elements size
	result.resize(size);
	//We already have an array of n elements
	for (int i = last_ptr; i >= 0; i--)
	{
		//The first element of the heap is the largest
		T currMax = elements[0];
		//Call the delete function
		Delete();
		//Then assign this curr max to the end of our array (should return something here later on)
		//elements[i] = currMax;
		result[i] = currMax;
	}
	return true;
}

/// <summary>
/// Recursive function that heapifys the heap to ensure partial order of heap is maintained
/// </summary>
/// <param name="H">index of root (usually 0)</param>
template <class T>
void Heap<T>::Heapify(int H)
{
	//This is 0 indexed
	//Check if this is leaf
	if (!isLeaf(H)) //
	{
		//Heapify both left and right subtrees
		Heapify((H * 2) + 1);
		Heapify((H * 2) + 2);
		//Then set k as the element at this index
		//PrintHeap();
		T k = elements[H];
		FixHeap(H, k, last_ptr);
	}
}

/// <summary>
/// Fixes the heap by comparing root and descendants
/// </summary>
/// <param name="H">index of root</param>
/// <param name="k">value to compare</param>
template <class T>
void Heap<T>::FixHeap(int H, T k, int maxIndex)
{
	//Error handling for when H is out of range
	if (H < 0 || H > maxIndex)
		return;

	//Using 0 indexed list
	//Check if parent head is a leaf node
	if (isLeaf(H))
	{
		//Insert k at index H
		elements[H] = k;
	}
	else
	{
		//Accessing of elements is 0 index
		int left = (H * 2) + 1;
		int right = (H * 2) + 2;

		//Index of the larger sub heap
		int largerSubHeap = 0;
		//Error handle the right as current node might not have a right child
		//Check if the left and right falls beneath maxIndex;
		if (left == maxIndex)
		{
			//If left is equals to maxIndex, means right is already out of the picture, so left subheap is automatically bigger, and no need to compare with the right
			//In tutorial, no key comparison was added here.
			largerSubHeap = left;
		}
		else if (right <= maxIndex) //right must be less than or equals to max index
		{
			//Then there are two children, and we must compare them both.
			if (this->heapType == MAXIMISING)
				largerSubHeap = elements[left] > elements[right] ? left : right;
			else
				largerSubHeap = elements[left] > elements[right] ? right : left;

			//Increment the keycomparisons for comparing a child
			keyComparisons++;
		}
		//Check k higher than larger element
		if (k >= elements[largerSubHeap] && this->heapType == MAXIMISING) // another comparison so 2 comparisons per fix heap
		{
			//Safely insert as k is larger than both left and rightchild of current root
			elements[H] = k;
		}
		else if (k <= elements[largerSubHeap] && this->heapType == MINIMISING)
		{
			elements[H] = k;
		}
		else
		{
			//We must insert root of the larger sub heap in root of H
			elements[H] = elements[largerSubHeap];
			FixHeap(largerSubHeap, k, maxIndex);
		}
	}
}

/// <summary>
/// Returns true if the nodes is a leaf node
/// </summary>
/// <param name="H">0-indexed index of the node</param>
/// <returns>None</returns>
template <class T>
bool Heap<T>::isLeaf(int H)
{
	return (H * 2) + 1 > last_ptr;
}

