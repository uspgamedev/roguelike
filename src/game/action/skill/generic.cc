
// Header File
#include "game/action/skill/generic.h"

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
    
Generic::Generic(const GenericValidator& validator, const GenericSpender& spender, const GameAction& action)
  : validator_(validator), spender_(spender), action_(action) {}


TimePassed Generic::operator()(base::GameObject* caster, const GameTargets& targets) {

    if(validator_(caster,targets)) {
        Efficiency power = spender_(caster,targets);
        if( power != 0.0 ) {
            return action_(caster,targets,power);
        }
    }

    return -1.0;
}

} // namespace skill
} // namespace action
} // namespace game
