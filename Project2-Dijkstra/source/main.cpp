#include <stdio.h>
#include <iostream>
#include "Dijkstra/Graph.h"
#include "Dijkstra/Node.h"
#include "Dijkstra/ListNode.h"
#include "Dijkstra/Dijkstra.h"

using namespace std;

void printGraphMatrix(Graph* g);
void printGraphList(Graph* g);

#define M INT_MAX

int main()
{
	//Create a graph
	Graph* graph = new Graph();

	int choice;
	do
	{
		//Print the UI
		cout << "---Dijkstra Interface---" << endl;
		cout << "1) Use Tutorial Graph" << endl;
		cout << "2) dd" << endl;
		cout << "3) Load Graph" << endl;
		cout << "4) Export Graph" << endl;
		cout << "5) Quit" << endl;
		cout << "Input choice: ";
		cin >> choice;

		switch (choice)
		{
			//Tutorial Graph
		case 1:
		{
			//Set the number of vertices to be 5
			graph->SetNoOfVertices(5);
			//Tutorial graph for it's adjacency matrix
			graph->adjMatrix = { { 0,4,2,6,8 },
								 { M,0,M,4,3 },
								 { M,M,0,1,M },
								 { M,1,M,0,3 },
								 { M,M,M,M,0 } };

			//Make many nodes for now to test (not the best implementation, just testing it out)
			Node* s = new Node(0, 0, "1");
			Node* u = new Node(1, 0, "2");
			Node* x = new Node(2, 0, "3");
			Node* v = new Node(3, 0, "4");
			Node* y = new Node(4, 0, "5");

			//Add into our graph the above nodes, storing the vertex as keys (assumes no vertex are repeated)
			graph->nodes[s->GetVertex()] = s;
			graph->nodes[u->GetVertex()] = u;
			graph->nodes[x->GetVertex()] = x;
			graph->nodes[v->GetVertex()] = v;
			graph->nodes[y->GetVertex()] = y;

			//Update adjacency list
			graph->UpdateAdjacencyList();
			//Get input and update adj matrix
			printGraphMatrix(graph);
			printGraphList(graph);

			//Then try print the shortest path from the soruce node to end point
			Dijkstra::FindShortestPath(graph, s, y, QUEUE_TYPE::ARRAY);
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		case 4:
		{
			cout << "What name is this graph called?: ";
			std::string fileName;
			cin >> fileName;
			string filePath = "data/" + fileName + ".csv";
			cout << filePath << endl;
			graph->ExportGraph(filePath);
			break;
		}
		case 5:
		{
			break;
		}
		default:
			break;
		}


	} while (choice != 5);
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
		{
			if (g->adjMatrix[i][j] == INT_MAX)
				printf("\t%c", 236);
			else
				printf("\t%d", g->adjMatrix[i][j]);
		}

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

	//Variable declaration
	int i;
	ListNode* temp;
	//Sanity check
	//Print at each index.
	cout << "Legend: ConnectedNode:Cost" << endl;
	for (i = 0; i < g->V; i++)
	{
		printf("%d:\t", i + 1);
		temp = g->adjList[i];
		while (temp != NULL) {
			cout << temp->node->GetName() << ":" << temp->cost;
			if (temp->next != NULL)
				cout << " -> ";
			temp = temp->next;
		}
		cout << endl;
	}

}


