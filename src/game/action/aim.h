#ifndef ROGUELIKE_ACTION_AIM_H_
#define ROGUELIKE_ACTION_AIM_H_

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
namespace action {

class Aim {
  public:
    Aim();
    ~Aim() {}

    ugdk::math::Integer2D AimedAt() { return target_.tile(); }
    void AimAt(const ugdk::math::Integer2D& aim);
    bool IsActive() { return target_.IsActive(); }
    void ToggleAim() { target_.ToggleActive(); }
    bool HasOrigin() { return origin_ != nullptr; }

    void set_origin(const ugdk::math::Integer2D* origin) { origin_ = origin; }

  private:
    const ugdk::math::Integer2D* origin_;
    ui::Cursor target_;
};

} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_AIM_H_