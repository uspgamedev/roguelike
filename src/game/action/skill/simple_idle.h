#ifndef ROGUELIKE_ACTION_SKILL_SIMPLE_IDLE_H_
#define ROGUELIKE_ACTION_SKILL_SIMPLE_IDLE_H_

// Inheritance
#include "game/action/skill/simple.h"
#include "game/action/skill/skill.h"

// External Dependencies
// (none)

// Internal Dependencies
// (none)

// Forward Declarations
// (none)

namespace game {
namespace action {
namespace skill {

class SimpleIdle : public Simple {
  typedef Simple super;
  public:
    SimpleIdle();
    ~SimpleIdle() {}
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SIMPLE_IDLE_H_