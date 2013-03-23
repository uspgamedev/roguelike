#ifndef ROGUELIKE_ACTION_SKILL_SIMPLE_MELEE_H_
#define ROGUELIKE_ACTION_SKILL_SIMPLE_MELEE_H_

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

class SimpleMelee : public Simple {
  typedef Simple super;
  public:
    SimpleMelee();
    ~SimpleMelee() {}
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SIMPLE_MELEE_H_