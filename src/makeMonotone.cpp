/** @file */

#include "makeMonotone.hpp"
#include <iostream>
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

int n;

VertexType getVertexType(EventPoint &event_point, DCEL &dcel) {
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
    return vertex_type;
}

void handleStartVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper) {
    binary_search_tree.insert(
        std::make_pair(&dcel.edges[event_point.index], event_point.index));
    helper[event_point.index] = event_point.index;
}
void handleEndVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    if (event_point.index > 0 && helper[event_point.index] > -1) {
        EventPoint helper_e_i_1;
        helper_e_i_1.vertex =
            dcel.vertices[helper[(event_point.index - 1 + n) % n]];
        helper_e_i_1.index = helper[(event_point.index - 1 + n) % n];
        if (getVertexType(helper_e_i_1, dcel) == MERGE) {
            diagonals.push_back(
                std::make_pair(event_point.index, helper_e_i_1.index));
            binary_search_tree.erase(
                std::make_pair((&dcel.edges[(event_point.index - 1 + n) % n]),
                               (event_point.index - 1 + n) % n));
        }
    }
}
void handleSplitVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    auto ejp = (binary_search_tree.lower_bound(
        std::make_pair(&dcel.edges[event_point.index], event_point.index)));
    ejp--;
    diagonals.push_back(
        std::make_pair(helper[(*ejp).second], event_point.index));
    helper[event_point.index] = event_point.index;
    helper[(*ejp).second] = event_point.index;
}

void handleMergeVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    if (event_point.index > 0 && helper[event_point.index] > -1) {
        EventPoint helper_e_i_1;
        helper_e_i_1.vertex =
            dcel.vertices[helper[(event_point.index - 1 + n) % n]];
        helper_e_i_1.index = helper[(event_point.index - 1 + n) % n];
        if (getVertexType(helper_e_i_1, dcel) == MERGE) {
            diagonals.push_back(
                std::make_pair(event_point.index, helper_e_i_1.index));
        }
    }
    binary_search_tree.erase(
        std::make_pair((&dcel.edges[(event_point.index - 1 + n) % n]),
                       (event_point.index - 1 + n) % n));
    auto ejp = (binary_search_tree.lower_bound(
        std::make_pair(&dcel.edges[event_point.index], event_point.index)));
    ejp--;
    EventPoint helper_e_j;
    helper_e_j.vertex = dcel.vertices[helper[(*ejp).second]];
    helper_e_j.index = helper[(*ejp).second];
    if (getVertexType(helper_e_j, dcel) == MERGE) {
        diagonals.push_back(
            std::make_pair(event_point.index, helper_e_j.index));
    }
    helper[(*ejp).second] = event_point.index;
}

void handleRegularVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    int n = dcel.vertices.size();
    Vertex prev = dcel.vertices[(event_point.index - 1 + n) % n];
    Vertex next = dcel.vertices[(event_point.index + 1) % n];
    if (event_point.vertex.point.isBelow(prev.point) &&
        prev.point.isBelow(event_point.vertex.point)) {
        if (event_point.index > 0 && helper[event_point.index] > -1) {
            EventPoint helper_e_i_1;
            helper_e_i_1.vertex =
                dcel.vertices[helper[(event_point.index - 1 + n) % n]];
            helper_e_i_1.index = helper[(event_point.index - 1 + n) % n];
            if (getVertexType(helper_e_i_1, dcel) == MERGE) {
                diagonals.push_back(
                    std::make_pair(event_point.index, helper_e_i_1.index));
                binary_search_tree.erase(std::make_pair(
                    (&dcel.edges[(event_point.index - 1 + n) % n]),
                    (event_point.index - 1 + n) % n));
            }
        }
        binary_search_tree.insert(
            std::make_pair(&dcel.edges[event_point.index], event_point.index));
        helper[event_point.index] = event_point.index;
        binary_search_tree.erase(
            std::make_pair((&dcel.edges[(event_point.index - 1 + n) % n]),
                           (event_point.index - 1 + n) % n));
    } else {
        auto ejp = (binary_search_tree.lower_bound(
            std::make_pair(&dcel.edges[event_point.index], event_point.index)));
        ejp--;
        EventPoint helper_e_j;
        helper_e_j.vertex = dcel.vertices[helper[(*ejp).second]];
        helper_e_j.index = helper[(*ejp).second];
        if (getVertexType(helper_e_j, dcel) == MERGE) {
            diagonals.push_back(
                std::make_pair(event_point.index, helper_e_j.index));
        }
        helper[(*ejp).second] = event_point.index;
    }
}

void handleVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals) {
    VertexType vertex_type = getVertexType(event_point, dcel);
    switch (vertex_type) {
    case START:
        std::cout << "START VERTEX\n";
        handleStartVertex(event_point, dcel, binary_search_tree, helper);
        break;
    case END:
        std::cout << "END VERTEX\n";
        handleEndVertex(event_point, dcel, binary_search_tree, helper,
                        diagonals);
        break;
    case SPLIT:
        std::cout << "SPLIT VERTEX\n";
        handleSplitVertex(event_point, dcel, binary_search_tree, helper,
                          diagonals);
        break;
    case MERGE:
        std::cout << "MERGE VERTEX\n";
        handleMergeVertex(event_point, dcel, binary_search_tree, helper,
                          diagonals);
        break;
    case REGULAR:
        std::cout << "REGULAR VERTEX\n";
        handleRegularVertex(event_point, dcel, binary_search_tree, helper,
                            diagonals);
    }
}

void makeMonotone(DCEL &dcel) {
    n = dcel.vertices.size();
    std::priority_queue<EventPoint, std::vector<EventPoint>, CompareVertices>
        event_points;
    for (int i = 0; i < n; i++) {
        event_points.push({dcel.vertices[i], i});
    }
    std::set<std::pair<Edge *, int>, CompareEdges> binary_search_tree;
    std::vector<int> helper(n, -1);
    std::vector<std::pair<int, int>> diagonals;
    int i = 1;
    while (!event_points.empty()) {
        i++;
        EventPoint event_point = event_points.top();
        event_points.pop();
        handleVertex(event_point, dcel, binary_search_tree, helper, diagonals);
    }
    for (std::pair<int, int> p : diagonals) {
        std::cout << p.first << " " << p.second << "\n";
    }
}
