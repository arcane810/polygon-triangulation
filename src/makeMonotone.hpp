/** @file */

#include "DCEL.hpp"
#include <queue>
#include <utility>
#include <vector>

DCEL makeMonotone(DCEL &dcel);

struct EventPoint {
    Vertex vertex;
    int index;
};

VertexType getVertexType(EventPoint &event_point, DCEL &dcel);
