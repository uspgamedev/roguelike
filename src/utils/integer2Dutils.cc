
#include "utils/integer2Dutils.h"

namespace ugdk {
namespace math {

bool operator==(const Integer2D& lhs, const Integer2D& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Integer2D& lhs, const Integer2D& rhs) {
    return lhs.x < rhs.x || ( lhs.x == rhs.x && lhs.y < rhs.y);
}

} // namespace math

bool operator<(const Frame& lhs, const Frame& rhs) {
    double l1 = lhs.left();
    double l2 = lhs.top();
    double l3 = lhs.right();
    double l4 = lhs.bottom();
    double r1 = rhs.left();
    double r2 = rhs.top();
    double r3 = rhs.right();
    double r4 = rhs.bottom();

    return l1 < r1 || ( l1 == r1 && ( l2 < r2 || ( l2 == r2 && ( l3 < r3 || ( l3 == r3 && l4 < r4 ) ) ) ) );
}

} // namespace ugdk