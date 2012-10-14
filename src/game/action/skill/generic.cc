
// Header File
#include "game/action/skill/generic.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gamething.h"

// Using
using game::action::skill::GameTargets;
using game::action::time::TimeElapsed;
using game::base::GameThing;

namespace game {
namespace action {
namespace skill {
    
Generic::Generic(const GenericValidator& validator, const GenericSpender& spender, const GenericAction& action)
  : validator_(validator), spender_(spender), action_(action) {}


TimeElapsed Generic::operator()(base::GameObject* caster, const GameTargets& targets) {
    if(!validator_(caster,targets)) return false;

    SpendInfo spend_info = spender_(caster,targets);
    if(spend_info) action_(caster,targets,spend_info);

    return spend_info;
}

} // namespace skill
} // namespace action
} // namespace game
