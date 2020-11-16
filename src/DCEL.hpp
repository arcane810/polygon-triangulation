#pragma once
#include <vector>

/**
 * A Class for a Point in 2-D Space
 */
class Point {
  public:
    /// The x coordinate of the Point
    long double x;
    /// The y coordinate of the Point
    long double y;

    /**
     * Constructor. Initializes the coordinates to the passed parameters
     *
     * @param x The x coordinate
     * @param y The y coordinate
     */
    Point(long double x, long double y);

    /**
     * Default Constructor
     */
    Point();
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
    /// Face which the half edge is incident on
    Face *face;

    /**
     * Default Constructor
     */
    HalfEdge();

    /**
     * Constructor.
     *
     * @param origin Any incident edge of the face
     */
    HalfEdge(Vertex *origin, Face *face);
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

    /**
     * Constructor. Makes a DCEL from a vector of points of a polygon.
     *
     * @param points List of points of a polygon in clockwise order
     */
    DCEL(std::vector<Point> points);
};