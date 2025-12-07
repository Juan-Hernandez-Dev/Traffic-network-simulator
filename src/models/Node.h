#ifndef NODE_H
#define NODE_H

#include <string>
#include "Edge.h"

struct Node {
    int id;
    std::string name;
    Edge* adjacencyList;
    bool active;

    Node() : id(-1), name(""), adjacencyList(nullptr), active(false) {}
};

#endif
