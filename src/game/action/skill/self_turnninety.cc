
// Header File
#include "game/action/skill/self_damage.h"

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

static bool validate_self_damage(const GameObject* caster) {
    return caster->damageable_component() != nullptr;
}

static SpendInfo spend_self_damage(GameObject* caster) {
    return SpendInfo(0.0,1.0);
}

static void act_self_damage(GameObject* caster, const Efficiency& power) {
    caster->damageable_component()->TakeDamage(9001.1337042);
}

SelfDamage::SelfDamage()
  : super(validate_self_damage, spend_self_damage, act_self_damage) {}

} // namespace skill
} // namespace action
} // namespace game
