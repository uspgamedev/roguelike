#ifndef ROGUELIKE_COMPONENT_AIM_H_
#define ROGUELIKE_COMPONENT_AIM_H_

// Inheritance
// (none)

// External Dependencies
// (none)

// Internal Dependencies
#include "game/ui/cursor.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace component {

class Aim {
  public:
    Aim(const ugdk::math::Integer2D& origin);
    ~Aim() {}

    ugdk::math::Integer2D AimedAt() { return target_.position(); }
    void AimAt(const ugdk::math::Integer2D& aim);

    bool IsActive() { return target_.IsActive(); }
    void ToggleAim();

  private:
    ugdk::math::Integer2D& origin_;
    ui::Cursor target_;

};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_AIM_H_