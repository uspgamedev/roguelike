
// Header File
#include "game/action/aim.h"

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"

// Using
using ugdk::math::Vector2D;
using game::base::GameController;

namespace game {
namespace action {
    
Aim::Aim() : origin_(nullptr), target_() {}

void Aim::AimAt(const ugdk::math::Integer2D& aimed_tile) {
    GameController* gc = GameController::reference();
    if( gc->TileOutOfBounds(aimed_tile) ) return;
    target_.ChangeTile(aimed_tile);
}

} // namespace action
} // namespace game