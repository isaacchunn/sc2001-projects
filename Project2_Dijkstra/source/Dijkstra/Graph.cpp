#include "Graph.h"

#define MAX_TRIES 50

Graph::Graph()
	:V(0), E(0), type(GRAPH_TYPE::DIRECTIONAL)
{
}
Graph::Graph(GRAPH_TYPE type)
	:V(0), E(0), type(type)
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

	//Resize node list
	this->nodes.resize(v);

	//Then resize the adj matrix at each i and create a list node at each i
	for (int i = 0; i < this->V; i++)
	{
		this->adjMatrix[i].resize(this->V);
	}
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

	//Resize node list
	nodes.resize(this->V);
	//Instantiate nodes up to V
	for (int i = 0; i < this->V; i++)
	{
		//Create a new node and store into nodes
		Node* newNode = new Node(i, 0, to_string(i + 1));
		nodes[i] = newNode;
	}

	//Loop through our edges and update the weights accordingly
	for (int i = 0; i < (int)data.size(); i++)
	{
		//first is source
		//second is target
		int source = data[i].first;
		int neighbour = data[i].second;
		int weight = weights[i];

		//Update the adj matrix
		//If bidirectional change here later.
		adjMatrix[source - 1][neighbour - 1] = weight;

		if (type == BIDIRECTIONAL) //both the weights of each other are same
			adjMatrix[neighbour - 1][source - 1] = weight;
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
	for (int i = 0; i < this->V; i++)
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
	if (this->V == 0)
	{
		cout << "Graph is empty. No adj matrix." << endl;
		return;
	}
	int i, j;
	//Print the rows first.
	printf("Adjacency Matrix\n");

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
	if (this->V == 0)
	{
		cout << "Graph is empty. No adj list." << endl;
		return;
	}

	//Variable declaration
	int i;
	ListNode* temp;
	//Sanity check
	//Print at each index.
	cout << "Adjacency List" << endl;
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
/// Generates a random graph with a fixed number of nodes and density
/// </summary>
/// <param name="numberOfNodes">number of nodes</param>
/// <param name="density">number of edges a node can connect to</param>
void Graph::GenerateRandomGraph(int numberOfNodes, int density)
{
	//Max density is n - 1
	//Error handling to limit density to number of nodes
	if (density >= numberOfNodes)
		density = numberOfNodes - 1;

	//Clear any previous graph if not done yet
	Clear();
	//Update the number of nodes in our vertices
	this->V = numberOfNodes;

	//Use an unordered map to store edges for each node to count the edges
	unordered_map<int, int> edges;
	//Some vector to keep track of remaining vertexes left
	vector<int> vertexesLeft = vector<int>(this->V, 0);
	//Resize our adj list and matrix
	adjMatrix.resize(this->V);
	//Resize nodes
	this->nodes.resize(this->V);
	for (int i = 0; i < this->V; i++)
	{
		//Initialize all to max to show the links
		adjMatrix[i] = vector<int>(this->V, INT_MAX);
		//Then update the vector to be 0 on the diagonals
		adjMatrix[i][i] = 0;

		//Update our edge and node map
		edges[i] = 0; //<0,0>

		//Create a new node and store into nodes
		Node* newNode = new Node(i, 0, to_string(i + 1));
		nodes[i] = newNode;

		vertexesLeft[i] = i;
	}
	adjList.resize(this->V);

	//We dont need to add connections if the V is <=1
	if (this->V <= 1)
		return;

	//Two pass generation to cover up any remaining gaps by earlier as there seems to be bias to earlier nodes?
	for (int y = 0; y < 2; y++)
	{
		//Save second iteration if vertexes left are all zero
		if (vertexesLeft.size() == 0 && type == BIDIRECTIONAL)
			break;

		//Then randomly generate up to n
		for (int i = 0; i < this->V; i++)
		{
			//If current node has reached max, we can skip the generation
			if (edges[i] == density && type == BIDIRECTIONAL)
				continue;

			//There are more nodes than density, so just for loop and try
			//For loop up to density and connect to previously connected graphs
			for (int j = edges[i]; j < density; j++)
			{
				//If there are no more vertexes left...
				if (vertexesLeft.size() == 0)
					break;

				//Generate a weight between vertices
				int weight = (rand() % (this->V * 2)) + 1;
				int randVertex = (rand() % vertexesLeft.size());
				int actualVertex = vertexesLeft[randVertex];
				
				//Tries for this vertex
				int tries = 0;
				while (actualVertex == i || adjMatrix[i][actualVertex] != INT_MAX) //reject overriding weights to itself or adding same weights
				{
					tries++;
					//if only one vertex, nothing else we can do, just return out
					if (vertexesLeft.size() <= 1)
						break;
					if (type == BIDIRECTIONAL && tries > MAX_TRIES)
						break;

					////Print edges
					//for (int k = 0; k < this->V; k++)
					//{
					//	cout << edges[k] << ", ";
					//}
					//cout << endl;
					//cout << "Vertexes left size: " << vertexesLeft.size() << endl;
					//cout << "Vertexes left: ";
					//for (int k = 0; k < vertexesLeft.size(); k++)
					//{
					//	cout << vertexesLeft[k] << ", ";
					//}
					//cout << endl;
					//cout << "Generated Vertex: " << actualVertex << " i: " << i << endl;

					randVertex = (rand() % vertexesLeft.size());
					actualVertex = vertexesLeft[randVertex];
				}
				//cout << "Adding edge between " << i << " and " << actualVertex << " of weight: " << weight << endl;
				//Then link this vertex to actual vertex
				adjMatrix[i][actualVertex] = weight;
				//increase edge at this place
				edges[i]++;

				//Check if edges has reached density, and remove it from vertexes left
				if (edges[i] >= density && type == BIDIRECTIONAL)
				{
					int z;
					//Remove this the index in the vertexesLeft
					for (z = 0; z < vertexesLeft.size(); z++)
					{
						if (vertexesLeft[z] == i)
							break;
					}
					//Remove it 
					if (z != vertexesLeft.size())
						vertexesLeft.erase(vertexesLeft.begin() + z);
				}

				if (type == BIDIRECTIONAL)
				{
					adjMatrix[actualVertex][i] = weight;
					edges[actualVertex]++;

					if (edges[actualVertex] >= density)
					{
						//Check if edges is there, and remove it from the vertexesleft
						int z;
						//Remove this the index in the vertexesLeft
						for (z = 0; z < vertexesLeft.size(); z++)
						{
							if (vertexesLeft[z] == actualVertex)
								break;
						}
						//Remove it 
						if (z != vertexesLeft.size())
							vertexesLeft.erase(vertexesLeft.begin() + z);
					}
				}
				this->E++;
			}
		}
	}
	//cout << "Graph finished generating." << endl;
	//After this is done, calculate our adj list
	UpdateAdjacencyList();

}


/// <summary>
/// Populates our adjacency list based on our adjacency matrix
/// </summary>
void Graph::UpdateAdjacencyList()
{
	//Loop through the adjMatrix
	for (int i = 0; i < this->V; i++)
	{
		for (int j = 0; j < this->V; j++)
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

