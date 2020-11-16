#include "DCEL.hpp"

Point::Point(long double x, long double y) : y(y), x(x) {}

Point::Point() : y(0), x(0) {}

Face::Face(HalfEdge *edge) : edge(edge) {}

Vertex::Vertex(Point p) : point(p) {}

HalfEdge::HalfEdge(Vertex *origin, Face *face) : origin(origin), face(face) {}

DCEL::DCEL(std::vector<Point> points) {
    Face outer = Face();
    Face inner = Face();
    for (Point p : points) {
        vertices.push_back(Vertex(p));
    }
    int n = vertices.size();
    HalfEdge *prev_in = nullptr;
    HalfEdge *prev_out = nullptr;
    HalfEdge *first_in, *first_out;
    for (int i = 0; i < n; i++) {
        HalfEdge curr_out = HalfEdge(&vertices[i], &outer);
        vertices[i].edge = &curr_out;
        curr_out.prev = prev_out;
        if (prev_out != nullptr) {
            prev_out->next = &curr_out;
        } else {
            first_out = &curr_out;
        }
        prev_out = &curr_out;

        HalfEdge curr_in = HalfEdge(&vertices[(i + 1) % n], &inner);
        curr_in.twin = &curr_out;
        curr_out.twin = &curr_in;

        curr_in.next = prev_in;
        if (prev_in != nullptr) {
            prev_in->prev = &curr_in;
        } else {
            first_in = &curr_in;
        }
        prev_in = &curr_in;
    }
    prev_out->next = first_out;
    first_out->prev = prev_out;

    prev_in->prev = first_in;
    first_in->next - prev_in;
    inner.edge = first_in;
    outer.edge = first_out;
}