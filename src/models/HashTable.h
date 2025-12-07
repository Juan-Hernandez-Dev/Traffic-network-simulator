#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <fstream>
#include <iostream>
#include "Vehicle.h"

const int HASH_SIZE = 101;  // Prime number for better distribution

class HashTable {
private:
    Vehicle table[HASH_SIZE];
    int vehicleCount;
    int nextId;
    std::string currentFile;

    int hashFunction(int id);
    int findSlot(int id);  // Linear probing
    void autoSave();
    void updateNextId();

public:
    HashTable();
    ~HashTable();

    // CRUD Operations
    bool addVehicle(int id, const std::string& plate, const std::string& type, int origin, int dest);
    bool addVehicleAuto(const std::string& plate, const std::string& type, int origin, int dest);
    bool removeVehicle(int id);
    Vehicle* searchVehicle(int id);

    // File I/O
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    void clearTable();

    // Display
    void showAllVehicles();
    void showHashInfo();

    // Movement tracking
    void logMovement(int vehicleId, int destNodeId, const std::string& status,
                    double travelTime, const std::string& failReason = "");
    void showMovementHistory();

    // Getters
    int getVehicleCount() const { return vehicleCount; }
    int getNextId() const { return nextId; }
    std::string getCurrentFile() const { return currentFile; }
    const Vehicle* getVehicles() const { return table; }
    int getHashSize() const { return HASH_SIZE; }
};

#endif
