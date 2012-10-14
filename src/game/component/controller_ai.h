#ifndef ROGUELIKE_COMPONENT_CONTROLLER_AI_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_AI_H_

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

class ControllerAi : public Controller {
  typedef Controller super;

  public:
    ControllerAi(game::base::GameObject* owner) : super(owner) {}
    ~ControllerAi() {}

    action::time::TimeElapsed Act() { return false; }
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_AI_H_