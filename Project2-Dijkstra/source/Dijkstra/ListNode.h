#ifndef LISTNODE_H
#define LISTNODE_H

#include "Node.h"

//Represent the costs of the graph in adjacency list
struct ListNode
{
    //Associated node
    Node * node;
	ListNode* next;
};
#endif

