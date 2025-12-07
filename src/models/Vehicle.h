#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    int id;
    std::string plate;
    std::string type;
    int currentNodeId;
    int destinationNodeId;
    bool active;

    Vehicle() : id(-1), plate(""), type(""), currentNodeId(-1), destinationNodeId(-1), active(false) {}
    Vehicle(int i, const std::string& p, const std::string& t, int curr, int dest)
        : id(i), plate(p), type(t), currentNodeId(curr), destinationNodeId(dest), active(true) {}
};

struct Movement {
    int vehicleId;
    int destinationNodeId;
    std::string status; // "pending", "success", "failed"
    double travelTimeMinutes;
    std::string failReason;

    Movement() : vehicleId(-1), destinationNodeId(-1), status("pending"), travelTimeMinutes(0.0), failReason("") {}
};

#endif
