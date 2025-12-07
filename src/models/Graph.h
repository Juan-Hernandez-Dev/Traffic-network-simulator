#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <iostream>
#include "Node.h"
#include "Edge.h"

const int MAX_NODES = 50;

class Graph {
private:
    Node nodes[MAX_NODES];
    int nodeCount;
    int nextId;
    std::string currentFile;  // Track the currently loaded file

    void clearEdges(int nodeIndex);
    void updateNextId();
    void autoSave();  // Auto-save to current file

public:
    Graph();
    ~Graph();

    // CRUD Operations
    bool addNode(int id, const std::string& name);
    bool addNodeAuto(const std::string& name);  // Auto-increment version
    bool removeNode(int id);
    bool addEdge(int sourceId, int destId, double weight);
    bool removeEdge(int sourceId, int destId);

    // File I/O
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    void clearNetwork();

    // Display
    void showAdjacencyList();
    void showAdjacencyMatrix();

    // Getters
    int getNodeCount() const { return nodeCount; }
    int getNextId() const { return nextId; }
    bool nodeExists(int id) const;
    std::string getNodeName(int id) const;
    std::string getCurrentFile() const { return currentFile; }
    const Node* getNodes() const { return nodes; }
    int getMaxNodes() const { return MAX_NODES; }
    int findNodeIndex(int id) const;  // Find array index for a node ID
    int getConnectionCount(int nodeId) const;  // Count edges for a node
};

#endif
