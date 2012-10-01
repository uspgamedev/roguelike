
// Header File
#include "game/action/skill/self.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using game::base::GameObject;
using game::action::skill::GameTargets;

namespace game {
namespace action {
namespace skill {
    
Self::Self( const SenseSpender& spender, const  SenseAction& action )
  : spender_(spender), action_(action) {}

double Self::operator()(GameObject* caster, const GameTargets& targets) {
    double power = spender_(caster);
    if(power != 0.0) {
        return action_(caster,power);
    }

    return -1.0;
}

} // namespace skill
} // namespace action
} // namespace game
