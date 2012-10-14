
// Header File
#include "game/action/skill/simple_fireat.h"

// External Dependencies
#include <ugdk/math/integer2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gamething.h"
#include "game/component/damageable.h"
#include "game/component/shape.h"

// Using
using ugdk::math::Integer2D;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameThing;
using game::component::Damageable;

namespace game {
namespace action {
namespace skill {

static bool validate_simple_fireat(const GameObject* caster, const GameThing& target) {
    return true;
}

static SpendInfo spend_simple_fireat(GameObject* caster, const GameThing& target) {
    return SpendInfo(0.0,1.0);
}

static void act_simple_fireat(GameObject* caster, GameThing& target, const Efficiency& power) {
    base::GameController* gc = base::GameController::reference();

    if(target.is_obj())
        target.obj()->damageable_component()->TakeDamage(9001.1337042);
    else {
        auto thiscodeisgonnago = gc->ObjectsAt(target.tile()); //TODO: thiscodeisgonnago
        if(!thiscodeisgonnago.empty()) {
            GameObject* obj = (*(gc->ObjectsAt(target.tile()).begin()));
            Damageable* damn = obj->damageable_component();
            damn->TakeDamage(9001.1337042);
        }
    }
}

SimpleFireAt::SimpleFireAt()
  : super(validate_simple_fireat,spend_simple_fireat,act_simple_fireat) {}

} // namespace skill
} // namespace action
} // namespace game
