
// Header File
#include "game/alg/los/eye.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Using
using ugdk::Frame;
using ugdk::math::Integer2D;

namespace game {
namespace alg {
namespace los {

Eye::Eye(const Integer2D& coordinates, const Frame& eyeframe)
  : coords(coordinates), frame(eyeframe) {}
Eye::Eye(const Integer2D& coordinates, double left, double top, double right, double bottom)
  : coords(coordinates), frame(left,top,right,bottom) {}
Eye::Eye(int x, int y, const ugdk::Frame& eyeframe)
  : coords(x,y), frame(eyeframe) {}
Eye::Eye(int x, int y, double left, double top, double right, double bottom)
  : coords(x,y), frame(left,top,right,bottom) {}

bool operator<(const Eye& lhs, const Eye& rhs) {
    return lhs.coords < rhs.coords || (lhs.coords == rhs.coords && lhs.frame < rhs.frame);
}

} // namespace los
} // namespace alg
} // namespace game
