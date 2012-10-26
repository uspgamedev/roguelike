// Header File
#include "game/component/aim.h"

// External Dependencies
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/component/shape.h"
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"

// Forward Declarations
// (none)

// Using
using ugdk::Vector2D;
using ugdk::math::Integer2D;
using ugdk::base::ResourceManager;
using ugdk::graphic::TexturedRectangle;
using game::base::GameController;

namespace game {
namespace component {
    
Aim::Aim() : cursor_node_(new ugdk::graphic::Node) {
    cursor_active_ = false;
    cursor_node_->modifier()->set_visible(false);
    TexturedRectangle* rect = new TexturedRectangle( ResourceManager::GetTextureFromFile("images/cursor.png") );
    cursor_node_->set_drawable(rect);
    cursor_node_->modifier()->set_scale( Vector2D(GameController::TILE_SIZE) / rect->width() );
    GameController::reference()->interface_node()->AddChild(cursor_node_);
}

void Aim::AimAt(const ugdk::math::Integer2D& aimed_tile) {
    game::base::GameController* gc = game::base::GameController::reference();
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