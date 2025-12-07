#include "SelectionService.h"
#include "services/UIService.h"
#include "utils/tableUtils.h"
#include "utils/colors.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

SelectionService::SelectionService() {}

// EXTRACTED from NetworkController and VehicleController (appears 6+ times!)
int SelectionService::selectNode(const Graph& network, const std::string& title) {
    if (network.getNodeCount() == 0) {
        std::cout << "No nodes available!\n";
        return -1;
    }

    InteractivePaginatedTable table(title, "Name", "Connections");
    const Node* nodes = network.getNodes();

    for (int i = 0; i < network.getMaxNodes(); i++) {
        if (nodes[i].active) {
            int connCount = network.getConnectionCount(nodes[i].id);
            table.addRow(nodes[i].id, nodes[i].name, std::to_string(connCount) + " edges");
        }
    }

    return table.run();
}

// EXTRACTED from VehicleController (appears 2+ times)
int SelectionService::selectVehicle(const HashTable& registry, const Graph& network,
                                   const std::string& title) {
    if (registry.getVehicleCount() == 0) {
        std::cout << "No vehicles available!\n";
        return -1;
    }

    InteractivePaginatedTable table(title, "Plate", "Type", "Location");
    const Vehicle* vehicles = registry.getVehicles();

    for (int i = 0; i < registry.getHashSize(); i++) {
        if (vehicles[i].active) {
            std::string location = network.nodeExists(vehicles[i].currentNodeId)
                ? network.getNodeName(vehicles[i].currentNodeId)
                : "Unknown";
            table.addRow(vehicles[i].id, vehicles[i].plate, vehicles[i].type, location);
        }
    }

    return table.run();
}

// EXTRACTED: Combined source + destination selection (used in add/remove edge, routing)
SelectionService::NodePair SelectionService::selectNodePair(
    const Graph& network,
    const std::string& sourceTitle,
    const std::string& destTitle,
    bool allowSame) {

    NodePair result = {-1, -1, false};

    // Select source
    result.sourceId = selectNode(network, sourceTitle);
    if (result.sourceId == -1) {
        result.cancelled = true;
        return result;
    }

    // Select destination
    result.destId = selectNode(network, destTitle);
    if (result.destId == -1) {
        result.cancelled = true;
        return result;
    }

    // Check for self-loop if not allowed
    if (!allowSame && result.sourceId == result.destId) {
        system("cls");
        std::cout << BOLD << "Error" << RESET << "\n";
        std::cout << RED << "Cannot select the same node for source and destination!" << RESET << "\n";
        result.cancelled = true;
        return result;
    }

    return result;
}

// EXTRACTED from NetworkController::handleAddEdge
SelectionService::EdgeDirection SelectionService::selectEdgeDirection(
    int sourceId, int destId,
    const std::string& sourceName,
    const std::string& destName) {

    int directionChoice = 0;

    while (true) {
        system("cls");
        std::cout << BOLD << "Confirm edge direction" << RESET << "\n\n";

        std::string sourceRole, destRole;

        if (directionChoice == 0) {
            sourceRole = "Bidirectional";
            destRole = "Bidirectional";
        } else if (directionChoice == 1) {
            sourceRole = "Source";
            destRole = "Destination";
        } else {
            sourceRole = "Destination";
            destRole = "Source";
        }

        std::cout << CYAN;
        std::cout << std::setw(6) << "ID" << " | "
                  << std::setw(20) << "Name" << " | "
                  << std::setw(15) << "Role" << "\n";
        std::cout << std::string(50, '-') << "\n";
        std::cout << std::setw(6) << sourceId << " | "
                  << std::setw(20) << sourceName << " | "
                  << std::setw(15) << sourceRole << "\n";
        std::cout << std::setw(6) << destId << " | "
                  << std::setw(20) << destName << " | "
                  << std::setw(15) << destRole << "\n";
        std::cout << RESET << "\n";

        std::cout << "Is this configuration correct?\n";
        std::cout << "[A/D or Left/Right] Change direction | [Enter] Confirm | [ESC] Cancel\n";

        int ch = _getch();

        if (ch == 224 || ch == 0) {
            ch = _getch();
            if (ch == 75 || ch == 'K') { // Left
                directionChoice = (directionChoice - 1 + 3) % 3;
            } else if (ch == 77 || ch == 'M') { // Right
                directionChoice = (directionChoice + 1) % 3;
            }
        } else if (ch == 'a' || ch == 'A') {
            directionChoice = (directionChoice - 1 + 3) % 3;
        } else if (ch == 'd' || ch == 'D') {
            directionChoice = (directionChoice + 1) % 3;
        } else if (ch == 13) { // Enter
            return static_cast<EdgeDirection>(directionChoice);
        } else if (ch == 27) { // ESC
            return EdgeDirection::CANCELLED;
        }
    }
}

// EXTRACTED from VehicleController::handleAddVehicle
std::string SelectionService::selectVehicleType() {
    UIService uiService;
    std::vector<std::string> types = {"Sedan", "Compact", "Truck"};

    int choice = uiService.showSelector("Select vehicle type", types);

    if (choice == -1) {
        return "";  // Cancelled
    }

    return types[choice];
}
