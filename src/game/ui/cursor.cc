
// Header File
#include "game/ui/cursor.h"

// External Dependencies
#include <ugdk/base/resourcemanager.h>
#include <ugdk/ui/node.h>
#include <ugdk/graphic/modifier.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/component/shape.h"
#include "game/base/gamecontroller.h"

// Using
using ugdk::math::Vector2D;
using ugdk::base::ResourceManager;
using ugdk::ui::Node;
using ugdk::graphic::TexturedRectangle;
using game::base::GameController;

namespace game {
namespace ui {
    
Cursor::Cursor() : tile_(0,0) {
    Node* node = new Node();
    TexturedRectangle* rect = new TexturedRectangle( ResourceManager::GetTextureFromFile("images/cursor.png") );
    node->set_drawable(rect);

    node_modifier_ = node->modifier();
    node_modifier_->set_scale( Vector2D(GameController::TILE_SIZE) / rect->width() );
    node_modifier_->set_visible(false);

    GameController::reference()->interface_node()->AddChild(node);
}

void Cursor::ChangeTile(const ugdk::math::Integer2D& tile) {
    GameController* gc = GameController::reference();
    if( gc->TileOutOfBounds(tile) ) return;

    tile_ = tile;
    node_modifier_->set_offset(GameController::TILE_SIZE.Multiplied(tile) + gc->content_node()->modifier()->offset());
}

bool Cursor::IsActive() {
    return node_modifier_->visible();
}

void Cursor::ToggleActive() {
    node_modifier_->set_visible(!node_modifier_->visible());
}

} // namespace ui
} // namespace game