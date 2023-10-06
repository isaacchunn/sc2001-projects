#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <string>
#include "../Dijkstra/Node.h"

using namespace std; 

enum TYPE
{
    MAXIMISING,
    MINIMISING,
    TOTAL_MODE
};

/// <summary>
/// Non templated heap update 10/6/2023 as templated heap was causing different results on compilation
/// </summary>
class Heap
{
    private:
        //Have the heap store a vector of elements
        std::vector<Node*> elements;
        //Store the type of heap
        TYPE heapType;
        //Store last pointer to present the "sorted result"
        int last_ptr;
        //Store the name of this heap for identification
        string heapName;
        //Misc
        static int keyComparisons;

    public:
        //Constructors, Destructors
        Heap();
        Heap(TYPE type, string name);
        ~Heap();
        
        //Accessors and Mutators
        void SetHeapType(TYPE type);
        void SetName(string name);
        TYPE GetHeapType();
        string GetName();
        vector<Node*> GetElements();
        
        //Print the heap
        void PrintElements();
        void PrintHeap();
        void PrintHeapArray();

        //Typical methods of heap
        bool ConstructHeap();
        bool SetElements(vector<Node*>& other);
        bool Insert(Node* element);
        void Delete();
        void Delete(Node* element);
        //*
        bool HeapSort(vector<Node*>& result);

    private:
        //Private methods that are exclusive to the heap
        void Heapify(int H);
        void FixHeap(int H, Node* k, int maxIndex);
        bool isLeaf(int H);
};
#endif
