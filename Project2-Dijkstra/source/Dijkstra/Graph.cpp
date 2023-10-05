#include "Graph.h"

Graph::Graph()
	:V(0), E(0)
{
}

Graph::~Graph()
{
}

/// <summary>
/// Sets a number of vertices if we know the graph's vertices beforehand.
/// </summary>
/// <param name="vertices">number of vertices</param>
void Graph::SetNoOfVertices(int v)
{
	//Clear all the previous entries if there exists
	this->adjMatrix.clear();
	this->adjList.clear();

	this->V = v;
	//Then resize our adjacency matrix and lists
	this->adjMatrix.resize(this->V);

	//Resize adjacency list to have |V| elements
	this->adjList.resize(v);

	//Then resize the adj matrix at each i and create a list node at each i
	for (int i = 0; i < this->V; i++)
	{
		this->adjMatrix[i].resize(this->V);
	}
	//Clear nodes map
	nodes.clear();
}

/// <summary>
/// Clears all vertices and edges from the graph
/// </summary>
void Graph::Clear()
{
	//Unsure if these clears all the sub vectors, need to check. but should work for now even if it stays in memory
	adjMatrix.clear();
	adjList.clear();
	nodes.clear();

	//Reset vertices and edges
	this->V = 0;
	this->E = 0;
}

/// <summary>
/// Loads a graph from a csv file
/// </summary>
/// <param name="file">fileName or path</param>
bool Graph::LoadGraph(std::string file)
{
	//Clear all our adjlist and matrices
	Clear();
	// Make sure the file is open
	vector<pair<int, int>> data;
	vector<int> weights;

	//Reset back to 0
	this->V = 0;
	this->E = 0;

	if (!DataHandler::ReadCSV(file, data, weights, this->V))
		return false;

	//Update edge count
	this->E = (int)data.size();
	cout << "Managed to import graph with " << this->V << " vertices and " << this->E << " edges." << endl;

	//Then resize our vectors accordingly
	adjMatrix.resize(this->V);
	for (int i = 0; i < adjMatrix.size(); i++)
	{
		adjMatrix[i] = vector<int>(this->V, INT_MAX);
	}
	//Resize adj list
	adjList.resize(this->V);

	//Instantiate nodes up to V
	for (int i = 0; i < this->V; i++)
	{
		//Create a new node and store into nodes
		Node* newNode = new Node(i, 0, to_string(i + 1));
		nodes[i] = newNode;
	}

	//Loop through our edges and update the weights accordingly
	for (int i = 0; i < data.size(); i++)
	{
		//first is source
		//second is target
		int source = data[i].first;
		int neighbour = data[i].second;
		int weight = weights[i];

		//Update the adj matrix
		//If bidirectional change here later.
		adjMatrix[source - 1][neighbour - 1] = weight;
	}

	//Once populated, update our adj list
	UpdateAdjacencyList();

	//Then print our matrix and list
	PrintAdjMatrix();
	PrintAdjList();

	return true;
}

/// <summary>
/// 
/// </summary>
/// <param name="file"></param>
/// <param name="edges"></param>
/// <param name="weights"></param>
bool Graph::ExportGraph(std::string file)
{
	vector<string> data;
	//Use our adjacency list to generate outputs as its faster
	for (int i = 0; i < adjList.size(); i++)
	{
		//If null entry go next
		if (adjList[i] == NULL)
			continue;

		//Loop through this current listnode and append
		string source = nodes[i]->GetName();
		ListNode* it = adjList[i];
		while (it != NULL)
		{
			string d = source + "," + it->node->GetName() + "," + to_string(it->cost);
			data.push_back(d);
			it = it->next;
		}
	}
	//Then call our static class to write the write the data
	DataHandler::WriteCSV(file, { "source","target","weight" }, data);
	return true;
}

/// <summary>
/// Prints the graph's adj matrix
/// </summary>
void Graph::PrintAdjMatrix()
{
	int i, j;
	//Print the rows first.
	printf("Adjacency Matrix\n");
	if (this->V == 0)
		return;

	//Print divider.
	for (i = 0; i < this->V; i++)
	{
		printf("----------");
	}
	printf("\n|  \t|");
	for (i = 0; i < this->V; i++)
	{
		printf("\t%d", i + 1);
	}
	printf("  |\n");
	//Print divider.
	for (i = 0; i < this->V; i++)
	{
		printf("----------");
	}
	printf("\n");
	for (i = 0; i < this->V; i++) {
		//Print divider.
		printf("| %d\t|", i + 1);
		for (j = 0; j < this->V; j++)
		{
			if (this->adjMatrix[i][j] == INT_MAX)
				printf("\t%c", 236);
			else
				printf("\t%d", this->adjMatrix[i][j]);
		}

		printf("  |\n");
	}
	//Print divider.
	for (i = 0; i < this->V; i++)
	{
		printf("----------");
	}
	printf("\n");
}

/// <summary>
/// Prints the graph's adj list
/// </summary>
void Graph::PrintAdjList()
{
	//Variable declaration
	int i;
	ListNode* temp;
	//Sanity check
	//Print at each index.
	cout << "Legend: ConnectedNode:Cost" << endl;
	for (i = 0; i < this->V; i++)
	{
		printf("%d:\t", i + 1);
		temp = this->adjList[i];
		while (temp != NULL) {
			cout << temp->node->GetName() << ":" << temp->cost;
			if (temp->next != NULL)
				cout << " -> ";
			temp = temp->next;
		}
		cout << endl;
	}
}


/// <summary>
/// Populates our adjacency list based on our adjacency matrix
/// </summary>
void Graph::UpdateAdjacencyList()
{
	//Loop through the adjMatrix
	for (int i = 0; i < adjMatrix.size(); i++)
	{
		for (int j = 0; j < adjMatrix.size(); j++)
		{
			//Ignore weights to itself
			if (i == j)
				continue;

			//Check if the weight is not max, if its not, then there exists a weight betweeb some arbitrary node i,j
			if (adjMatrix[i][j] != INT_MAX)
			{
				//Check if we have created if at this index, a list node has been created
				if (adjList[i] == NULL)
				{
					//Create a listnode at this location and set the cost
					ListNode* n = new ListNode();
					n->cost = adjMatrix[i][j];
					n->node = nodes[j];
					n->next = NULL;
					adjList[i] = n;
				}
				else
				{
					//There exists nodes before this so just go to end and repeat
					ListNode* curr = adjList[i];
					//Make curr go to last element
					while (curr->next != NULL)
					{
						curr = curr->next;
					}
					//Make a new list node with this cost and insert at back
					ListNode* n = new ListNode();
					n->cost = adjMatrix[i][j];
					n->node = nodes[j];
					n->next = NULL;
					//Update it at last index
					curr->next = n;
				}

			}
		}
	}
}

