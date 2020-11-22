#include "DCEL.hpp"
#include <utility>
#include <vector>

DCEL monotoneTriangulation(DCEL &dcel);
void faceTriangulation(Face &face, DCEL &dcel,
                       std::vector<std::pair<int, int>> &diagonals);