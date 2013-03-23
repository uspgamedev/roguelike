
// Header File
#include "game/action/skill/simple_idle.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gamething.h"

// Using
using game::base::GameObject;
using game::base::GameThing;

namespace game {
namespace action {
namespace skill {

static bool validate_simple_idle(const GameObject* caster, const GameThing& target) {
    return true;
}

static SpendInfo spend_simple_idle(GameObject* caster, const GameThing& target) {
    return SpendInfo(1.0, 1.0);
}

static void act_simple_idle(GameObject* caster, GameThing& target, const Efficiency& power) {
    return;
}

SimpleIdle::SimpleIdle()
  : super(validate_simple_idle,spend_simple_idle,act_simple_idle) {}

} // namespace skill
} // namespace action
} // namespace game
