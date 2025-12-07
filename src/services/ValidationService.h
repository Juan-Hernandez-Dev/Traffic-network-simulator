#ifndef VALIDATIONSERVICE_H
#define VALIDATIONSERVICE_H

#include <string>

// Reusable validation service
class ValidationService {
public:
    ValidationService();

    // EXTRACTED: Input validation
    bool validateNodeName(const std::string& name);
    bool validateWeight(double weight);
    bool validatePlate(const std::string& plate);
    bool validateFilename(const std::string& filename);

    // Range validation
    bool validateIntRange(int value, int min, int max);
    bool validateDoubleRange(double value, double min, double max);

    // String validation
    bool isEmptyOrWhitespace(const std::string& str);
    bool containsInvalidChars(const std::string& str, const std::string& invalidChars);

    // Get last error message
    std::string getLastError() const;

private:
    std::string lastError;
    void setError(const std::string& error);
};

#endif
