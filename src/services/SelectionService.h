#ifndef SELECTIONSERVICE_H
#define SELECTIONSERVICE_H

#include "models/Graph.h"
#include "models/HashTable.h"
#include <string>

// Reusable selection service - extracts ALL table selection patterns
class SelectionService {
public:
    SelectionService();

    // EXTRACTED: Node selection (appears 6+ times in controllers!)
    int selectNode(const Graph& network, const std::string& title = "SELECT NODE");

    // EXTRACTED: Vehicle selection (appears 2+ times)
    int selectVehicle(const HashTable& registry, const Graph& network,
                     const std::string& title = "SELECT VEHICLE");

    // EXTRACTED: Source and destination node selection (used in edges, routing)
    struct NodePair {
        int sourceId;
        int destId;
        bool cancelled;
    };
    NodePair selectNodePair(const Graph& network,
                           const std::string& sourceTitle = "SELECT SOURCE NODE",
                           const std::string& destTitle = "SELECT DESTINATION NODE",
                           bool allowSame = false);

    // EXTRACTED: Edge direction selection (used in add/remove edge)
    enum class EdgeDirection {
        BIDIRECTIONAL = 0,
        FORWARD = 1,
        REVERSE = 2,
        CANCELLED = -1
    };
    EdgeDirection selectEdgeDirection(int sourceId, int destId,
                                     const std::string& sourceName,
                                     const std::string& destName);

    // EXTRACTED: Vehicle type selection
    std::string selectVehicleType();
};

#endif
