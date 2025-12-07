#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include <string>
#include <iostream>

class BaseController {
protected:
    void showSuccess(const std::string& message) {
        std::cout << "✓ " << message << "\n";
    }

    void showError(const std::string& message) {
        std::cout << "✗ Error: " << message << "\n";
    }

    void showInfo(const std::string& message) {
        std::cout << "ℹ " << message << "\n";
    }

    void showCancelled() {
        std::cout << "Operation cancelled.\n";
    }

public:
    virtual ~BaseController() = default;
};

#endif
