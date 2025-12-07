#include "VehicleController.h"
#include "utils/inputUtils.h"
#include "utils/colors.h"
#include "services/SelectionService.h"
#include "services/MessageService.h"
#include "services/FileService.h"
#include "Algorithms.h"
#include <conio.h>

VehicleController::VehicleController(HashTable& reg, Graph& net)
    : registry(reg), network(net) {}

// Services
static SelectionService selectionService;
static MessageService messageService;
static FileService fileService;

void VehicleController::handleLoadVehicles() {
    messageService.showTitle("Load vehicles");

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [this](const std::string& name) {
        fileService.loadVehicles(name, registry);
    })) {
        messageService.showCancelled();
    }
}

void VehicleController::handleSaveVehicles() {
    messageService.showTitle("Save vehicles");

    if (registry.getVehicleCount() == 0) {
        messageService.showError("No vehicles to save!");
        return;
    }

    auto filename = getStringInput("Enter filename (without extension): ");
    if (!withInput(filename, [this](const std::string& name) {
        fileService.saveVehicles(name, registry);
    })) {
        messageService.showCancelled();
    }
}

void VehicleController::handleAddVehicle() {
    messageService.showTitle("Add vehicle");

    if (network.getNodeCount() == 0) {
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

    int currentLocation = selectionService.selectNode(network, "SELECT CURRENT LOCATION");
    if (currentLocation == -1) {
        messageService.showCancelled();
        return;
    }

    registry.addVehicleAuto(plate, selectedType, currentLocation, -1);
}

void VehicleController::handleSearchVehicle() {
    messageService.showTitle("Search vehicle");

    auto id = getIntInput("Enter vehicle ID to search: ");
    if (!withInput(id, [this](int vehicleId) {
        Vehicle* vehicle = registry.searchVehicle(vehicleId);
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

void VehicleController::handleRemoveVehicle() {
    messageService.showTitle("Remove vehicle");

    auto id = getIntInput("Enter vehicle ID to remove: ");
    if (!withInput(id, [this](int vehicleId) {
        registry.removeVehicle(vehicleId);
    })) {
        messageService.showCancelled();
    }
}

void VehicleController::handleShowAll() {
    registry.showAllVehicles();
}

void VehicleController::handleShowHashInfo() {
    registry.showHashInfo();
}

void VehicleController::handleMoveVehicle() {
    messageService.showTitle("Move vehicle");

    if (registry.getVehicleCount() == 0) {
        messageService.showError("No vehicles registered!");
        return;
    }

    if (network.getNodeCount() < 2) {
        messageService.showError("Need at least 2 nodes in network!");
        return;
    }

    int vehicleId = selectionService.selectVehicle(registry, network, "SELECT VEHICLE TO MOVE");
    if (vehicleId == -1) {
        messageService.showCancelled();
        return;
    }

    Vehicle* vehicle = registry.searchVehicle(vehicleId);
    if (vehicle == nullptr) {
        messageService.showError("Vehicle not found!");
        return;
    }

    int destId = selectionService.selectNode(network, "SELECT DESTINATION");
    if (destId == -1) {
        messageService.showCancelled();
        return;
    }

    if (vehicle->currentNodeId == destId) {
        system("cls");
        messageService.showError("Vehicle is already at destination!");
        return;
    }

    PathResult result = dijkstra(network, vehicle->currentNodeId, destId, true);

    if (result.found) {
        vehicle->currentNodeId = destId;
        vehicle->destinationNodeId = destId;
        registry.logMovement(vehicleId, destId, "success", result.travelTimeMinutes, "");

        displayPath(network, result);
        messageService.showSuccess("\nVehicle moved successfully!");
        std::cout << "New location: [" << destId << "] " << network.getNodeName(destId) << "\n";
    } else {
        registry.logMovement(vehicleId, destId, "failed", 0.0, "No path found");
        displayPath(network, result);
        std::cout << "\nMovement failed: No path found!\n";
    }
}

void VehicleController::handleShowMovementHistory() {
    registry.showMovementHistory();
}
