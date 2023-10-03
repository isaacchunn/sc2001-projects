//
//  Node.cpp
//  DijkstraProject
//
//  Created by Isaac on 3/10/23.
//

#include "Node.h"

Node::Node() :
    dist(INT_MAX),
    vertex(-1),
    name("Test Node")
{
    
}

Node::Node(int vertex, int distance, std::string name = "Test Node")
    : vertex(vertex),
    dist(distance),
    name(name)
{
    
}

int Node::GetVertex()
{
    return this->vertex;
}

int Node::GetDistanceFromSource()
{
    return this->dist;
}

std::string Node::GetName()
{
    return this->name;
}

void Node::SetVertex(int vertex)
{
    this->vertex = vertex;
}

void Node::SetDistanceFromSource(int distance)
{
    this->dist = distance;
}

void Node::Setname(std::string name)
{
    this->name = name;
}
