#ifndef ROGUELIKE_COMPONENT_CONTROLLER_IDLE_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_IDLE_H_

// Inheritance
#include "game/component/controller.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ControllerIdle : public Controller {
  typedef Controller super;
  public:
    ControllerIdle(game::base::GameObject* owner) : super(owner) {}
    ~ControllerIdle() {}

    action::time::TimeElapsed Act() { return false; }
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_IDLE_H_