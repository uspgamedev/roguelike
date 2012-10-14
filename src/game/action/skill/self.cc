
// Header File
#include "game/action/skill/self.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"

// Using
using game::base::GameObject;
using game::action::skill::GameTargets;
using game::action::time::TimeElapsed;

namespace game {
namespace action {
namespace skill {
    
Self::Self( const SelfValidator& validator, const SelfSpender& spender, const SelfAction& action )
  : validator_(validator), spender_(spender), action_(action) {}

TimeElapsed Self::operator()(GameObject* caster, const GameTargets&) {
    if(!validator_(caster)) return false;

    SpendInfo spend_info = spender_(caster);
    if(spend_info) action_(caster,spend_info);

    return spend_info;
}

} // namespace skill
} // namespace action
} // namespace game
