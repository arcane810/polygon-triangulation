# Polygon Triangulation

An implementation of polygon triangulation which first partitions the polygon into monotone parts and triangulates the monotone polygons. A DCEL is used to store the polygon and its monotone partitioning and the triangulation. Made as a part of the computation geometry course at BITS Pilani, Hyderabad Campus.

To use the api:

- Use utils.cpp header for the Point class
- Include utils.hpp, DCEL.hpp, makeMonotone.hpp and monotoneTriangulation.hpp
- Use makeMonotone() function to partition the polygon into monotone polygons and then use monotoneTriangulation() function to triangulate the partitions polygon.
- Compile all the files in proper order.

Important points to take care of:

- While using this API provide the polygon in counter-clockwise order in the DCEL constructor.
