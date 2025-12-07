#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include "BaseView.h"
#include "models/Graph.h"
#include <string>

class NetworkView : public BaseView {
public:
    NetworkView();

    void showAdjacencyList(const Graph& network);
    void showAdjacencyMatrix(const Graph& network);
    void showNodeDetails(const Node& node);
};

#endif
