#include "UIService.h"
#include "utils/colors.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

UIService::UIService() {}

// EXTRACTED from NetworkController and VehicleController
int UIService::showSelector(const std::string& title,
                            const std::vector<std::string>& options,
                            const std::string& subtitle) {
    if (options.empty()) return -1;

    int choice = 0;

    while (true) {
        system("cls");
        std::cout << BOLD << title << RESET << "\n";

        if (!subtitle.empty()) {
            std::cout << subtitle << "\n\n";
        }

        for (size_t i = 0; i < options.size(); i++) {
            if (i == static_cast<size_t>(choice)) {
                std::cout << CYAN << "> " << options[i] << RESET << "\n";
            } else {
                std::cout << "  " << options[i] << "\n";
            }
        }

        std::cout << "\n[W/S or Up/Down] Navigate | [Enter] Confirm | [ESC] Cancel\n";

        int ch = _getch();

        if (ch == 224 || ch == 0) {
            ch = _getch();
            if (ch == 72 || ch == 'H') { // Up
                choice = (choice - 1 + options.size()) % options.size();
            } else if (ch == 80 || ch == 'P') { // Down
                choice = (choice + 1) % options.size();
            }
        } else if (ch == 'w' || ch == 'W') {
            choice = (choice - 1 + options.size()) % options.size();
        } else if (ch == 's' || ch == 'S') {
            choice = (choice + 1) % options.size();
        } else if (ch == 13) { // Enter
            return choice;
        } else if (ch == 27) { // ESC
            return -1;
        }
    }
}

// EXTRACTED from multiple controllers
bool UIService::showConfirmation(const std::string& message) {
    std::cout << "\n" << message << "\n";
    std::cout << "Confirm? (y/n): ";

    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    return (confirm == 'y' || confirm == 'Y');
}

// EXTRACTED from multiple locations
bool UIService::askYesNo(const std::string& question) {
    std::cout << question << " (y/n): ";

    char response;
    std::cin >> response;
    std::cin.ignore();

    return (response == 'y' || response == 'Y');
}

// EXTRACTED table display pattern
void UIService::showInfoTable(const std::string& title,
                              const std::vector<std::pair<std::string, std::string>>& data) {
    system("cls");
    std::cout << BOLD << title << RESET << "\n\n";

    std::cout << CYAN;
    std::cout << std::setw(25) << "Field" << " | " << "Value" << "\n";
    std::cout << std::string(60, '-') << "\n";
    std::cout << RESET;

    for (const auto& row : data) {
        std::cout << std::setw(25) << row.first << " | " << row.second << "\n";
    }

    std::cout << "\n";
}

// EXTRACTED comparison table (used in edge direction selection)
void UIService::showComparisonTable(const std::string& title,
                                   const std::vector<std::string>& headers,
                                   const std::vector<std::vector<std::string>>& rows) {
    system("cls");
    std::cout << BOLD << title << RESET << "\n\n";

    std::cout << CYAN;

    // Headers
    for (const auto& header : headers) {
        std::cout << std::setw(20) << header << " | ";
    }
    std::cout << "\n";
    std::cout << std::string(headers.size() * 23, '-') << "\n";
    std::cout << RESET;

    // Rows
    for (const auto& row : rows) {
        for (const auto& cell : row) {
            std::cout << std::setw(20) << cell << " | ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

// EXTRACTED progress display
void UIService::showProgress(const std::string& message, int current, int total) {
    std::cout << "\r" << message << " [" << current << "/" << total << "]";
    std::cout.flush();
}

// EXTRACTED wait for key
void UIService::waitForKey(const std::string& message) {
    std::cout << message;
    _getch();
}
