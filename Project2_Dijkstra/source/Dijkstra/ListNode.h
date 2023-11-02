#ifndef LISTNODE_H
#define LISTNODE_H

#include "Node.h"

//Represent the costs of the graph in adjacency list
struct ListNode
{
	//Associated node for identification purposes
	Node* node;
	//Weight to this node
	int cost;
	//Next node
	ListNode* next;
};
#endif

