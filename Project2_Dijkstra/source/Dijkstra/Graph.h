#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <time.h>
#include "ListNode.h"
#include "../Misc/DataHandler.h"

using namespace std;

enum GRAPH_TYPE
{
	DIRECTIONAL,
	BIDIRECTIONAL,
	TOTAL_TYPE
};

class Graph
{
	public:
		Graph();
		Graph(GRAPH_TYPE type);
		~Graph();

		//Public for ease of accessibility as I want functions so I dont use struct.
		int V;
		int E;
		GRAPH_TYPE type;

		vector<vector<int>> adjMatrix;
		vector<ListNode*> adjList;
		vector<Node*> nodes;
		
		//Functions
		void SetNoOfVertices(int vertices);
		void Clear();
		void UpdateAdjacencyList();
		//CSV
		bool LoadGraph(std::string file);
		bool ExportGraph(std::string file);
		//Node addition and deletion later on
		//Printing
		void PrintAdjMatrix();
		void PrintAdjList();
		//Random function
		void GenerateRandomGraph(int numberOfNodes, int density);
		
};

#endif

