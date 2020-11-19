/** @file */

#pragma once
#include "utils.hpp"
#include <vector>

/// Enum type for the type of vertex
enum VertexType {
    /// Start Vertex
    START,
    /// End Vertex
    END,
    /// Split Vertex
    SPLIT,
    /// Merge Vertex
    MERGE,
    /// Regular Vertex
    REGULAR
};

class HalfEdge;
class Edge;

/**
 * Vertex Class for DCEL
 */
class Vertex {
  public:
    /// The point which the Vertex represents
    Point point;

    /// Incident HalfEdge (any half edge that originates from this vertex)
    HalfEdge *half_edge;

    /**
     * Default Constructor
     */
    Vertex();

    /**
     * Constructor.
     *
     * @param origin Any incident edge of the face
     */
    Vertex(Point p);
};

/**
 * Half-Edge Class for DCEL
 */
class HalfEdge {
  public:
    /// Pointer to the origin vertex of the half edge
    Vertex *origin;
    /// Pointer to the twin half edge
    HalfEdge *twin;
    /// Pointer to the next half edge
    HalfEdge *next;
    /// Pointer to previous hald edge
    HalfEdge *prev;
    /// Edge to which HalfEdge belongs
    Edge *edge;

    /**
     * Default Constructor
     */
    HalfEdge();

    /**
     * Constructor.
     *
     * @param origin Any incident edge of the face
     */
    HalfEdge(Vertex *origin);
};

/**
 * Half-Edge Class for DCEL
 */
class Edge {
  public:
    /// Pointer to the origin vertex of the half edge
    Vertex *v1, *v2;
    /// Pointer to one of the half edges
    HalfEdge *half_edge;

    /**
     * Default Constructor
     */
    Edge();

    /**
     * Constructor.
     *
     * @param origin Any incident edge of the face
     */
    Edge(Vertex *v1, Vertex *v2, HalfEdge *half_edge);
};

/**
 * Face Class for DCEL
 */
class Face {
  public:
    /// A half edge on which incident on face
    HalfEdge *half_edge;

    /**
     * Default Constructor
     */
    Face();

    /**
     * Constructor which takes in the incident edge.
     *
     * @param half_edge Any incident edge of the face
     */
    Face(HalfEdge *half_edge);
};

/**
 * DCEL class
 */
class DCEL {
  public:
    /// List of Vertices in the DCEL
    std::vector<Vertex> vertices;

    /// List of Faces in the DCEL
    std::vector<Face> faces;

    /// List of HalfEdges in the DCEL
    std::vector<HalfEdge> half_edges;

    /// List of Edges in the DCEL
    std::vector<Edge *> edges;

    /**
     * Constructor. Makes a DCEL from a vector of points of a polygon.
     *
     * @param points List of points of a polygon in clockwise order
     */
    DCEL(std::vector<Point> points);

    /**
     * Adds an edge to the DCEL
     */
    void addEdge();
};
