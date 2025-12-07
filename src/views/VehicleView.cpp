#include "VehicleView.h"
#include <iomanip>
#include <fstream>
#include <sstream>

VehicleView::VehicleView() {}

void VehicleView::showAllVehicles(const HashTable& registry) {
    if (registry.getVehicleCount() == 0) {
        showError("No vehicles registered!");
        return;
    }

    showTitle("Registered vehicles");
    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(12) << "Plate" << " | "
              << std::setw(15) << "Type" << " | "
              << std::setw(8) << "Origin" << " | "
              << std::setw(8) << "Dest" << "\n";
    std::cout << std::string(65, '-') << "\n";

    const Vehicle* vehicles = registry.getVehicles();
    for (int i = 0; i < registry.getHashSize(); i++) {
        if (vehicles[i].active) {
            std::cout << std::setw(5) << vehicles[i].id << " | "
                      << std::setw(12) << vehicles[i].plate << " | "
                      << std::setw(15) << vehicles[i].type << " | "
                      << std::setw(8) << vehicles[i].currentNodeId << " | "
                      << std::setw(8) << vehicles[i].destinationNodeId << "\n";
        }
    }
    std::cout << "\n";
}

void VehicleView::showHashInfo(const HashTable& registry) {
    showTitle("Hash table statistics");

    const Vehicle* vehicles = registry.getVehicles();
    int vehicleCount = registry.getVehicleCount();
    int hashSize = registry.getHashSize();

    // Calculate statistics
    int usedSlots = 0;
    for (int i = 0; i < hashSize; i++) {
        if (vehicles[i].active || vehicles[i].id != -1) {
            usedSlots++;
        }
    }
    double loadFactor = (double)vehicleCount / hashSize;
    int availableCapacity = hashSize - vehicleCount;
    double usagePercent = (double)vehicleCount / hashSize * 100;
    int collisions = usedSlots - vehicleCount;

    // Main statistics table
    std::cout << std::setw(25) << "Metric" << " | "
              << std::setw(15) << "Value" << " | "
              << std::setw(30) << "Status" << "\n";
    std::cout << std::string(75, '-') << "\n";

    // Vehicles stored
    std::cout << std::setw(25) << "Vehicles registered" << " | "
              << std::setw(15) << vehicleCount << " | ";
    if (vehicleCount == 0) {
        std::cout << std::setw(30) << "Empty registry";
    } else if (vehicleCount < 50) {
        std::cout << std::setw(30) << "Light usage";
    } else if (vehicleCount < 70) {
        std::cout << std::setw(30) << "Moderate usage";
    } else {
        std::cout << std::setw(30) << "Heavy usage";
    }
    std::cout << "\n";

    // Storage capacity
    std::cout << std::setw(25) << "Storage capacity" << " | "
              << std::setw(15) << hashSize << " | "
              << std::setw(30) << "Maximum slots" << "\n";

    // Available space
    std::cout << std::setw(25) << "Available space" << " | "
              << std::setw(15) << availableCapacity << " | "
              << std::setw(30) << "Slots remaining" << "\n";

    // Usage percentage
    std::cout << std::setw(25) << "Usage percentage" << " | "
              << std::setw(14) << std::fixed << std::setprecision(1) << usagePercent << "%" << " | ";
    if (usagePercent < 50) {
        std::cout << std::setw(30) << "Plenty of room";
    } else if (usagePercent < 70) {
        std::cout << std::setw(30) << "Getting busy";
    } else if (usagePercent < 90) {
        std::cout << std::setw(30) << "Consider archiving";
    } else {
        std::cout << std::setw(30) << "Nearly full";
    }
    std::cout << "\n";

    // Load factor
    std::cout << std::setw(25) << "Load factor" << " | "
              << std::setw(15) << std::fixed << std::setprecision(3) << loadFactor << " | ";
    if (loadFactor < 0.5) {
        std::cout << GREEN << std::setw(30) << "Excellent performance" << RESET;
    } else if (loadFactor < 0.7) {
        std::cout << GREEN << std::setw(30) << "Good performance" << RESET;
    } else if (loadFactor < 0.9) {
        std::cout << YELLOW << std::setw(30) << "Fair performance" << RESET;
    } else {
        std::cout << YELLOW << std::setw(30) << "Performance degrading" << RESET;
    }
    std::cout << "\n";

    // Occupied slots
    std::cout << std::setw(25) << "Occupied slots" << " | "
              << std::setw(15) << (std::to_string(usedSlots) + " / " + std::to_string(hashSize)) << " | "
              << std::setw(30) << "Actual positions used" << "\n";

    // Collisions
    std::cout << std::setw(25) << "Collisions handled" << " | "
              << std::setw(15) << collisions << " | ";
    if (collisions == 0) {
        std::cout << GREEN << std::setw(30) << "Perfect hashing" << RESET;
    } else if (collisions < 5) {
        std::cout << std::setw(30) << "Minimal collisions";
    } else if (collisions < 10) {
        std::cout << std::setw(30) << "Some collisions";
    } else {
        std::cout << YELLOW << std::setw(30) << "Many collisions" << RESET;
    }
    std::cout << "\n";

    std::cout << "\n";
}

void VehicleView::showMovementHistory() {
    std::ifstream file("data/.movements.csv");
    if (!file.is_open()) {
        showError("No movement history found.");
        return;
    }

    showTitle("Movement history");
    std::cout << std::setw(10) << "Vehicle ID" << " | "
              << std::setw(12) << "Destination" << " | "
              << std::setw(10) << "Status" << " | "
              << std::setw(12) << "Time (min)" << " | "
              << "Reason\n";
    std::cout << std::string(70, '-') << "\n";

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string vidStr, destStr, status, timeStr, reason;

        std::getline(ss, vidStr, ';');
        std::getline(ss, destStr, ';');
        std::getline(ss, status, ';');
        std::getline(ss, timeStr, ';');
        std::getline(ss, reason);

        std::cout << std::setw(10) << vidStr << " | "
                  << std::setw(12) << destStr << " | "
                  << std::setw(10) << status << " | "
                  << std::setw(12) << timeStr << " | "
                  << reason << "\n";
    }

    file.close();
    std::cout << "\n";
}

void VehicleView::showVehicleDetails(const Vehicle& vehicle) {
    std::cout << "Vehicle ID: " << vehicle.id << "\n";
    std::cout << "Plate: " << vehicle.plate << "\n";
    std::cout << "Type: " << vehicle.type << "\n";
    std::cout << "Current Node: " << vehicle.currentNodeId << "\n";
    std::cout << "Destination: " << vehicle.destinationNodeId << "\n";
}
