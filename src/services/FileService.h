#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <string>
#include "models/Graph.h"
#include "models/HashTable.h"

// Reusable file service - extracts ALL file operations
class FileService {
public:
    FileService();

    // EXTRACTED: Network file operations
    bool loadNetwork(const std::string& filename, Graph& network);
    bool saveNetwork(const std::string& filename, Graph& network);

    // EXTRACTED: Vehicle file operations
    bool loadVehicles(const std::string& filename, HashTable& registry);
    bool saveVehicles(const std::string& filename, HashTable& registry);

    // EXTRACTED: Seed generation
    bool generateNetworkSeed(const std::string& filename);
    bool generateVehicleSeed(const std::string& filename);

    // EXTRACTED: Path utilities
    std::string sanitizeFilename(const std::string& filename);
    std::string getDataPath(const std::string& filename);
    std::string getSeedPath(const std::string& filename);

    // File validation
    bool fileExists(const std::string& path);
    bool isValidFilename(const std::string& filename);
};

#endif
