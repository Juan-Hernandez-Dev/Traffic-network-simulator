#ifndef BASEVIEW_H
#define BASEVIEW_H

#include <iostream>
#include <string>
#include <conio.h>
#include "utils/colors.h"

class BaseView {
protected:
    void showTitle(const std::string& title) {
        std::cout << BOLD << title << RESET << "\n";
    }

    void showMessage(const std::string& message) {
        std::cout << message << "\n";
    }

    void showSuccess(const std::string& message) {
        std::cout << GREEN << "✓ " << message << RESET << "\n";
    }

    void showError(const std::string& message) {
        std::cout << "✗ Error: " << message << "\n";
    }

    void showWarning(const std::string& message) {
        std::cout << YELLOW << "⚠ " << message << RESET << "\n";
    }

    void showInfo(const std::string& message) {
        std::cout << CYAN << "ℹ " << message << RESET << "\n";
    }

    void waitForKey() {
        std::cout << "\nPress any key to continue...";
        _getch();
    }

public:
    virtual ~BaseView() = default;
};

#endif
