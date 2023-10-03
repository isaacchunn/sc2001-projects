#include <stdio.h>
#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "ListNode.h"
#include "Dijkstra.h"

using namespace std;

void printGraphMatrix(Graph* g);
void printGraphList(Graph* g);


int main()
{
	//Create a graph
	Graph* graph = new Graph();
	//Initialzie graph
	graph->V = 0;
	graph->V = 0;

	//Assume each vertex starts from 0 (now hard coded to suit lecture's graph)
	int vertexes = 5;
	cout << "Input number of vertices: ";
	//Get input
	//cin >> vertexes;
	cout << endl;

	//Update size
	graph->V = vertexes;
	//Resize our graph vectors
	//Initialize our adj list first
	//graph->adjList.resize(graph->V);
	//for (int i = 0; i < graph->V; i++)
	//{
	//	//No head is initialized as we are using indexing to determine adjacency
	//	graph->adjList[i] = ll;
	//}

	graph->adjMatrix.resize(graph->V);
	//Then do for our adj matrix
	for (int i = 0; i < graph->V; i++)
	{
		graph->adjMatrix[i].resize(graph->V);
	}

	//Code it for lecture graph
	//graph->adjMatrix[0] = {0,10,5,INT_MAX,INT_MAX};
	//graph->adjMatrix[1] = {INT_MAX,0,2,1,INT_MAX};
	//graph->adjMatrix[2] = {INT_MAX,3,0,9,2};
	//graph->adjMatrix[3] = {INT_MAX,INT_MAX,INT_MAX,0,4};
	//graph->adjMatrix[4] = {7,INT_MAX,INT_MAX,6,0};

	//Tutorial graph for it's adjacency matrix
	graph->adjMatrix[0] = { 0,4,2,6,8 };
	graph->adjMatrix[1] = { INT_MAX,0,INT_MAX,4,3 };
	graph->adjMatrix[2] = { INT_MAX,INT_MAX,0,1,INT_MAX };
	graph->adjMatrix[3] = { INT_MAX,1,INT_MAX,0,3 };
	graph->adjMatrix[4] = { INT_MAX,INT_MAX,INT_MAX,INT_MAX,0 };

	//Make many nodes for now to test (not the best implementation, just testing it out)
	Node* s = new Node(0, 0, "s");
	Node* u = new Node(1, 0, "u");
	Node* x = new Node(2, 0, "x");
	Node* v = new Node(3, 0, "v");
	Node* y = new Node(4, 0, "y");

	//Add into our graph the above nodes, storing the vertex as keys (assumes no vertex are repeated)
	graph->nodes[s->GetVertex()] = s;
	graph->nodes[u->GetVertex()] = u;
	graph->nodes[x->GetVertex()] = x;
	graph->nodes[v->GetVertex()] = v;
	graph->nodes[y->GetVertex()] = y;

	//Get input and update adj matrix
	printGraphMatrix(graph);

	//Then try print the shortest path from the soruce node to end point
	Dijkstra::FindShortestPath(graph, s, y);

	return 0;
}

/// @brief Prints the adjacency matrix of a graph
/// @param g graph
void printGraphMatrix(Graph* g)
{
	int i, j;

	//Print the rows first.
	printf("Adjacency Matrix\n");
	//Print divider.
	for (i = 0; i < g->V; i++)
	{
		printf("----------");
	}
	printf("\n|  \t|");
	for (i = 0; i < g->V; i++)
	{
		printf("\t%d", i + 1);
	}
	printf("  |\n");
	//Print divider.
	for (i = 0; i < g->V; i++)
	{
		printf("----------");
	}
	printf("\n");
	for (i = 0; i < g->V; i++) {
		//Print divider.
		printf("| %d\t|", i + 1);
		for (j = 0; j < g->V; j++)
			printf("\t%d", g->adjMatrix[i][j]);
		printf("  |\n");
	}
	//Print divider.
	for (i = 0; i < g->V; i++)
	{
		printf("----------");
	}
	printf("\n");
}

/// @brief Prints the adjacency list of a graph
/// @param g graph
void printGraphList(Graph* g) {
	/*
	//Variable declaration
	int i;
	ListNode* temp;
	//Sanity check

	//Print at each index.
	for (i = 0; i < g->V; i++)
	{
		printf("%d:\t", i + 1);
		temp = g->adjList[i];
		while (temp != NULL) {
			printf("%d -> ", temp->cost);
			temp = temp->next;
		}
		printf("\n");
	}
	*/
}


