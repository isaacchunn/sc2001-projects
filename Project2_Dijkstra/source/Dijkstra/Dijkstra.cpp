#include "Dijkstra.h"

//Static variable declarations
vector<int> Dijkstra::S = {};
vector<Node*> Dijkstra::pi = {};

#define ADDALLNODES

/// <summary>
/// Calculates the shortest paths from source to each linked node using a minimizing heap and adjacency list implementation.
/// </summary>
/// <param name="g">graph</param>
/// <param name="source">source node</param>
void Dijkstra::CalculateShortestPathHeap(Graph* g, Node* source)
{
	//Handle trivial cases
	if (g == NULL || source == NULL)
		return;

	//cout << "[Heap] Calculating Shortest Path from " << source->GetName() << endl;
	Timer::Start();

	//Initialize new priority queue
	//Priority queue in terms of int distances, we will utilise the map
	PriorityQueue pq = PriorityQueue(TYPE::MINIMISING);

	//For each vertice in graph (assumed to be in ascending order)
	for (int v = 0; v < g->V; v++)
	{
		//Set distance of each node from source to be MAX
		g->nodes[v]->SetDistanceFromSource(INT_MAX);
		//Initialize all predecessors to NULL
		pi[v] = NULL;
		//Initialize all S to be 0 as none are in the set at this time
		S[v] = 0;
	}
	//Update distance to source to be 0 as source -> source is 0
	source->SetDistanceFromSource(0);

#ifdef ADDALLNODES
	//Insert every vertice in the graph into pq
	for (int i = 0; i < g->V; i++)
	{
		pq.Insert(g->nodes[i]);
	}
#endif

#ifndef ADDALLNODES
	//Insert source as first element of priority queue
	pq.Insert(source);
#endif

	//pq.PrintQueue();

	//Print iterations
#ifdef DEBUGPRINT
	int iteration = 1;
#endif

	//While the queue is not empty, extract
	while (!pq.IsEmpty())
	{
#ifdef DEBUGPRINT
		Debug(g, iteration++);
#endif
		//Pop first u to get first vertex
		Node* u = pq.Top();
#ifdef DEBUGPRINT
		//cout << "Popped " << u->GetName() << " with vertex " << u->GetVertex() << endl;
#endif
		int uVertex = u->GetVertex();
		int uDist = u->GetDistanceFromSource();
		//Update visited array
		S[uVertex] = 1;
		//Then for each vertex v adjacent to u
		//Use the adjacency list
		ListNode* curr = g->adjList[uVertex];
		//Go through all the neighbours
		while (curr != NULL)
		{
			Node* adjNode = curr->node;
			int adjVertex = adjNode->GetVertex();
			int adjDist = adjNode->GetDistanceFromSource();
#ifndef ADDALLNODES
			//If the node has not been visited yet, and is not already in the queue, we add it.
			if (S[adjNode->GetVertex()] == 0)
			{
				pq.Insert(adjNode);
			}
#endif
			//If this node is not in the shortest path set
			//And the current distance to the node is more than the current cost to REACH current vertex + distance from this vertex to node
			if (S[adjVertex] != 1 && adjDist > uDist + curr->cost)
			{
				//Remove this node and update back
				pq.Delete(adjNode);
				//Update the distance of adjacent node to the shorter distance
				adjNode->SetDistanceFromSource(uDist + curr->cost);
				//Update pre-decessor
				pi[adjVertex] = u;
				//Insert the node back into the queue with updated weights
				pq.Insert(adjNode);
			}
			curr = curr->next;
		}
	}
	Timer::Stop();
#ifdef DEBUGPRINT
	Debug(g, iteration++);
#endif
}

/// <summary>
/// Calculates the shortest path to all nodes from a source node in a graph using an array as a priority queue
/// </summary>
/// <param name="g">graph</param>
/// <param name="source">source node</param>
void Dijkstra::CalculateShortestPathArray(Graph* g, Node* source)
{
	//Handle trivial cases
	if (g == NULL || source == NULL)
		return;

	//cout << "[Array] Calculating Shortest Path from " << source->GetName() << endl;
	Timer::Start();
	//Initialize new priority queue
	//Priority queue in terms of int distances, we will utilise the map
	PriorityQueueArray pq = PriorityQueueArray(TYPE::MINIMISING);

	//For each vertice in graph (assumed to be in ascending order)
	for (int v = 0; v < g->V; v++)
	{
		//Set distance of each node from source to be MAX
		g->nodes[v]->SetDistanceFromSource(INT_MAX);
		//Initialize all predecessors to NULL
		pi[v] = NULL;
		//Initialize all S to be 0 as none are in the set at this time
		S[v] = 0;
	}
	//Update distance to source to be 0 as source -> source is 0
	source->SetDistanceFromSource(0);

#ifdef ADDALLNODES
	//Insert every vertice in the graph into pq
	for (int i = 0; i < g->V; i++)
	{
		pq.Insert(g->nodes[i]);
	}
#endif

#ifndef ADDALLNODES
	//Insert source as first element of priority queue
	pq.Insert(source);
#endif

	//pq.PrintQueue();

	//Print iterations
#ifdef DEBUG_PRINT
	int iteration = 1;
#endif

	//While the queue is not empty, extract
	while (!pq.IsEmpty())
	{
#ifdef DEBUGPRINT
		Debug(g, iteration++);
#endif
		//Pop first u to get first vertex
		Node* u = pq.GetSmallest();
		int uVertex = u->GetVertex();
		int uDist = u->GetDistanceFromSource();
#ifdef DEBUGPRINT
		cout << "Popped " << u->GetName() << " with vertex " << u->GetVertex() << endl;
#endif
		//Update visited array
		S[uVertex] = 1;
		//Then for each vertex v adjacent to u
		//Look into our adjacency matrix
		for (int i = 0; i < g->V; i++)
		{
			//Look through adjacent nodes
			int cost = g->adjMatrix[uVertex][i];
			if (cost != INT_MAX)
			{
				//There is a link
				Node* adjNode = g->nodes[i];
				int adjVertex = adjNode->GetVertex();
				int adjDist = adjNode->GetDistanceFromSource();
#ifndef ADDALLNODES
				//If the node has not been visited yet, and is not already in the queue, we add it.
				if (S[adjNode->GetVertex()] == 0)
				{
					pq.Insert(adjNode);
				}
#endif
				//If this node is not in the shortest path set
				//And the current distance to the node is more than the current cost to REACH current vertex + distance from this vertex to node
				if (S[adjVertex] != 1 && adjDist > uDist + cost)
				{
					//Remove this node and update back
					pq.Delete(adjNode);
					//Update the distance of adjacent node to the shorter distance
					adjNode->SetDistanceFromSource(uDist + cost);
					//Update pre-decessor
					pi[adjVertex] = u;
					//Insert the node back into the queue with updated weights
					pq.Insert(adjNode);
				}
			}
		}
	}
	Timer::Stop();
#ifdef DEBUGPRINT
	Debug(g, iteration++);
#endif
}

/// <summary>
/// Wrapper function that calculates the shortest path using a heap as priority queue and given a source vertex
/// </summary>
/// <param name="g">graph</param>
/// <param name="sourceVertex">source vertex</param>
void Dijkstra::CalculateShortestPathHeap(Graph* g, int sourceVertex)
{
	Node* source = g->nodes[sourceVertex];
	CalculateShortestPathHeap(g, source);
}

/// <summary>
/// Wrapper function that calculates the shortest path using an array as priority queue and given a source vertex
/// </summary>
/// <param name="g">graph</param>
/// <param name="sourceVertex">source vertex</param>
void Dijkstra::CalculateShortestPathArray(Graph* g, int sourceVertex)
{
	Node* source = g->nodes[sourceVertex];
	CalculateShortestPathArray(g, source);
}

void Dijkstra::FindShortestPath(Graph* g, Node* source, Node* target, QUEUE_TYPE type)
{
	//Trivial case checking
	if (g == NULL || source == NULL || target == NULL)
	{
		cout << "Null pointer exception in finding shortest path" << endl;
		return;
	}

	//Clear our previous vectors
	pi.clear();
	S.clear();

	//Resize our containers to the new graph's vertices
	pi.resize(g->V);
	S.resize(g->V);

	//Calculate our shortest paths from the source node given
	if (type == QUEUE_TYPE::HEAP)
		CalculateShortestPathHeap(g, source);
	else if (type == QUEUE_TYPE::ARRAY)
		CalculateShortestPathArray(g, source);


	vector<Node*> path;
	//Assign current node to be target so we can get our path in reverse
	Node* currentNode = target;
	int pathCost = currentNode->GetDistanceFromSource();
	while (currentNode != NULL && currentNode != source)
	{
		//Push back current node
		path.push_back(currentNode);
		currentNode = pi[currentNode->GetVertex()];
	}
	//Check if no path was found
	if (currentNode == NULL)
	{
		cout << "No path between " << source->GetName() << " and " << target->GetName() << endl;
		return;
	}

	//Else we managed to find a path, so print out total cost
	cout << "Path found success! Path cost: " << pathCost << endl;
	//Push back final source node
	path.push_back(currentNode);
	//Just print in reverse first to show it works!
	for (int i = (int)path.size() - 1; i >= 0; i--)
	{
		cout << path[i]->GetVertex() + 1;
		//cout << path[i]->name;
		if (i != 0)
			cout << " -> ";
	}
	cout << endl;
}

/// <summary>
/// Wrapper function to find shortest path between two known vertexes
/// </summary>
/// <param name="g">graph</param>
/// <param name="sourceVertex">vertex of source node</param>
/// <param name="endVertex">vertex of target node</param>
/// <param name="type">queue type</param>
void Dijkstra::FindShortestPath(Graph* g, int sourceVertex, int endVertex, QUEUE_TYPE type)
{
	if (sourceVertex < 0 || sourceVertex > g->V || endVertex < 0 || endVertex > g->V)
		return;

	Node* source = g->nodes[sourceVertex];
	Node* end = g->nodes[endVertex];
	FindShortestPath(g, source, end, type);
}

/// <summary>
/// Wrapper function to calculate the shortest path to linked nodes from a source node
/// </summary>
/// <param name="g">graph</param>
/// <param name="source">source node</param>
/// <param name="type">type</param>
void Dijkstra::CalculateShortestPath(Graph* g, Node* source, QUEUE_TYPE type)
{
	//DO it here so it does not affect time to clear our vectorsd
	//Clear our previous vectors
	pi.clear();
	S.clear();

	//Resize our containers to the new graph's vertices
	pi.resize(g->V);
	S.resize(g->V);

	switch (type)
	{
	case HEAP: {

		CalculateShortestPathHeap(g, source);
		break;
	}
	case ARRAY:
	{
		CalculateShortestPathArray(g, source);
		break;
	}
	case TOTAL_QUEUETYPE:
	{
		break;
	}
	default:
		break;
	}
}

/// <summary>
/// Wrapper function to calculate the shortest path to linked nodes from a source vertex
/// </summary>
/// <param name="g">graph</param>
/// <param name="sourceVertex">source vertex</param>
/// <param name="type">type</param>
void Dijkstra::CalculateShortestPath(Graph* g, int sourceVertex, QUEUE_TYPE type)
{
	Node* n = g->nodes[sourceVertex];
	CalculateShortestPath(g, n, type);
}

/// <summary>
/// Function that returns the number of visited and unvisited nodes
/// </summary>
void Dijkstra::PrintUnvisitedNodes()
{
	std::string unvisitedNodes;
	int unvisited = 0;
	for (int i = 0; i < (int)S.size(); i++)
	{
		if (S[i] == 0)
		{
			unvisited++;
			unvisitedNodes += to_string(i) + ", ";
		}
	}
	cout << "Visited Nodes: " << S.size() - unvisited << ", Unvisited: " << unvisited << endl;
	cout << unvisitedNodes << endl;
}

void Dijkstra::Debug(Graph* g, int iteration)
{
	cout << "---\nIteration: " << iteration++ << endl;
	//Print S (for tutorial questions)
	cout << "S: ";
	for (auto i : S)
	{
		cout << i << " ";
	}
	cout << endl;
	//Print D
	cout << "D: ";
	for (int i = 0; i < g->V; i++)
	{
		cout << g->nodes[i]->GetDistanceFromSource() << " ";
	}
	cout << endl;
	//Print pi
	cout << "Pi: ";
	for (auto i : pi)
	{
		if (i == NULL)
			cout << "NULL ";
		else
			//cout << i->name << " ";
			cout << i->GetVertex() + 1 << " ";
	}
	cout << endl;
}
