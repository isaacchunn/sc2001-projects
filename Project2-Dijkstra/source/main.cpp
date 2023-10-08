#include <stdio.h>
#include <iostream>
#include "Dijkstra/Graph.h"
#include "Dijkstra/Node.h"
#include "Dijkstra/ListNode.h"
#include "Dijkstra/Dijkstra.h"
#include "Misc/Timer.h"
#include <filesystem>

#define M INT_MAX
#define MAX_VERTICE 1000
#define MAX_DENSITY 1000
#define AVG_SAMPLES 10
//#define DEBUG 

int main()
{	//Initialize time
	srand(time(NULL));
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
		cout << "5) Print Graph Details" << endl;
		cout << "6) Find Shortest Path" << endl;
		cout << "7) Dijkstra [Single]" << endl;
		cout << "8) Dijkstra [Fixed Density Varying V]" << endl;
		cout << "9) Dijkstra [Fixed V Varying Density]" << endl;
		cout << "10) Dijkstra [Complete Graph up to N]" << endl;
		cout << "11) Dijkstra [Chosen V and D]" << endl;
		cout << "12) Clear Console" << endl;
		cout << "13) Quit" << endl;
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
			int n, density, mode;
			cout << "Enter number of nodes: ";
			cin >> n;
			cout << "Enter density: ";
			cin >> density;
			cout << "Enter type DIRECTIONAL:0 or BIDIRECTIONAL:1 : " << endl;
			cin >> mode;
			graph->type = GRAPH_TYPE(mode);
			graph->GenerateRandomGraph(n, density);
			graph->PrintAdjMatrix();
			graph->PrintAdjList();
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
			string filePath = "data/Graphs/" + fileName + ".csv";
			if (graph->ExportGraph(filePath))
				cout << "Graph successfully exported to " + filePath << endl;
			break;
		}
		case 5:
		{
			graph->PrintAdjMatrix();
			graph->PrintAdjList();
			break;
		}
		case 6:
		{
			int sourceVertex, endVertex, mode;
			cout << "Input source vertex: " << endl;
			cin >> sourceVertex;
			cout << "Input end vertex: " << endl;
			cin >> endVertex;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;
			//Then try print the shortest path from the source node to end point
			Dijkstra::FindShortestPath(graph, sourceVertex, endVertex, (QUEUE_TYPE)mode);
			break;
		}
		case 7:
		{
			if (graph->V == 0)
			{
				cout << "Load or generate a graph first!" << endl;
				break;
			}

			int sourceVertex, mode;
			cout << "Input source vertex: " << endl;
			cin >> sourceVertex;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;

			long sumTime = 0;
			for (int i = 0; i < AVG_SAMPLES; i++)
			{
				Dijkstra::CalculateShortestPath(graph, sourceVertex, (QUEUE_TYPE)mode);
				sumTime += Timer::GetDuration().count();
				std::cout << " Time taken: " << Timer::GetDuration().count() << " microseconds" << std::endl;
			}
			std::cout << "Average Time taken: " << sumTime / AVG_SAMPLES << " microseconds" << std::endl;


			break;
		}
		case 8:
		{
			//Fixed density varying n
			int density, mode, samples, vertices, graphMode;
			cout << "Input max vertices: " << endl;
			cin >> vertices;
			cout << "Input density: " << endl;
			cin >> density;
			cout << "Input samples: " << endl;
			cin >> samples;
			cout << "Enter type DIRECTIONAL:0 or BIDIRECTIONAL:1 : " << endl;
			cin >> graphMode;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;

			//Update graph mode
			graph->type = (GRAPH_TYPE)graphMode;

			string folderPath = "data/VaryingVFixedD/";
			string folderName = "V_" + to_string(vertices) + "_D_" + to_string(density);
			if (mode == HEAP)
				folderName += "_Heap";
			else
				folderName += "_Array";
			string filePath = folderPath + folderName + "/" + folderName + ".csv";

			//Make directory
			if (!std::filesystem::exists(folderPath + folderName))
				std::filesystem::create_directory(folderPath + folderName + "/");
			if (!std::filesystem::exists(folderPath + folderName + "/Graph"))
				std::filesystem::create_directory(folderPath + folderName + "/Graph/");

			//Trivial checking
			if (vertices < 0 || density < 0)
			{
				cout << "Vertices or density cannot be 0." << endl;
				break;
			}
			vector<string> stringData;
			//Take up to input vertices / samples if its divisible
			int step = vertices / samples;
			int graphNumber = 1;
			for (int i = step; i <= vertices; i += step)
			{
				string data = to_string(i) + "," + to_string(density) + ",";
				//Generate a graph based on this density and node number (i)
				graph->GenerateRandomGraph(i, density);
				//Export our graph so we can track and print in python~
				//graph->ExportGraph(folderPath + folderName + "/Graph/graph" + to_string(graphNumber) + ".csv");

#ifdef DEBUG
				graph->PrintAdjMatrix();
				graph->PrintAdjList();
#endif
				long sumTime = 0;
				for (int j = 0; j < AVG_SAMPLES; j++)
				{				
					//Then start from the first vertex 0
					Dijkstra::CalculateShortestPath(graph, 0, (QUEUE_TYPE)mode);
					sumTime += Timer::GetDuration().count();
					//std::cout << " Time taken: " << Timer::GetDuration().count() << " microseconds" << std::endl;
				}
				cout << "Iteration: " << i + 1 << "|";
				std::cout << " Average Time taken: " << sumTime / AVG_SAMPLES << " microseconds" << std::endl;
				//Then append the time taken
				data += to_string(sumTime / AVG_SAMPLES);
				stringData.push_back(data);

				//Increment graph Number
				graphNumber++;
			}

			//Then finally export into relevant excels
			DataHandler::WriteCSV(filePath, { "Vertices","Density","Time taken(ms)" }, stringData);
			cout << "Data successfully exported to " << filePath << endl;
			break;
		}
		case 9:
		{
			//Fixed n varying density
			int density, mode, samples, vertices,graphMode;
			cout << "Input vertices: " << endl;
			cin >> vertices;
			cout << "Input max density: " << endl;
			cin >> density;
			cout << "Input samples: " << endl;
			cin >> samples;
			cout << "Enter type DIRECTIONAL:0 or BIDIRECTIONAL:1 : " << endl;
			cin >> graphMode;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;

			//Update graph mode
			graph->type = (GRAPH_TYPE)graphMode;

			string folderPath = "data/VaryingDFixedV/";
			string folderName = "V_" + to_string(vertices) + "_D_" + to_string(density);
			if (mode == HEAP)
				folderName += "_Heap";
			else
				folderName += "_Array";
			
			string filePath = folderPath + folderName + "/" + folderName + ".csv";

			//Make directory
			if (!std::filesystem::exists(folderPath + folderName))
				std::filesystem::create_directory(folderPath + folderName + "/");
			if (!std::filesystem::exists(folderPath + folderName + "/Graph"))
				std::filesystem::create_directory(folderPath + folderName + "/Graph/");

			//Trivial checking
			if (vertices < 0 || density < 0)
			{
				cout << "Vertices or density cannot be 0." << endl;
				break;
			}
			vector<string> stringData;
			//Take up to input vertices / samples if its divisible
			int step = density / samples;
			int graphNumber = 1;
			for (int i = step; i <= density; i += step)
			{
				string data = to_string(vertices) + "," + to_string(i) + ",";
				//Generate a graph based on this density and node number (i)
				graph->GenerateRandomGraph(vertices, i);
				//Export our graph so we can track and print in python~
				//graph->ExportGraph(folderPath + folderName + "/graph/Graph" + to_string(graphNumber) + ".csv");

#ifdef DEBUG
				graph->PrintAdjMatrix();
				graph->PrintAdjList();
#endif
				long sumTime = 0;
				for (int j = 0; j < AVG_SAMPLES; j++)
				{
					//Then start from the first vertex 0
					Dijkstra::CalculateShortestPath(graph, 0, (QUEUE_TYPE)mode);
					sumTime += Timer::GetDuration().count();
				}
				cout << "Iteration: " << i + 1 << "|";
				//Timer::PrintDuration();
				std::cout << " Time taken: " << sumTime / AVG_SAMPLES << " microseconds" << std::endl;
				//Then append the time taken
				data += to_string(sumTime / AVG_SAMPLES);
				stringData.push_back(data);

				//Increment graph Number
				graphNumber++;
			}

			//Then finally export into relevant excels
			DataHandler::WriteCSV(filePath, { "Vertices","Density","Time taken(ms)" }, stringData);
			cout << "Data successfully exported to " << filePath << endl;
			break;
		}
		case 10:
		{			
			//Fixed density varying n
			int mode, samples, vertices, graphMode;
			cout << "Input max vertices: " << endl;
			cin >> vertices;
			cout << "Input samples: " << endl;
			cin >> samples;
			cout << "Enter type DIRECTIONAL:0 or BIDIRECTIONAL:1 : " << endl;
			cin >> graphMode;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;

			//Update graph mode
			graph->type = (GRAPH_TYPE)graphMode;

			string folderPath = "data/VaryingVVaryingD/";
			string folderName = "V_" + to_string(vertices) + "_D_" + to_string(vertices);
			if (mode == HEAP)
				folderName += "_Heap";
			else
				folderName += "_Array";
			string filePath = folderPath + folderName + "/" + folderName + ".csv";

			//Make directory
			if (!std::filesystem::exists(folderPath + folderName))
				std::filesystem::create_directory(folderPath + folderName + "/");
			if (!std::filesystem::exists(folderPath + folderName + "/Graph"))
				std::filesystem::create_directory(folderPath + folderName + "/Graph/");

			//Trivial checking
			if (vertices < 0)
			{
				cout << "Vertices cannot be 0." << endl;
				break;
			}
			vector<string> stringData;
			//Take up to input vertices / samples if its divisible
			int step = vertices / samples;
			int graphNumber = 1;
			for (int i = step; i <= vertices; i += step)
			{
				string data = to_string(i) + "," + to_string(i) + ",";
				//Generate a graph based on this density and node number (i)
				graph->GenerateRandomGraph(i, i);
				//Export our graph so we can track and print in python~
				//graph->ExportGraph(folderPath + folderName + "/Graph/graph" + to_string(graphNumber) + ".csv");

#ifdef DEBUG
				graph->PrintAdjMatrix();
				graph->PrintAdjList();
#endif
				long sumTime = 0;
				for (int j = 0; j < AVG_SAMPLES; j++)
				{
					//Then start from the first vertex 0
					Dijkstra::CalculateShortestPath(graph, 0, (QUEUE_TYPE)mode);
					sumTime += Timer::GetDuration().count();
					//std::cout << " Time taken: " << Timer::GetDuration().count() << " microseconds" << std::endl;
				}
				cout << "Iteration: " << i + 1 << "|";
				std::cout << " Average Time taken: " << sumTime / AVG_SAMPLES << " microseconds" << std::endl;
				//Then append the time taken
				data += to_string(sumTime / AVG_SAMPLES);
				stringData.push_back(data);

				//Increment graph Number
				graphNumber++;
			}

			//Then finally export into relevant excels
			DataHandler::WriteCSV(filePath, { "Vertices","Density","Time taken(ms)" }, stringData);
			cout << "Data successfully exported to " << filePath << endl;
			break;
		}
		case 11:
		{
			//Fixed n fixed d
			int density, mode, samples, vertices, graphMode;
			cout << "Input vertices: " << endl;
			cin >> vertices;
			cout << "Input density: " << endl;
			cin >> density;
			cout << "Enter type DIRECTIONAL:0 or BIDIRECTIONAL:1 : " << endl;
			cin >> graphMode;
			cout << "Input mode (0: HEAP, 1: ARRAY): ";
			cin >> mode;

			//Update graph mode
			graph->type = (GRAPH_TYPE)graphMode;

			string folderPath = "data/FixedDFixedV/";
			string folderName = "V_" + to_string(vertices) + "_D_" + to_string(density);
			if (mode == HEAP)
				folderName += "_Heap";
			else
				folderName += "_Array";
			string filePath = folderPath + folderName + "/" + folderName + ".csv";

			//Make directory
			if (!std::filesystem::exists(folderPath + folderName))
				std::filesystem::create_directory(folderPath + folderName + "/");


			//Trivial checking
			if (vertices < 0 || density < 0)
			{
				cout << "Vertices or density cannot be 0." << endl;
				break;
			}
			vector<string> stringData;
			//Take up to input vertices / samples if its divisible
			string data = to_string(vertices) + "," + to_string(density) + ",";
			//Generate a graph based on this density and node number (i)
			graph->GenerateRandomGraph(vertices, density);
			//Export our graph so we can track and print in python~
			//graph->ExportGraph(folderPath + folderName + "/graph.csv");

#ifdef DEBUG
			graph->PrintAdjMatrix();
			graph->PrintAdjList();
#endif
			//Then start from the first vertex 0
			Dijkstra::CalculateShortestPath(graph, 0, (QUEUE_TYPE)mode);
			Timer::PrintDuration();

			//Then append the time taken
			data += to_string(Timer::GetDuration().count());
			stringData.push_back(data);

			//Then finally export into relevant excels
			DataHandler::WriteCSV(filePath, { "Vertices","Density","Time taken(ms)" }, stringData);
			cout << "Data successfully exported to " << filePath << endl;
			break;
		}
		case 12:
		{
			system("cls");
			break;
		}
		default:
		{
			break;
		}
		}

	} while (choice != 12);
	return 0;
}



