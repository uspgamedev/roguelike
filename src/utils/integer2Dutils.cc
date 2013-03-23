
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

// lexical (dictionary) ordering
bool operator<(const Frame& lhs, const Frame& rhs) {
    double l1, l2, l3, r1, r2, r3;

    /*
    double l1 = lhs.left();
    double l2 = lhs.top();
    double l3 = lhs.right();
    double l4 = lhs.bottom();
    double r1 = rhs.left();
    double r2 = rhs.top();
    double r3 = rhs.right();
    double r4 = rhs.bottom();
    */

    return (l1 = lhs.left()) < (r1 = rhs.left()) || (
             (l1 == r1) && ( (l2 = lhs.top()) < (r2 = rhs.top()) || (
               (l2 == r2) && ( (l3 = lhs.right()) < (r3 = rhs.right()) || (
                 (l3 == r3) && lhs.bottom() < rhs.bottom()
               ))
             ))
           );
}

} // namespace ugdk