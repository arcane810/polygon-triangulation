/** @file */

#include "DCEL.hpp"

Face::Face(HalfEdge *edge) : edge(edge) {}

Vertex::Vertex(Point p) : point(p) {}

HalfEdge::HalfEdge(Vertex *origin) : origin(origin) {}

DCEL::DCEL(std::vector<Point> points) {
    Face outer = Face();
    Face inner = Face();

    // Populate Vertices
    for (Point p : points) {
        vertices.push_back(Vertex(p));
    }
    int n = vertices.size();

    HalfEdge *prev_in = nullptr;
    HalfEdge *prev_out = nullptr;

    HalfEdge *first_in, *first_out;

    for (int i = 0; i < n; i++) {

        // Outer HalfEdge
        HalfEdge curr_out = HalfEdge(&vertices[(i + 1) % n]);

        vertices[(i + 1) % n].edge = &curr_out;

        curr_out.next = prev_out;
        if (prev_out != nullptr) {
            prev_out->prev = &curr_out;
        } else {
            first_out = &curr_out;
        }
        prev_out = &curr_out;

        HalfEdge curr_in = HalfEdge(&vertices[i]);
        curr_in.twin = &curr_out;
        curr_out.twin = &curr_in;

        curr_in.prev = prev_in;
        if (prev_in != nullptr) {
            prev_in->next = &curr_in;
        } else {
            first_in = &curr_in;
        }
        prev_in = &curr_in;
    }
    prev_out->prev = first_out;
    first_out->next = prev_out;

    prev_in->next = first_in;
    first_in->prev - prev_in;

    inner.edge = first_in;

    outer.edge = first_out;
}