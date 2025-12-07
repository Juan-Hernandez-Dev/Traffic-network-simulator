#ifndef VEHICLEVIEW_H
#define VEHICLEVIEW_H

#include "BaseView.h"
#include "models/HashTable.h"
#include <string>

class VehicleView : public BaseView {
public:
    VehicleView();

    void showAllVehicles(const HashTable& registry);
    void showHashInfo(const HashTable& registry);
    void showMovementHistory();
    void showVehicleDetails(const Vehicle& vehicle);
};

#endif
