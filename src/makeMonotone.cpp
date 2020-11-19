/** @file */

#include "makeMonotone.hpp"
#include <queue>
#include <set>
#include <utility>
#include <vector>

struct EventPoint {
    Vertex vertex;
    int index;
};

/**
 * A comparator class with a functor to compare 2 vertices for priority in the
 * event_points priority queue
 */
class CompareVertices {
  public:
    bool operator()(EventPoint first, EventPoint second) {
        return (first.vertex.point.y == second.vertex.point.y)
                   ? (first.vertex.point.x > second.vertex.point.x)
                   : first.vertex.point.y < second.vertex.point.y;
    }
};

/**
 * A comparator class with a functor to compare HalfEdges from left to right
 */
class CompareEdges {
  public:
    bool operator()(std::pair<Edge *, int> first,
                    std::pair<Edge *, int> second) {
        return first.first->v1->point.x < second.first->v1->point.x;
    }
};

void makeMonotone(DCEL &dcel) {
    std::priority_queue<EventPoint, std::vector<EventPoint>, CompareVertices>
        event_points;
    for (int i = 0; i < dcel.vertices.size(); i++) {
        event_points.push({dcel.vertices[i], i});
    }
    std::set<std::pair<Edge *, int>, CompareEdges> binary_search_tree;
    std::vector<int> helper(dcel.vertices.size(), -1);
    std::vector<std::pair<int, int>> diagonals;
    while (!event_points.empty()) {
        EventPoint event_point = event_points.top();
        event_points.pop();
        handleVertex(event_point, dcel, binary_search_tree, helper, diagonals);
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

void handleVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    VertexType vertex_type = getVertexType(event_point, dcel);
    switch (vertex_type) {
    case START:
        handleStartVertex(event_point, dcel, binary_search_tree, helper);
        break;
    case END:
        handleEndVertex(event_point, dcel, binary_search_tree, helper,
                        diagonals);
        break;
    case SPLIT:
        handleSplitVertex(event_point, dcel, binary_search_tree, helper,
                          diagonals);
        break;
    case MERGE:
        handleMergeVertex(event_point, binary_search_tree, helper);
        break;
    case REGULAR:
        handleRegularVertex(event_point, binary_search_tree, helper);
    }
}

void handleStartVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper) {
    binary_search_tree.insert(
        std::make_pair(dcel.edges[event_point.index], event_point.index));
    helper[event_point.index] = event_point.index;
}
void handleEndVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    if (event_point.index > 0 && helper[event_point.index] > -1) {
        EventPoint helper_e_i_1;
        helper_e_i_1.vertex = dcel.vertices[helper[event_point.index - 1]];
        helper_e_i_1.index = helper[event_point.index - 1];
        if (getVertexType(helper_e_i_1, dcel) == MERGE) {
            diagonals.push_back(
                std::make_pair(event_point.index, helper_e_i_1.index));
            binary_search_tree.erase(std::make_pair(
                (dcel.edges[event_point.index - 1]), event_point.index - 1));
        }
    }
}
void handleSplitVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    auto ejp = (binary_search_tree.lower_bound(
        std::make_pair(dcel.edges[event_point.index], event_point.index)));
    ejp--;
    diagonals.push_back(
        std::make_pair(helper[(*ejp).second], event_point.index));
    helper[event_point.index] = event_point.index;
    helper[(*ejp).second] = event_point.index;
}
void handleMergeVertex(EventPoint &event_point,
                       std::set<Edge, CompareEdges> &binary_search_tree,
                       std::vector<Vertex *> &helper) {}
void handleRegularVertex(EventPoint &event_point,
                         std::set<Edge, CompareEdges> &binary_search_tree,
                         std::vector<Vertex *> &helper) {}