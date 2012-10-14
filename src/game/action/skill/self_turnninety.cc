
// Header File
#include "game/action/skill/self_turnninety.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/damageable.h"

// Using
using game::base::GameObject;
using game::component::Damageable;

namespace game {
namespace action {
namespace skill {

static bool validate_self_turninety(const GameObject*) {
    return false;
}

static SpendInfo spend_self_turninety(GameObject*) {
    return SpendInfo(false,0.0);
}

static void act_self_turninety(GameObject*, const Efficiency&) {
    ;
}

SelfTurnNinety::SelfTurnNinety()
  : super(validate_self_turninety, spend_self_turninety, act_self_turninety) {}

} // namespace skill
} // namespace action
} // namespace game
