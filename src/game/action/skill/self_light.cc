
// Header File
#include "game/action/skill/self_light.h"

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

static double spend_sense_light(GameObject* caster) {
    return 1.0;
}

static void act_sense_light(GameObject* caster, double power) {
    caster->vision_component()->See();
}

SelfLight* SelfLight::reference_ = nullptr;

SelfLight::SelfLight()
  : super(spend_sense_light, act_sense_light) {}

} // namespace skill
} // namespace action
} // namespace game