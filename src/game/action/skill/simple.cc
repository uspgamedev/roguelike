
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
    // Simple skills all have this validator step:
    if(targets.size() != 1) return false;
    GameThing target = targets.front();

    if(!validator_(caster,target)) return false;

    SpendInfo spend_info = spender_(caster,target);
    if(spend_info) action_(caster,target,spend_info);

    return spend_info;
}

} // namespace skill
} // namespace action
} // namespace game
