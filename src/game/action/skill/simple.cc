
// Header File
#include "game/action/skill/simple.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gamething.h"

// Using
using game::action::skill::GameTargets;
using game::base::GameThing;

namespace game {
namespace action {
namespace skill {
    
Simple::Simple(const SimpleValidator& validator, const SimpleSpender& spender, const SimpleAction& action)
  : validator_(validator), spender_(spender), action_(action) {}

TimePassed Simple::operator()(base::GameObject* caster, const GameTargets& targets) {
    if(targets.size() != 1) return -1.0;

    GameThing target = targets.front();

    if(validator_(caster, target)) {
        Efficiency power = spender_(caster,target);
        if( power != 0.0 ) {
            return action_(caster,target,power);
        }
    }

    return -1.0;
}

} // namespace skill
} // namespace action
} // namespace game
