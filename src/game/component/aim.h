#ifndef ROGUELIKE_COMPONENT_AIM_H_
#define ROGUELIKE_COMPONENT_AIM_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/integer2D.h> // aim_
#include <ugdk/graphic/node.h>

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class Aim {
  public:
    Aim(game::base::GameObject* owner);
    ~Aim() {}

    ugdk::math::Integer2D aim() { return aim_; }
    void AimAt(ugdk::math::Integer2D aim);

    bool IsActive() { return cursor_active_; }
    void ToggleAim();

  protected:
    bool cursor_active_;
    ugdk::math::Integer2D aim_;
    ugdk::graphic::Node* cursor_node_;

    game::base::GameObject* owner_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_AIM_H_