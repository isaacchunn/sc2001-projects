#include <stdio.h>
#include <iostream>
#include "Dijkstra/Graph.h"
#include "Dijkstra/Node.h"
#include "Dijkstra/ListNode.h"
#include "Dijkstra/Dijkstra.h"

using namespace std;

#define M INT_MAX


int main()
{
	//Create a graph
	Graph* graph = new Graph();

	int choice;
	do
	{
		//Print the UI
		cout << endl;
		cout << "---Dijkstra Interface---" << endl;
		cout << "1) Use Tutorial Graph" << endl;
		cout << "2) Randomly Generate Graph" << endl;
		cout << "3) Load Graph" << endl;
		cout << "4) Export Graph" << endl;
		cout << "5) Find Shortest Path" << endl;
		cout << "6) Dijkstra" << endl;
		cout << "7) Quit" << endl;
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
			graph->PrintAdjMatrix();
			graph->PrintAdjList();
			break;
		}
		case 2:
		{
			//TODO
			break;
		}
		case 3:
		{
			cout << "What name is the graph called?: ";
			std::string fileName;
			cin >> fileName;
			string filePath = "data/" + fileName + ".csv";
			if (graph->LoadGraph(filePath))
				cout << "Graph sucessfully imported from " + filePath << endl;

			break;
		}
		case 4:
		{
			cout << "What name is this graph called?: ";
			std::string fileName;
			cin >> fileName;
			string filePath = "data/" + fileName + ".csv";
			if (graph->ExportGraph(filePath))
				cout << "Graph sucessfully exported to " + filePath << endl;
			break;
		}
		case 5:
		{
			int sourceVertex, endVertex, mode;
			cout << "Input source vertex: " << endl;
			cin >> sourceVertex;
			cout << "Input end vertex: " << endl;
			cin >> endVertex;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;


			//Then try print the shortest path from the soruce node to end point
			Dijkstra::FindShortestPath(graph, sourceVertex, endVertex, (QUEUE_TYPE)mode);
			break;
		}
		case 6:
		{
			int sourceVertex, mode;
			cout << "Input source vertex: " << endl;
			cin >> sourceVertex;
			cout << "Input mode (0: HEAP, 1: ARRAY)";
			cin >> mode;
			Dijkstra::CalculateShortestPath(graph, sourceVertex, (QUEUE_TYPE)mode);
			break;
		}
		case 7:
		{
			break;
		}
		default:
		{
			break;
		}
		}

	} while (choice != 7);
	return 0;
}



