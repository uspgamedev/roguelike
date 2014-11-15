// Header File
#include "gametile.h"

// External Dependencies
#include <memory>
#include <ugdk/resource/module.h>
#include <ugdk/ui/drawable/texturedrectangle.h>
#include <ugdk/ui/node.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/system/compatibility.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/component/graphic.h"

// Using
using ugdk::math::Integer2D;
using ugdk::math::Vector2D;
using game::base::GameController;
using game::base::GameObject;
using ugdk::ui::Node;
using ugdk::ui::TexturedRectangle;

namespace game {
namespace base {

GameTile::GameTile(const Integer2D& coords) : coords_(coords), node_(new Node) {
	node_->set_drawable(
		ugdk::MakeUnique<TexturedRectangle>(
			ugdk::resource::GetTextureFromFile("images/white.png")
		)
	);
    node_->geometry() = ugdk::graphic::Geometry(
		Vector2D(),
		Vector2D(GameController::TILE_SIZE) / node_->drawable()->width()
	);
}
GameTile::GameTile(int x, int y) : coords_(x,y), node_(new Node) {
	node_->set_drawable(
		ugdk::MakeUnique<TexturedRectangle>(
			ugdk::resource::GetTextureFromFile("images/white.png")
		)
	);
    node_->geometry() = ugdk::graphic::Geometry(
		Vector2D(),
		Vector2D(GameController::TILE_SIZE) / node_->drawable()->width()
	);
}

GameTile::~GameTile() {}

void GameTile::PushObject(GameObject* obj) {
	objects_here_.insert(obj);
}

void GameTile::RemoveObject(GameObject* obj) {
	objects_here_.erase(obj);
}

void GameTile::SetVisibility(bool visibility) {
    node_->effect().set_visible(visibility);
    for(auto it = objects_here_.begin(); it != objects_here_.end(); ++it) {
        //TODO: fix
        //(*it)->graphic_component()->SetVisibility(visibility);
    }
}

} // namespace base
} // namespace game