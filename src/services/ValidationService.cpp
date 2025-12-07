#include "ValidationService.h"
#include <algorithm>

ValidationService::ValidationService() : lastError("") {}

void ValidationService::setError(const std::string& error) {
    lastError = error;
}

std::string ValidationService::getLastError() const {
    return lastError;
}

// EXTRACTED: Node name validation
bool ValidationService::validateNodeName(const std::string& name) {
    if (isEmptyOrWhitespace(name)) {
        setError("Node name cannot be empty");
        return false;
    }

    if (name.length() > 50) {
        setError("Node name too long (max 50 characters)");
        return false;
    }

    if (containsInvalidChars(name, ";\n\r")) {
        setError("Node name contains invalid characters");
        return false;
    }

    return true;
}

// EXTRACTED: Weight validation
bool ValidationService::validateWeight(double weight) {
    if (weight <= 0) {
        setError("Weight must be positive");
        return false;
    }

    if (weight > 10000) {
        setError("Weight too large (max 10000)");
        return false;
    }

    return true;
}

// EXTRACTED: Plate validation
bool ValidationService::validatePlate(const std::string& plate) {
    if (isEmptyOrWhitespace(plate)) {
        setError("Plate cannot be empty");
        return false;
    }

    if (plate.length() > 15) {
        setError("Plate too long (max 15 characters)");
        return false;
    }

    if (containsInvalidChars(plate, ";\n\r")) {
        setError("Plate contains invalid characters");
        return false;
    }

    return true;
}

// EXTRACTED: Filename validation
bool ValidationService::validateFilename(const std::string& filename) {
    if (isEmptyOrWhitespace(filename)) {
        setError("Filename cannot be empty");
        return false;
    }

    if (filename.length() > 100) {
        setError("Filename too long");
        return false;
    }

    if (containsInvalidChars(filename, "<>:\"/|?*")) {
        setError("Filename contains invalid characters");
        return false;
    }

    return true;
}

// Range validation
bool ValidationService::validateIntRange(int value, int min, int max) {
    if (value < min || value > max) {
        setError("Value must be between " + std::to_string(min) + " and " + std::to_string(max));
        return false;
    }
    return true;
}

bool ValidationService::validateDoubleRange(double value, double min, double max) {
    if (value < min || value > max) {
        setError("Value must be between " + std::to_string(min) + " and " + std::to_string(max));
        return false;
    }
    return true;
}

// String utilities
bool ValidationService::isEmptyOrWhitespace(const std::string& str) {
    return str.empty() || std::all_of(str.begin(), str.end(), ::isspace);
}

bool ValidationService::containsInvalidChars(const std::string& str, const std::string& invalidChars) {
    return str.find_first_of(invalidChars) != std::string::npos;
}
