#ifndef UISERVICE_H
#define UISERVICE_H

#include <string>
#include <vector>
#include <functional>

// Reusable UI service for all interactive components
class UIService {
public:
    UIService();

    // EXTRACTED: Generic selector (used for direction, type, etc.)
    int showSelector(const std::string& title,
                    const std::vector<std::string>& options,
                    const std::string& subtitle = "");

    // EXTRACTED: Confirmation dialog
    bool showConfirmation(const std::string& message);

    // EXTRACTED: Yes/No prompt
    bool askYesNo(const std::string& question);

    // EXTRACTED: Display info table (2 columns)
    void showInfoTable(const std::string& title,
                      const std::vector<std::pair<std::string, std::string>>& data);

    // EXTRACTED: Display comparison table (for edge direction, etc.)
    void showComparisonTable(const std::string& title,
                            const std::vector<std::string>& headers,
                            const std::vector<std::vector<std::string>>& rows);

    // EXTRACTED: Progress indicator
    void showProgress(const std::string& message, int current, int total);

    // EXTRACTED: Wait for key press
    void waitForKey(const std::string& message = "Press any key to continue...");
};

#endif
