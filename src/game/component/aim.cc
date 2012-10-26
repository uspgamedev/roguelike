
// Header File
#include "game/component/aim.h"

// External Dependencies
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"

// Using
using ugdk::Vector2D;
using ugdk::math::Integer2D;
using game::base::GameController;

namespace game {
namespace component {
    
Aim::Aim(const Integer2D& origin) : origin_(origin), target_() {}

void Aim::AimAt(const ugdk::math::Integer2D& aimed_tile) {
    GameController* gc = GameController::reference();
    if( gc->TileOutOfBounds(aimed_tile) ) return;
    aimed_tile_ = aimed_tile;
    cursor_node_->modifier()->set_offset(GameController::TILE_SIZE.Multiplied(aimed_tile_));
}

void Aim::ToggleAim() {
    cursor_node_->modifier()->set_visible(!cursor_node_->modifier()->visible());
    cursor_active_ = !cursor_active_;
}

} // namespace component
} // namespace game