#include "NetworkView.h"
#include <iomanip>

NetworkView::NetworkView() {}

void NetworkView::showAdjacencyList(const Graph& network) {
    if (network.getNodeCount() == 0) {
        showError("Network is empty!");
        return;
    }

    showTitle("Adjacency list");

    const Node* nodes = network.getNodes();
    for (int i = 0; i < network.getMaxNodes(); i++) {
        if (nodes[i].active) {
            std::cout << "[" << nodes[i].id << "] " << nodes[i].name << " -> ";

            Edge* current = nodes[i].adjacencyList;
            if (current == nullptr) {
                std::cout << "(no connections)";
            } else {
                while (current != nullptr) {
                    // Find destination node name
                    std::string destName = "";
                    for (int j = 0; j < network.getMaxNodes(); j++) {
                        if (nodes[j].active && nodes[j].id == current->destination) {
                            destName = nodes[j].name;
                            break;
                        }
                    }
                    std::cout << destName << "(" << current->weight << ")";
                    if (current->next != nullptr) {
                        std::cout << ", ";
                    }
                    current = current->next;
                }
            }
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

void NetworkView::showAdjacencyMatrix(const Graph& network) {
    if (network.getNodeCount() == 0) {
        showError("Network is empty!");
        return;
    }

    showTitle("Adjacency matrix");

    const Node* nodes = network.getNodes();

    // Header
    std::cout << std::setw(6) << " ";
    for (int i = 0; i < network.getMaxNodes(); i++) {
        if (nodes[i].active) {
            std::cout << std::setw(6) << nodes[i].id;
        }
    }
    std::cout << "\n";

    // Matrix
    for (int i = 0; i < network.getMaxNodes(); i++) {
        if (nodes[i].active) {
            std::cout << std::setw(6) << nodes[i].id;

            for (int j = 0; j < network.getMaxNodes(); j++) {
                if (nodes[j].active) {
                    double weight = 0.0;
                    Edge* current = nodes[i].adjacencyList;
                    while (current != nullptr) {
                        if (current->destination == nodes[j].id) {
                            weight = current->weight;
                            break;
                        }
                        current = current->next;
                    }

                    if (weight > 0) {
                        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << weight;
                    } else {
                        std::cout << std::setw(6) << "-";
                    }
                }
            }
            std::cout << "\n";
        }
    }
    std::cout << "\n";
}

void NetworkView::showNodeDetails(const Node& node) {
    std::cout << "Node ID: " << node.id << "\n";
    std::cout << "Name: " << node.name << "\n";
    std::cout << "Active: " << (node.active ? "Yes" : "No") << "\n";
}
