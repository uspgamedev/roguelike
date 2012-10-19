#ifndef ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/component/controller.h"

// External Dependencies
#include <ugdk/math/integer2D.h> // where_to_
#include <ugdk/time/timeaccumulator.h> // time_held_
#include <ugdk/graphic/node.h>

// Internal Dependencies
#include "game/component/aim.h"
// (none)

// Forward Declarations
#include <ugdk/time.h>
#include "game/base.h"

namespace game {
namespace component {

class ControllerPlayer : public Controller {
  typedef Controller super;
  public:
    ControllerPlayer(game::base::GameObject* owner);
    ~ControllerPlayer();

    double Act();
    double Cursor();

    ugdk::math::Integer2D Movement();

  private:
    Aim* aim_;
    ugdk::math::Integer2D where_to_;
    ugdk::time::TimeAccumulator time_held_;
    ugdk::time::TimeAccumulator hold_tick_;

    bool held_movement_adjusted_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_