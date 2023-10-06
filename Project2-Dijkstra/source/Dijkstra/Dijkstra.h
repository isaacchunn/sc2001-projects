#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Node.h"
#include <iostream>
#include "../PriorityQueue/PriorityQueue.h"
#include "../PriorityQueue/PriorityQueueArray.h"
#include "../Misc/Timer.h"

//#define DEBUGPRINT

/// <summary>
/// Enum to determine between which type of priority queue to use
/// </summary>
enum QUEUE_TYPE
{
    HEAP,
    ARRAY,
    TOTAL_QUEUETYPE
};

class Dijkstra
{
public:
	//Simple wrapper that contains a static method
    static void FindShortestPath(Graph * g, Node * source, Node* end, QUEUE_TYPE type);    
    static void FindShortestPath(Graph* g, int sourceVertex, int endVertex, QUEUE_TYPE type);
    static void CalculateShortestPath(Graph* g, Node * source, QUEUE_TYPE type);
    static void CalculateShortestPath(Graph* g, int sourceVertex, QUEUE_TYPE type);

    //Helper function to print number of unvisited nodes
    static void PrintUnvisitedNodes();

private:
    //Vector that stores the predecessor "node" of the associated shortest path
	static vector<Node*> pi;
    //A vector that indicates if this node is already been accounted for
	static vector<int> S;
    //A vector that stores the distinct amount of shortest paths to each vertex
    
    //Debugging function
    static void Debug(Graph * g, int iteration);
    //Graph function to calculate shortest path
    static void CalculateShortestPathHeap(Graph* g, Node* source);
    static void CalculateShortestPathArray(Graph* g, Node* source);
    static void CalculateShortestPathHeap(Graph* g, int sourceVertex);
    static void CalculateShortestPathArray(Graph* g, int sourceVertex);

};
#endif

