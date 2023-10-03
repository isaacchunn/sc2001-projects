#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include "Node.h"
#include <queue>
#include <iostream>

class Dijkstra
{
public:
	//Simple wrapper that contains a static method
	static void CalculateShortestPath(Graph * g, Node * source);
    static void FindShortestPath(Graph * g, Node * source, Node* end);

private:
    //Vector that stores the distance of each vertex to source node
	//static vector<int> d;
    //Vector that stores the predecessor "node" of the associated shortest path
	static vector<Node*> pi;
    //A vector that indicates if this node is already been accounted for
	static vector<int> S;
    //A vector that stores the distinct amount of shortest paths to each vertex
    static vector<int> pathCount;
    
    //Debugging function
    static void Debug(Graph * g, int iteration);
};
#endif

