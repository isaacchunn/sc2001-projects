#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "Node.h"
#include "ListNode.h"

using namespace std;

struct Graph
{
    //Number of vertices
	int V;
    //Int number of edges
	int E;
    
    //Easy implementation to get nodes from indexes and vertexes
    unordered_map<int,Node*> nodes;
	//Adjacency Matrix Implementation
	vector<vector<int>> adjMatrix;
	//Adjacency List Implementation
	vector<ListNode*> adjList;
};

#endif

