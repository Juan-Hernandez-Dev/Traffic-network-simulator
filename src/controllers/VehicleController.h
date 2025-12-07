#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H

#include "BaseController.h"
#include "models/HashTable.h"
#include "models/Graph.h"
#include <string>

class VehicleController : public BaseController {
private:
    HashTable& registry;
    Graph& network;

public:
    VehicleController(HashTable& reg, Graph& net);

    void handleLoadVehicles();
    void handleSaveVehicles();
    void handleAddVehicle();
    void handleSearchVehicle();
    void handleRemoveVehicle();
    void handleShowAll();
    void handleShowHashInfo();
    void handleMoveVehicle();
    void handleShowMovementHistory();
};

#endif
