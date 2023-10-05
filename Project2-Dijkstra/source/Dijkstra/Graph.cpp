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
}

/// <summary>
/// Loads a graph from a csv file
/// </summary>
/// <param name="file">fileName or path</param>
void Graph::LoadGraph(std::string file)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="file"></param>
/// <param name="edges"></param>
/// <param name="weights"></param>
void Graph::ExportGraph(std::string file)
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
		cout << endl;
	}
}

