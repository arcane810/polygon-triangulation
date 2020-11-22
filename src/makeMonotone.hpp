/** @file */

#include "DCEL.hpp"
#include <queue>
#include <utility>
#include <vector>

/**
 * Takes the DCEL of a polygon and returns a DCEL of its monotone partitioning
 * @param dcel DCEL of the polygon (passed by reference)
 * @return DCEL of monotone partitioning of polygon
 */
DCEL makeMonotone(DCEL &dcel);

/**
 * A wrapper structure which represents an event point of the sweep line
 */
struct EventPoint {
    Vertex vertex;
    int index;
};

/**
 * A function that returns the type of an event point, i.e. Split, End, etc.
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 *
 * @return A value of enum type VertexType which denotes the type of the vertex
 */
VertexType getVertexType(EventPoint &event_point, DCEL &dcel);

/**
 * A function to handle START Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 */
void handleStartVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper);

/**
 * A function to handle END Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 * @param diagonals A vector of diagonals to which new diagonals are added.
 */
void handleEndVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals);

/**
 * A function to handle SPLIT Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 * @param diagonals A vector of diagonals to which new diagonals are added.
 */
void handleSplitVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals);

/**
 * A function to handle MERGE Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 * @param diagonals A vector of diagonals to which new diagonals are added.
 */
void handleMergeVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals);

/**
 * A function to handle REGULAR Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 * @param diagonals A vector of diagonals to which new diagonals are added.
 */
void handleRegularVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals);

/**
 * A function to handle Vertices of polygon
 * @param event_point the event point
 * @param dcel DCEL of the polygon to which the vertex belongs
 * @param binary_search_tree A BST containing the edges.
 * @param helper A vector which stores the helper of edges using their indices.
 * @param diagonals A vector of diagonals to which new diagonals are added.
 */
void handleVertex(
    EventPoint &event_point, DCEL &dcel,
    std::set<std::pair<Edge *, int>, CompareEdges> &binary_search_tree,
    std::vector<int> &helper, std::vector<std::pair<int, int>> &diagonals);
