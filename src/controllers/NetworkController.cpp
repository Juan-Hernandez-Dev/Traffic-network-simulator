#include "NetworkController.h"
#include "utils/inputUtils.h"
#include "utils/colors.h"
#include "services/SelectionService.h"
#include "services/MessageService.h"
#include "services/FileService.h"
#include <fstream>
#include <iomanip>
#include <conio.h>

NetworkController::NetworkController(Graph& net) : network(net) {}

// Services
static SelectionService selectionService;
static MessageService messageService;
static FileService fileService;

void NetworkController::handleLoadNetwork() {
    messageService.showTitle("Load network");

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [this](const std::string& name) {
        fileService.loadNetwork(name, network);
    })) {
        messageService.showCancelled();
    }
}

void NetworkController::handleSaveNetwork() {
    messageService.showTitle("Save network");

    if (network.getNodeCount() == 0) {
        messageService.showError("Network is empty! Nothing to save.");
        return;
    }

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [this](const std::string& name) {
        fileService.saveNetwork(name, network);
    })) {
        messageService.showCancelled();
    }
}

void NetworkController::handleAddNode() {
    messageService.showTitle("Add node");

    auto name = getStringInput("Enter node name: ");
    if (!withInput(name, [this](const std::string& nodeName) {
        network.addNodeAuto(nodeName);
    })) {
        messageService.showCancelled();
    }
}

void NetworkController::handleAddEdge() {
    messageService.showTitle("Add edge");

    if (network.getNodeCount() == 0) {
        messageService.showError("No nodes in network! Add nodes first.");
        return;
    }

    auto nodePair = selectionService.selectNodePair(network, "SELECT SOURCE NODE", "SELECT DESTINATION NODE", false);
    if (nodePair.cancelled) {
        messageService.showCancelled();
        return;
    }

    auto direction = selectionService.selectEdgeDirection(
        nodePair.sourceId, nodePair.destId,
        network.getNodeName(nodePair.sourceId),
        network.getNodeName(nodePair.destId)
    );

    if (direction == SelectionService::EdgeDirection::CANCELLED) {
        messageService.showCancelled();
        return;
    }

    auto weight = getDoubleInput("Enter weight (distance/time): ");
    if (!withInput(weight, [&](double w) {
        if (direction == SelectionService::EdgeDirection::BIDIRECTIONAL) {
            network.addEdge(nodePair.sourceId, nodePair.destId, w);
            network.addEdge(nodePair.destId, nodePair.sourceId, w);
        } else if (direction == SelectionService::EdgeDirection::FORWARD) {
            network.addEdge(nodePair.sourceId, nodePair.destId, w);
        } else if (direction == SelectionService::EdgeDirection::REVERSE) {
            network.addEdge(nodePair.destId, nodePair.sourceId, w);
        }
    })) {
        messageService.showCancelled();
    }
}

void NetworkController::handleRemoveNode() {
    messageService.showTitle("Remove node");

    auto id = getIntInput("Enter node ID to remove: ");
    if (!withInput(id, [this](int nodeId) {
        network.removeNode(nodeId);
    })) {
        messageService.showCancelled();
    }
}

void NetworkController::handleRemoveEdge() {
    messageService.showTitle("Remove edge");

    if (network.getNodeCount() == 0) {
        messageService.showError("No nodes in network!");
        return;
    }

    auto nodePair = selectionService.selectNodePair(network, "SELECT SOURCE NODE", "SELECT DESTINATION NODE", true);
    if (nodePair.cancelled) {
        messageService.showCancelled();
        return;
    }

    system("cls");
    messageService.showTitle("Remove edge");

    std::cout << CYAN;
    std::cout << std::setw(6) << "ID" << " | "
              << std::setw(20) << "Name" << " | "
              << std::setw(15) << "Role" << "\n";
    std::cout << std::string(50, '-') << "\n";
    std::cout << std::setw(6) << nodePair.sourceId << " | "
              << std::setw(20) << network.getNodeName(nodePair.sourceId) << " | "
              << std::setw(15) << "Source" << "\n";
    std::cout << std::setw(6) << nodePair.destId << " | "
              << std::setw(20) << network.getNodeName(nodePair.destId) << " | "
              << std::setw(15) << "Destination" << "\n";
    std::cout << RESET << "\n";

    std::cout << "Confirm removal? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm == 'y' || confirm == 'Y') {
        network.removeEdge(nodePair.sourceId, nodePair.destId);
    } else {
        messageService.showCancelled();
    }
}

void NetworkController::handleGenerateSeed() {
    messageService.showTitle("Generate seed file");

    auto filename = getStringInput("Enter seed filename (without extension): ");
    if (!withInput(filename, [](const std::string& name) {
        fileService.generateNetworkSeed(name);
    })) {
        messageService.showCancelled();
    }
}
