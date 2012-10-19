
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

static bool validate_fireat(const GameObject* caster, const GameThing& target) {
    return true;
}

static Efficiency spend_fireat(GameObject* caster, const GameThing& target) {
    return 1.0;
}

static TimePassed act_fireat(GameObject* caster, GameThing& target, Efficiency power) {
    base::GameController* gc = base::GameController::reference();

    if(target.is_obj()) {
        if(target.obj()->damageable_component())
            target.obj()->damageable_component()->TakeDamage(9001.1337042);
    }
    else {
        auto thiscodeisgonnago = gc->ObjectsAt(target.tile());
        if(!thiscodeisgonnago.empty()) {
            GameObject* obj = (*(gc->ObjectsAt(target.tile()).begin()));
            Damageable* damn = obj->damageable_component();
            if(damn)
                damn->TakeDamage(9001.1337042);
        }
    }
    return 0.0;
}

SimpleFireAt::SimpleFireAt()
  : super(validate_fireat,spend_fireat,act_fireat) {}

} // namespace skill
} // namespace action
} // namespace game
