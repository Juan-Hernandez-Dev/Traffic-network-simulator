#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <string>
#include <map>
#include <iostream>
#include <conio.h>
#include "MenuItem.h"
#include "utils/colors.h"

class MenuView {
private:
    std::string title;
    std::map<int, MenuItem> items;
    int selectedIndex;

    void display();
    MenuItem& getSelectedItem();

public:
    MenuView(const std::string& t);
    void addItem(int key, const MenuItem& item);
    bool run();
};

#endif
