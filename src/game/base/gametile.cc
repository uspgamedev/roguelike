// Header File
#include "gametile.h"

// External Dependencies
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/graphic/node.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/component/graphic.h"

// Using
using ugdk::math::Integer2D;
using ugdk::Vector2D;
using game::base::GameController;
using game::base::GameObject;
using ugdk::base::ResourceManager;
using ugdk::graphic::Node;
using ugdk::graphic::TexturedRectangle;

namespace game {
namespace base {

GameTile::GameTile(const Integer2D& coords) : coords_(coords), node_(new Node) {
	ground_ = new TexturedRectangle( ResourceManager::GetTextureFromFile("images/white.png") );
	node_->set_drawable(ground_);
    node_->modifier()->set_scale( Vector2D(GameController::TILE_SIZE) / ground_->width());
}
GameTile::GameTile(int x, int y) : coords_(x,y), node_(new Node) {
	ground_ = new TexturedRectangle( ResourceManager::GetTextureFromFile("images/white.png") );
	node_->set_drawable(ground_);
    node_->modifier()->set_scale( Vector2D(GameController::TILE_SIZE) / ground_->width());
}

GameTile::~GameTile() { 
	node_->set_drawable(ground_);
	delete node_;
}

void GameTile::PushObject(GameObject* obj) {
	objects_here_.insert(obj);
}

void GameTile::RemoveObject(GameObject* obj) {
	objects_here_.erase(obj);
}

void GameTile::SetVisibility(bool visibility) {
    node_->modifier()->set_visible(visibility);
    for(auto it = objects_here_.begin(); it != objects_here_.end(); ++it) {
        (*it)->graphic_component()->node()->modifier()->set_visible(visibility);
    }
}

} // namespace base
} // namespace game