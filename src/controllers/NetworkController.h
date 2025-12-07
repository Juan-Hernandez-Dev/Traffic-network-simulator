#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "BaseController.h"
#include "models/Graph.h"
#include <string>

class NetworkController : public BaseController {
private:
    Graph& network;

public:
    NetworkController(Graph& net);

    void handleLoadNetwork();
    void handleSaveNetwork();
    void handleAddNode();
    void handleAddEdge();
    void handleRemoveNode();
    void handleRemoveEdge();
    void handleGenerateSeed();
};

#endif
