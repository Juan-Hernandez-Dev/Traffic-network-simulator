#ifndef MESSAGESERVICE_H
#define MESSAGESERVICE_H

#include <string>

// Reusable message service - extracts ALL message display patterns
class MessageService {
public:
    MessageService();

    // EXTRACTED: Standard messages (used everywhere!)
    void showError(const std::string& message);
    void showSuccess(const std::string& message);
    void showWarning(const std::string& message);
    void showInfo(const std::string& message);
    void showCancelled();

    // EXTRACTED: Title display
    void showTitle(const std::string& title);
    void showSectionHeader(const std::string& header);

    // EXTRACTED: Status messages
    void showLoading(const std::string& message);
    void showSaving(const std::string& message);
    void showProcessing(const std::string& message);

    // EXTRACTED: Result messages
    void showOperationResult(bool success, const std::string& successMsg, const std::string& errorMsg);

    // EXTRACTED: Dividers and separators
    void showDivider(int length = 60);
    void showDoubleDivider(int length = 60);
};

#endif
