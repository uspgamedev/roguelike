#ifndef ROGUELIKE_COMPONENT_CONTROLLER_H_
#define ROGUELIKE_COMPONENT_CONTROLLER_H_

// Inheritance
#include "game/component/componentbase.h"

// External Dependencies
#include <string>

// Internal Dependencies
#include "game/action/skill/skill.h"
#include "game/action/time/timeelapsed.h"

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace component {

class Controller : public ComponentBase {
  typedef ComponentBase super;
  public:
    Controller(game::base::GameObject* owner) : super(owner) {}
    virtual ~Controller() {}

    virtual action::time::TimeElapsed Act();

    action::time::TimeElapsed Cast(const std::string& skill, const action::skill::GameTargets& targets);
    action::time::TimeElapsed Cast(const std::string& skill, const ugdk::math::Integer2D& target);
    action::time::TimeElapsed Cast(const std::string& skill, base::GameObject* target);
    action::time::TimeElapsed Cast(const std::string& skill);

  private:
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_CONTROLLER_H_