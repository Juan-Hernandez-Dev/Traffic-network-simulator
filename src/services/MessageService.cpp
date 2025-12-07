#include "MessageService.h"
#include "utils/colors.h"
#include <iostream>
#include <string>

MessageService::MessageService() {}

// EXTRACTED from BaseView and scattered throughout controllers
void MessageService::showError(const std::string& message) {
    std::cout << RED << "Error: " << message << RESET << "\n";
}

void MessageService::showSuccess(const std::string& message) {
    std::cout << GREEN << message << RESET << "\n";
}

void MessageService::showWarning(const std::string& message) {
    std::cout << YELLOW << "Warning: " << message << RESET << "\n";
}

void MessageService::showInfo(const std::string& message) {
    std::cout << CYAN << message << RESET << "\n";
}

void MessageService::showCancelled() {
    std::cout << YELLOW << "Operation cancelled." << RESET << "\n";
}

// EXTRACTED: Title display
void MessageService::showTitle(const std::string& title) {
    std::cout << BOLD << title << RESET << "\n";
}

void MessageService::showSectionHeader(const std::string& header) {
    std::cout << "\n" << BOLD << CYAN << header << RESET << "\n";
    showDivider();
}

// EXTRACTED: Status messages
void MessageService::showLoading(const std::string& message) {
    std::cout << CYAN << "Loading " << message << "..." << RESET << "\n";
}

void MessageService::showSaving(const std::string& message) {
    std::cout << CYAN << "Saving " << message << "..." << RESET << "\n";
}

void MessageService::showProcessing(const std::string& message) {
    std::cout << CYAN << "Processing " << message << "..." << RESET << "\n";
}

// EXTRACTED: Result messages
void MessageService::showOperationResult(bool success, const std::string& successMsg, const std::string& errorMsg) {
    if (success) {
        showSuccess(successMsg);
    } else {
        showError(errorMsg);
    }
}

// EXTRACTED: Dividers
void MessageService::showDivider(int length) {
    std::cout << std::string(length, '-') << "\n";
}

void MessageService::showDoubleDivider(int length) {
    std::cout << std::string(length, '=') << "\n";
}
