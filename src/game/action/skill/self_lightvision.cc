
// Header File
#include "game/action/skill/self_lightvision.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/component/vision.h"

// Using
using game::base::GameObject;

namespace game {
namespace action {
namespace skill {

static bool validate_self_lightvision(const GameObject* caster) {
    return caster->vision_component() != nullptr;
}

static SpendInfo spend_self_lightvision(GameObject* caster) {
    return SpendInfo(0.0,1.0);
}

static void act_self_lightvision(GameObject* caster, const Efficiency& power) {
    caster->vision_component()->See();
}

LightVision::LightVision()
  : super(validate_self_lightvision, spend_self_lightvision, act_self_lightvision) {}

} // namespace skill
} // namespace action
} // namespace game
