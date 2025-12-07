#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <functional>
#include <memory>

class MenuView;

struct MenuItem {
    std::string label;
    std::function<void()> action;
    std::shared_ptr<MenuView> submenu;

    MenuItem() : label(""), action(nullptr), submenu(nullptr) {}

    MenuItem(const std::string& lbl, std::function<void()> act = nullptr)
        : label(lbl), action(act), submenu(nullptr) {}

    MenuItem(const std::string& lbl, std::shared_ptr<MenuView> sub)
        : label(lbl), action(nullptr), submenu(sub) {}
};

#endif
