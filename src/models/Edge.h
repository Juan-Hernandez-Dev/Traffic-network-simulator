#ifndef EDGE_H
#define EDGE_H

struct Edge {
    int destination;
    double weight;
    Edge* next;

    Edge(int dest, double w) : destination(dest), weight(w), next(nullptr) {}
};

#endif
