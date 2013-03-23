
// Header File
#include "game/action/skill/simple_melee.h"

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

static bool validate_simple_melee(const GameObject* caster, const GameThing& target) {
    
    if( target.is_obj() ) {
        for(auto tait = target.obj()->shape_component()->occupying_tiles().begin(); tait != target.obj()->shape_component()->occupying_tiles().end(); ++tait)
            for(auto cait = caster->shape_component()->occupying_tiles().begin(); cait != caster->shape_component()->occupying_tiles().end(); ++cait)
                if( ((*tait) - (*cait)).Length() < 2 )
                    return true;
    }
    else {
        for(auto cait = caster->shape_component()->occupying_tiles().begin(); cait != caster->shape_component()->occupying_tiles().begin(); ++cait)
            if( ((*cait) - target.tile()).Length() < 2 )
                    return true;
    }
    return false;
}

static SpendInfo spend_simple_melee(GameObject* caster, const GameThing& target) {

    return SpendInfo(0.0, 1.0);
}

static void act_simple_melee(GameObject* caster, GameThing& target, const Efficiency& power) {
    base::GameController* gc = base::GameController::reference();

    if(target.is_obj()) {
        if(target.obj()->damageable_component())
            target.obj()->damageable_component()->TakeDamage(9001.1337042);
    }
    else {
        auto thiscodeisgonnago = gc->ObjectsAt(target.tile()); //TODO: thiscodeisgonnago
        if(!thiscodeisgonnago.empty()) {
            GameObject* obj = (*(gc->ObjectsAt(target.tile()).begin()));
            Damageable* damn = obj->damageable_component();
            if(damn)
                damn->TakeDamage(9001.1337042);
        }
    }
}

SimpleMelee::SimpleMelee()
  : super(validate_simple_melee,spend_simple_melee,act_simple_melee) {}

} // namespace skill
} // namespace action
} // namespace game
