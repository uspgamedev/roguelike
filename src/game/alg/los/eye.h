#ifndef ROGUELIKE_ALG_LOS_EYE_H_
#define ROGUELIKE_ALG_LOS_EYE_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/frame.h>
#include <ugdk/math/integer2D.h>
#include "utils/integer2Dutils.h"

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace alg {
namespace los {

struct Eye {
    Eye(const ugdk::math::Integer2D& coordinates, const ugdk::Frame& frame);
    Eye(const ugdk::math::Integer2D& coordinates, double left, double top, double right, double bottom);
    Eye(int x, int y, const ugdk::Frame& frame);
    Eye(int x, int y, double left, double top, double right, double bottom);
    ~Eye() {}

    ugdk::math::Integer2D coords;
    ugdk::Frame frame;
};

bool operator<(const Eye& lhs, const Eye& rhs);

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_EYE_H_