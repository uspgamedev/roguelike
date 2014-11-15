#ifndef ROGUELIKE_ALG_LOS_CONE_H_
#define ROGUELIKE_ALG_LOS_CONE_H_

// Inheritance
// (none)

// External Dependencies
#include <list>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/alg/equationallinedouble.h"

// Forward Declarations
#include "game/alg/los.h"

namespace game {
namespace alg {
namespace los {

class Cone {
  public:
    Cone(const EquationalLineDouble& upper, const EquationalLineDouble& lower);
    ~Cone() {};
    
    enums::bump::BumpType ComputeBumpType(const ugdk::math::Vector2D& up_left);

    void UpperBump(const ugdk::math::Vector2D& up_left);
    void LowerBump(const ugdk::math::Vector2D& up_left);

    const EquationalLineDouble& upper() const { return upper_; }
    const EquationalLineDouble& lower() const { return lower_; }

  private:
    EquationalLineDouble upper_;
    EquationalLineDouble lower_;
    
    std::list<ugdk::math::Vector2D> upper_bumps_;
    std::list<ugdk::math::Vector2D> lower_bumps_;
};

} // namespace los
} // namespace alg
} // namespace game

#endif // ROGUELIKE_ALG_LOS_CONE_H_