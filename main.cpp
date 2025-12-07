#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "utils/colors.h"
#include "utils/inputUtils.h"
#include "utils/tableUtils.h"
#include "models/Graph.h"
#include "models/HashTable.h"
#include "Algorithms.h"
#include "views/MenuView.h"
#include "views/MenuItem.h"
#include "controllers/NetworkController.h"
#include "controllers/VehicleController.h"
#include "services/SelectionService.h"
#include "services/MessageService.h"
#include "services/FileService.h"
#include "services/UIService.h"

// Global instances
Graph cityNetwork;
HashTable vehicleRegistry;

// Controllers
NetworkController* networkController = nullptr;
VehicleController* vehicleController = nullptr;

// Services
SelectionService selectionService;
MessageService messageService;
FileService fileService;

// ===== NETWORK MANAGEMENT (using controllers) =====

void generateVehicleSeedFile() {
    messageService.showTitle("Generate vehicle seed file");
    fileService.generateVehicleSeed("vehicles");
}

// ===== NETWORK VISUALIZATION =====
void showAdjacencyList() {
    cityNetwork.showAdjacencyList();
}

void showAdjacencyMatrix() {
    cityNetwork.showAdjacencyMatrix();
}

// ===== QUERIES AND ALGORITHMS =====
void findShortestPath() {
    messageService.showTitle("Find shortest path");

    if (cityNetwork.getNodeCount() < 2) {
        messageService.showError("Need at least 2 nodes in the network!");
        return;
    }

    auto nodePair = selectionService.selectNodePair(cityNetwork, "SELECT SOURCE NODE", "SELECT DESTINATION NODE", false);
    if (nodePair.cancelled) {
        messageService.showCancelled();
        return;
    }

    PathResult result = dijkstra(cityNetwork, nodePair.sourceId, nodePair.destId, true);
    displayPath(cityNetwork, result);
}

void breadthFirstSearch() {
    messageService.showTitle("Breadth-first search");

    if (cityNetwork.getNodeCount() == 0) {
        messageService.showError("Network is empty!");
        return;
    }

    int startId = selectionService.selectNode(cityNetwork, "SELECT START NODE");
    if (startId == -1) {
        messageService.showCancelled();
        return;
    }

    TraversalResult result = bfs(cityNetwork, startId, true);
    displayTraversal(cityNetwork, result, "BREADTH-FIRST SEARCH");
}

void depthFirstSearch() {
    messageService.showTitle("Depth-first search");

    if (cityNetwork.getNodeCount() == 0) {
        messageService.showError("Network is empty!");
        return;
    }

    int startId = selectionService.selectNode(cityNetwork, "SELECT START NODE");
    if (startId == -1) {
        messageService.showCancelled();
        return;
    }

    TraversalResult result = dfs(cityNetwork, startId, true);
    displayTraversal(cityNetwork, result, "DEPTH-FIRST SEARCH");
}

// ===== VEHICLE MANAGEMENT =====
void loadVehicles() {
    messageService.showTitle("Load vehicles");

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [](const std::string& name) {
        fileService.loadVehicles(name, vehicleRegistry);
    })) {
        messageService.showCancelled();
    }
}

void saveVehicles() {
    messageService.showTitle("Save vehicles");

    if (vehicleRegistry.getVehicleCount() == 0) {
        messageService.showError("No vehicles to save!");
        return;
    }

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [](const std::string& name) {
        fileService.saveVehicles(name, vehicleRegistry);
    })) {
        messageService.showCancelled();
    }
}

void addVehicle() {
    messageService.showTitle("Add vehicle");

    if (cityNetwork.getNodeCount() == 0) {
        messageService.showError("No nodes in network! Add nodes first.");
        return;
    }

    std::string plate = getValidString("Enter vehicle plate: ");
    if (plate.empty()) {
        messageService.showCancelled();
        return;
    }

    std::string selectedType = selectionService.selectVehicleType();
    if (selectedType.empty()) {
        messageService.showCancelled();
        return;
    }

    int currentLocation = selectionService.selectNode(cityNetwork, "SELECT CURRENT LOCATION");
    if (currentLocation == -1) {
        messageService.showCancelled();
        return;
    }

    vehicleRegistry.addVehicleAuto(plate, selectedType, currentLocation, -1);
}

void searchVehicle() {
    messageService.showTitle("Search vehicle");

    auto id = getIntInput("Enter vehicle ID to search: ");
    if (!withInput(id, [](int vehicleId) {
        Vehicle* vehicle = vehicleRegistry.searchVehicle(vehicleId);
        if (vehicle != nullptr) {
            std::cout << "\nVehicle found!\n";
            std::cout << "ID: " << vehicle->id << "\n";
            std::cout << "Plate: " << vehicle->plate << "\n";
            std::cout << "Type: " << vehicle->type << "\n";
            std::cout << "Current Node: " << vehicle->currentNodeId << "\n";
            std::cout << "Destination Node: " << vehicle->destinationNodeId << "\n";
        } else {
            messageService.showError("Vehicle not found!");
        }
    })) {
        messageService.showCancelled();
    }
}

void removeVehicle() {
    messageService.showTitle("Remove vehicle");

    auto id = getIntInput("Enter vehicle ID to remove: ");
    if (!withInput(id, [](int vehicleId) {
        vehicleRegistry.removeVehicle(vehicleId);
    })) {
        messageService.showCancelled();
    }
}

void showAllVehicles() {
    vehicleRegistry.showAllVehicles();
}

void showHashInfo() {
    vehicleRegistry.showHashInfo();
}

void moveVehicle() {
    messageService.showTitle("Move vehicle");

    if (vehicleRegistry.getVehicleCount() == 0) {
        messageService.showError("No vehicles registered!");
        return;
    }

    if (cityNetwork.getNodeCount() < 2) {
        messageService.showError("Need at least 2 nodes in network!");
        return;
    }

    int vehicleId = selectionService.selectVehicle(vehicleRegistry, cityNetwork, "SELECT VEHICLE TO MOVE");
    if (vehicleId == -1) {
        messageService.showCancelled();
        return;
    }

    Vehicle* vehicle = vehicleRegistry.searchVehicle(vehicleId);
    if (vehicle == nullptr) {
        messageService.showError("Vehicle not found!");
        return;
    }

    int destId = selectionService.selectNode(cityNetwork, "SELECT DESTINATION");
    if (destId == -1) {
        messageService.showCancelled();
        return;
    }

    if (vehicle->currentNodeId == destId) {
        system("cls");
        messageService.showError("Vehicle is already at destination!");
        return;
    }

    PathResult result = dijkstra(cityNetwork, vehicle->currentNodeId, destId, true);

    if (result.found) {
        vehicle->currentNodeId = destId;
        vehicle->destinationNodeId = destId;
        vehicleRegistry.logMovement(vehicleId, destId, "success", result.travelTimeMinutes, "");

        displayPath(cityNetwork, result);
        messageService.showSuccess("\nVehicle moved successfully!");
        std::cout << "New location: [" << destId << "] " << cityNetwork.getNodeName(destId) << "\n";
    } else {
        vehicleRegistry.logMovement(vehicleId, destId, "failed", 0.0, "No path found");
        displayPath(cityNetwork, result);
        std::cout << "\nMovement failed: No path found!\n";
    }
}

void showMovementHistory() {
    vehicleRegistry.showMovementHistory();
}

// ===== EXIT =====
void exitAction() {
    std::cout << "Exiting application...\n";
    exit(0);
}

int main() {
    // Initialize controllers
    networkController = new NetworkController(cityNetwork);
    vehicleController = new VehicleController(vehicleRegistry, cityNetwork);

    // 1. Road Network Management submenu
    auto roadNetworkMenu = std::make_shared<MenuView>("Network Management");
    roadNetworkMenu->addItem(1, MenuItem("Load Network", []() { networkController->handleLoadNetwork(); }));
    roadNetworkMenu->addItem(2, MenuItem("Save Network", []() { networkController->handleSaveNetwork(); }));
    roadNetworkMenu->addItem(3, MenuItem("Add Node", []() { networkController->handleAddNode(); }));
    roadNetworkMenu->addItem(4, MenuItem("Add Edge", []() { networkController->handleAddEdge(); }));
    roadNetworkMenu->addItem(5, MenuItem("Remove Node", []() { networkController->handleRemoveNode(); }));
    roadNetworkMenu->addItem(6, MenuItem("Remove Edge", []() { networkController->handleRemoveEdge(); }));
    roadNetworkMenu->addItem(7, MenuItem("Generate Seed File", []() { networkController->handleGenerateSeed(); }));

    // 2. Queries and Algorithms submenu (kept for manual testing)
    auto algorithmsMenu = std::make_shared<MenuView>("Network Analysis (Manual)");
    algorithmsMenu->addItem(1, MenuItem("Find Shortest Path", findShortestPath));
    algorithmsMenu->addItem(2, MenuItem("Breadth-First Search", breadthFirstSearch));
    algorithmsMenu->addItem(3, MenuItem("Depth-First Search", depthFirstSearch));

    // 3. Network Visualization submenu
    auto visualizationMenu = std::make_shared<MenuView>("Network Visualization");
    visualizationMenu->addItem(1, MenuItem("Show Adjacency List", showAdjacencyList));
    visualizationMenu->addItem(2, MenuItem("Show Adjacency Matrix", showAdjacencyMatrix));

    // 4. Vehicle Management submenu
    auto vehicleMenu = std::make_shared<MenuView>("Vehicle Management");
    vehicleMenu->addItem(1, MenuItem("Load Vehicles", []() { vehicleController->handleLoadVehicles(); }));
    vehicleMenu->addItem(2, MenuItem("Save Vehicles", []() { vehicleController->handleSaveVehicles(); }));
    vehicleMenu->addItem(3, MenuItem("Add Vehicle", []() { vehicleController->handleAddVehicle(); }));
    vehicleMenu->addItem(4, MenuItem("Move Vehicle (Uses Dijkstra)", []() { vehicleController->handleMoveVehicle(); }));
    vehicleMenu->addItem(5, MenuItem("Search Vehicle", []() { vehicleController->handleSearchVehicle(); }));
    vehicleMenu->addItem(6, MenuItem("Remove Vehicle", []() { vehicleController->handleRemoveVehicle(); }));
    vehicleMenu->addItem(7, MenuItem("Show All Vehicles", []() { vehicleController->handleShowAll(); }));
    vehicleMenu->addItem(8, MenuItem("Show Movement History", []() { vehicleController->handleShowMovementHistory(); }));
    vehicleMenu->addItem(9, MenuItem("Show Hash Info", []() { vehicleController->handleShowHashInfo(); }));
    vehicleMenu->addItem(10, MenuItem("Generate Vehicle Seed File", generateVehicleSeedFile));

    // Main menu
    MenuView mainMenu("Main menu");
    mainMenu.addItem(1, MenuItem("Network Management", roadNetworkMenu));
    mainMenu.addItem(2, MenuItem("Vehicle Management", vehicleMenu));
    mainMenu.addItem(3, MenuItem("Network Visualization", visualizationMenu));
    mainMenu.addItem(4, MenuItem("Network Analysis (Manual)", algorithmsMenu));
    mainMenu.addItem(5, MenuItem("Exit", exitAction));

    mainMenu.run();

    return 0;
}
