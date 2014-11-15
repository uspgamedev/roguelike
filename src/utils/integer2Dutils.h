#ifndef ROGUELIKE_INTEGER2DUTILS_H_
#define ROGUELIKE_INTEGER2DUTILS_H_

#include <ugdk/math/frame.h>
#include <ugdk/math/integer2D.h>

namespace ugdk {
namespace math {

bool operator==(const Integer2D& lhs, const Integer2D& rhs);
bool operator<(const Integer2D& lhs, const Integer2D& rhs);
bool operator<(const Frame& lhs, const Frame& rhs);

} // namespace math
} // namespace ugdk

#endif /* ROGUELIKE_INTEGER2DUTILS_H_ */