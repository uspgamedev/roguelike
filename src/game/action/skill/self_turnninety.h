#ifndef ROGUELIKE_ACTION_SKILL_SELF_TURNNINETY_H_
#define ROGUELIKE_ACTION_SKILL_SELF_TURNNINETY_H_

// Inheritance
#include "game/action/skill/self.h"
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

class SelfTurnNinety : public Self {
  typedef Self super;
  public:
    SelfTurnNinety();
    ~SelfTurnNinety() {}
};

} // namespace skill
} // namespace action
} // namespace game

#endif // ROGUELIKE_ACTION_SKILL_SELF_TURNNINETY_H_