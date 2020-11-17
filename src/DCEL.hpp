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

/**
 * Vertex Class for DCEL
 */
class Vertex {
  public:
    /// The point which the Vertex represents
    Point point;

    /// Incident Edge (any edge that originates from this vertex)
    HalfEdge *edge;

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
 * Face Class for DCEL
 */
class Face {
  public:
    /// A half edge on which incident on face
    HalfEdge *edge;

    /**
     * Default Constructor
     */
    Face();

    /**
     * Constructor which takes in the incident edge.
     *
     * @param edge Any incident edge of the face
     */
    Face(HalfEdge *edge);
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