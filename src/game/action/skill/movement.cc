
// Header File
#include "game/action/skill/movement.h"

// External Dependencies
// (none)

// Internal Dependencies
#include "game/base/gamething.h"
#include "game/base/gameobject.h"
#include "game/component/shape.h"

// Using
using ugdk::math::Integer2D;
using game::action::skill::GameTargets;
using game::base::GameObject;
using game::base::GameThing;


namespace game {
namespace action {
namespace skill {

Movement::Movement( bool is_relative, const MovementCalculator& calculator,
                    const MovementSpender& spender, const MovementAction& action )
  : is_relative_(is_relative), calculator_(calculator), spender_(spender), action_(action) {}


TimePassed Movement::operator()(base::GameObject* caster, const GameTargets& targets) {
    const GameThing& thing = targets.front();
    if( thing.is_obj() ) return -1.0;

    const Integer2D& tile = thing.tile();
    Integer2D movement = calculator_(caster,tile);

    if(is_relative_) { if( movement.x == 0 && movement.y == 0 ) return false; }
    else {
        const Integer2D& casterpos = caster->shape_component()->occupying_tiles().front();
        if( movement.x == casterpos.x && movement.y == casterpos.y ) return -1.0;
    }

    Efficiency power = spender_(caster,movement);
    if( power != 0.0 ) {
        return action_(caster,movement,power);
    }

    return -1.0;
}

} // namespace skill
} // namespace action
} // namespace game
