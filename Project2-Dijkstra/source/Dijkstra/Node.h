//
//  Node.h
//  Djikstra
//
//  Created by Isaac on 17/9/23.
//

#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
private:
    //Corresponds to which vertex
    int vertex;
    //Name of this node
    std::string name;
    //Current distance to source
    int dist;
public:
    Node();
    Node(int vertex, int dist, std::string name);
    
    //Accessors and Mutators
    int GetVertex();
    int GetDistanceFromSource();
    std::string GetName();
    
    void SetVertex(int vertex);
    void SetDistanceFromSource(int distance);
    void Setname(std::string name);
};
#endif /* NODE_H */
