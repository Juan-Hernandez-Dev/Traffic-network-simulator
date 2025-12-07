#include "MenuView.h"

MenuView::MenuView(const std::string& t) : title(t), selectedIndex(0) {}

void MenuView::display() {
    system("cls");
    std::cout << BOLD << title << RESET << "\n";

    int idx = 0;
    for (const auto& [key, item] : items) {
        if (idx == selectedIndex) {
            std::cout << CYAN << "> ";
        } else {
            std::cout << "  ";
        }
        std::cout << item.label << RESET << "\n";
        idx++;
    }
    std::cout << "[W/S or Arrow Keys] Navigate | [Enter] Select | [ESC] Back\n\n";
}

MenuItem& MenuView::getSelectedItem() {
    int idx = 0;
    for (auto& [key, item] : items) {
        if (idx == selectedIndex) {
            return item;
        }
        idx++;
    }
    return items.begin()->second;
}

void MenuView::addItem(int key, const MenuItem& item) {
    items[key] = item;
}

bool MenuView::run() {
    selectedIndex = 0;

    while (true) {
        display();

        int ch = _getch();

        if (ch == 224 || ch == 0) {
            ch = _getch();
            if (ch == 72 || ch == 'H') { // Up arrow
                selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
            } else if (ch == 80 || ch == 'P') { // Down arrow
                selectedIndex = (selectedIndex + 1) % items.size();
            }
        } else if (ch == 'w' || ch == 'W') {
            selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
        } else if (ch == 's' || ch == 'S') {
            selectedIndex = (selectedIndex + 1) % items.size();
        } else if (ch == 13) { // Enter
            MenuItem& selected = getSelectedItem();

            if (selected.submenu) {
                selected.submenu->run();
            } else if (selected.action) {
                system("cls");
                selected.action();
                std::cout << "\nPress any key to continue...";
                _getch();
            }
        } else if (ch == 27) { // ESC
            return false;
        }
    }

    return true;
}
