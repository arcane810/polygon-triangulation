/** @file */

#include "makeMonotone.hpp"
#include <queue>

struct EventPoint {
    Vertex vertex;
    int index;
};

/**
 * A comparator class with a functor to compare 2 vertices for priority in the
 * event_points priority queue
 */
class Compare {
  public:
    bool operator()(EventPoint first, EventPoint second) {
        return (first.vertex.point.y == second.vertex.point.y)
                   ? (first.vertex.point.x < second.vertex.point.x)
                   : first.vertex.point.y > second.vertex.point.y;
    }
};

void makeMonotone(DCEL &dcel) {
    std::priority_queue<EventPoint, std::vector<EventPoint>, Compare>
        event_points;
    for (int i = 0; i < dcel.vertices.size(); i++) {
        event_points.push({dcel.vertices[i], i});
    }

    while (!event_points.empty()) {
        EventPoint event_point = event_points.top();
        event_points.pop();
        handleVertex(event_point, dcel);
    }
}

VertexType getVertexType(EventPoint &event_point, DCEL &dcel) {
    int n = dcel.vertices.size();
    Vertex curr_vertex = event_point.vertex;
    Vertex prev_vertex = dcel.vertices[(event_point.index - 1 + n) % n];
    Vertex next_vertex = dcel.vertices[(event_point.index + 1) % n];
    VertexType vertex_type;
    if (prev_vertex.point.isBelow(curr_vertex.point) &&
        next_vertex.point.isBelow(curr_vertex.point)) {
        if (counterClockwise(prev_vertex.point, curr_vertex.point,
                             next_vertex.point)) {
            vertex_type = START;
        } else {
            vertex_type = SPLIT;
        }
    } else if (curr_vertex.point.isBelow(prev_vertex.point) &&
               curr_vertex.point.isBelow(next_vertex.point)) {
        if (counterClockwise(prev_vertex.point, curr_vertex.point,
                             next_vertex.point)) {
            vertex_type = END;
        } else {
            vertex_type = MERGE;
        }
    } else {
        vertex_type = REGULAR;
    }
}

void handleVertex(EventPoint &event_point, DCEL &dcel) {
    VertexType vertex_type = getVertexType(event_point, dcel);
    switch (vertex_type) {
    case START:
        handleStartVertex(event_point);
        break;
    case END:
        handleEndVertex(event_point);
        break;
    case SPLIT:
        handleSplitVertex(event_point);
        break;
    case MERGE:
        handleMergeVertex(event_point);
        break;
    case REGULAR:
        handleRegularVertex(event_point);
    }
}

void handleStartVertex(EventPoint &event_point) {}
void handleEndVertex(EventPoint &event_point) {}
void handleSplitVertex(EventPoint &event_point) {}
void handleMergeVertex(EventPoint &event_point) {}
void handleRegularVertex(EventPoint &event_point) {}