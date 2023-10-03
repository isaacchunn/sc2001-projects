//
//  main.cpp
//  HeapSort
//
//  Created by Isaac on 10/9/23.
//

#include <stdio.h>
#include <iostream>
#include "heap.h"

using namespace std;



int main(int argc, const char * argv[]) {
    //Create a new heap
    Heap<int> heap;
    //Set the type of heap
    heap.SetHeapType(MAXIMISING);
    
    //Initialize the heap with some initial elements
    //vector<int> elements = {14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    vector<int> elements = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    heap.SetElements(elements);
    
    //Then we want to construct our heap
    heap.PrintElements();
    //Print initial arrangement before it is "heaped"
    heap.PrintHeap();
    //Construct heap from our initial elements
    heap.ConstructHeap();
    //Print the heap
    heap.PrintHeap();
    //Print the elements of the array
    heap.PrintElements();

    //Answer vector
    vector<int> result;
    //Sort the heap and store into result
    heap.HeapSort(result);
    //Print the resulting elements
    //heap.PrintElements();
    //Print answer array
    cout << "Sorted Array from Heap: [ ";
    for (auto i : result)
    {
        cout << i << " ";
    }
    cout << "]\n";
    
    return 0;
}
