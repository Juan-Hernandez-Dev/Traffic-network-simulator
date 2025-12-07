#include "FileService.h"
#include "utils/colors.h"
#include <fstream>
#include <iostream>
#include <algorithm>

FileService::FileService() {}

// EXTRACTED from utils/fileUtils.h
std::string FileService::sanitizeFilename(const std::string& input) {
    std::string filename = input;

    // Remove leading/trailing whitespace
    size_t start = filename.find_first_not_of(" \t\n\r");
    size_t end = filename.find_last_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    filename = filename.substr(start, end - start + 1);

    // Remove any directory traversal patterns
    size_t pos;
    while ((pos = filename.find("..")) != std::string::npos) {
        filename.erase(pos, 2);
    }

    // Remove path separators
    while ((pos = filename.find("/")) != std::string::npos) {
        filename.erase(pos, 1);
    }
    while ((pos = filename.find("\\")) != std::string::npos) {
        filename.erase(pos, 1);
    }

    // Remove any existing extension
    pos = filename.find_last_of('.');
    if (pos != std::string::npos) {
        filename = filename.substr(0, pos);
    }

    // Remove dangerous characters
    filename.erase(std::remove_if(filename.begin(), filename.end(),
        [](char c) { return c == ':' || c == '*' || c == '?' || c == '"' ||
                     c == '<' || c == '>' || c == '|'; }), filename.end());

    return filename;
}

std::string FileService::getDataPath(const std::string& filename) {
    return "data/" + sanitizeFilename(filename) + ".csv";
}

std::string FileService::getSeedPath(const std::string& filename) {
    return "seeds/" + sanitizeFilename(filename) + ".csv";
}

// EXTRACTED from Graph::loadFromFile
bool FileService::loadNetwork(const std::string& filename, Graph& network) {
    std::string fullPath = getDataPath(filename);
    std::cout << "Loading from: " << fullPath << "\n\n";
    return network.loadFromFile(fullPath);
}

// EXTRACTED from Graph::saveToFile
bool FileService::saveNetwork(const std::string& filename, Graph& network) {
    std::string fullPath = getDataPath(filename);
    std::cout << "Saving to: " << fullPath << "\n\n";
    return network.saveToFile(fullPath);
}

// EXTRACTED from HashTable::loadFromFile
bool FileService::loadVehicles(const std::string& filename, HashTable& registry) {
    std::string fullPath = getDataPath(filename);
    std::cout << "Loading from: " << fullPath << "\n\n";
    return registry.loadFromFile(fullPath);
}

// EXTRACTED from HashTable::saveToFile
bool FileService::saveVehicles(const std::string& filename, HashTable& registry) {
    std::string fullPath = getDataPath(filename);
    std::cout << "Saving to: " << fullPath << "\n\n";
    return registry.saveToFile(fullPath);
}

// EXTRACTED from NetworkController::handleGenerateSeed
bool FileService::generateNetworkSeed(const std::string& filename) {
    std::string sanitized = sanitizeFilename(filename);
    if (sanitized.empty()) {
        std::cout << RED << "Error: Invalid filename!" << RESET << "\n";
        return false;
    }

    std::string fullPath = getSeedPath(sanitized);
    std::cout << "Generating seed file: " << fullPath << "\n\n";

    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::cout << RED << "Error: Could not create seed file!" << RESET << "\n";
        return false;
    }

    file << "# SAMPLE NETWORK - Aguascalientes City\n";
    file << "# NODES\n";
    file << "N;0;UAA\n";
    file << "N;1;Plaza_Patria\n";
    file << "N;2;Centro_Historico\n";
    file << "N;3;Glorieta_Norte\n";
    file << "N;4;Estadio_Victoria\n";
    file << "N;5;Expo_Plaza\n";
    file << "\n# EDGES (source;destination;weight)\n";
    file << "E;0;1;3.5\n";
    file << "E;1;2;2.8\n";
    file << "E;0;2;6.2\n";
    file << "E;2;3;4.1\n";
    file << "E;1;3;5.0\n";
    file << "E;3;4;3.2\n";
    file << "E;4;0;7.5\n";
    file << "E;1;5;2.1\n";
    file << "E;5;3;3.9\n";

    file.close();
    std::cout << GREEN << "Seed file generated successfully!" << RESET << "\n";
    std::cout << "You can now load it using 'Load Network' option.\n";
    return true;
}

// EXTRACTED: Vehicle seed generation
bool FileService::generateVehicleSeed(const std::string& filename) {
    std::string sanitized = sanitizeFilename(filename);
    if (sanitized.empty()) {
        std::cout << RED << "Error: Invalid filename!" << RESET << "\n";
        return false;
    }

    std::string fullPath = getSeedPath(sanitized);
    std::cout << "Generating vehicle seed file: " << fullPath << "\n\n";

    std::ofstream file(fullPath);
    if (!file.is_open()) {
        std::cout << RED << "Error: Could not create seed file!" << RESET << "\n";
        return false;
    }

    file << "# SAMPLE VEHICLES\n";
    file << "# VEHICLES (id;plate;type;currentNode;destinationNode)\n";
    file << "V;0;ABC-123;Sedan;0;-1\n";
    file << "V;1;XYZ-789;Truck;1;-1\n";
    file << "V;2;DEF-456;Compact;2;-1\n";

    file.close();
    std::cout << GREEN << "Vehicle seed file generated successfully!" << RESET << "\n";
    return true;
}

// File validation
bool FileService::fileExists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

bool FileService::isValidFilename(const std::string& filename) {
    std::string sanitized = sanitizeFilename(filename);
    return !sanitized.empty();
}
