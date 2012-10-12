// Header File
#include "game/component/aim.h"

// External Dependencies
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/component/shape.h"
#include "game/base/gamecontroller.h"
#include "game/base/gametile.h"
#include "game/base/gameobject.h"

// Forward Declarations
// (none)

// Using
using ugdk::Vector2D;
using ugdk::base::ResourceManager;
using ugdk::graphic::TexturedRectangle;

namespace game {
namespace component {
    
Aim::Aim(game::base::GameObject* owner) : owner_(owner), cursor_node_(new ugdk::graphic::Node) {
    cursor_active_ = false;
    cursor_node_->modifier()->set_visible(false);
    cursor_node_->set_drawable(new TexturedRectangle( ResourceManager::GetTextureFromFile("images/cursor.png") ));
    cursor_node_->modifier()->set_scale( Vector2D(1.0, 1.0) * 0.382 );
    game::base::GameController::reference()->interface_node()->AddChild(cursor_node_);
}

void Aim::AimAt(ugdk::math::Integer2D aim) {
    if(aim_.x == aim.x && aim_.y == aim.y)
        return;
    aim_ = aim;
    cursor_node_->modifier()->set_offset(game::base::GameTile::TILE_SIZE.Multiplied(aim_));
}

void Aim::ToggleAim() {
    cursor_node_->modifier()->set_visible(!cursor_node_->modifier()->visible());
    cursor_active_ = !cursor_active_;
}

} // namespace component
} // namespace game