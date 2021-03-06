#ifndef ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_

// Inheritance
#include "game/component/controller.h"

// External Dependencies
#include <ugdk/math/integer2D.h> // where_to_
#include <ugdk/time/timeaccumulator.h> // time_held_
#include <ugdk/ui/node.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/action/aim.h"

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

    action::time::TimeElapsed Act();

  private:
    action::time::TimeElapsed cursor(action::Aim* aim);
    ugdk::math::Integer2D movement();

    ugdk::math::Integer2D where_to_;
    ugdk::time::TimeAccumulator time_held_;
    ugdk::time::TimeAccumulator hold_tick_;

    game::base::GameController* gc;

    bool held_movement_adjusted_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_PLAYER_H_