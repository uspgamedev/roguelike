
// Header File
#include "game/component/graphic_rectangular.h"

// External Dependencies
#include <cmath>
#include <ugdk/base/resourcemanager.h>
#include <ugdk/graphic/drawable/texturedrectangle.h>
#include <ugdk/graphic/node.h>
#include <ugdk/math/integer2D.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gamecontroller.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/shape_rectangular.h"

// Using
using std::set;
using std::string;
using ugdk::base::ResourceManager;
using ugdk::graphic::TexturedRectangle;
using ugdk::Vector2D;
using ugdk::math::Integer2D;
using game::base::GameController;
using game::base::GameObject;
using game::base::GameTile;

namespace game {
namespace component {

GraphicRectangular::GraphicRectangular(GameObject* owner, const string& visual_representation, double zindex)
  : super(owner, visual_representation, zindex) {
    TexturedRectangle* rect = new TexturedRectangle( ResourceManager::GetTextureFromFile("images/"+visual_representation+".png") );
    rect_size_ = rect->size();
    node_->set_drawable(rect);
}
GraphicRectangular::~GraphicRectangular() {}

void GraphicRectangular::Update(double) {}

void GraphicRectangular::NodeLogic(const set<Integer2D>& occupying_tiles) {
	const GameController* gamecontroller = GameController::reference();
    
    Integer2D dimensions = static_cast<ShapeRectangular*>(owner_->shape_component())->dimensions();
    dimensions.Multiply(GameController::TILE_SIZE);
    node_->modifier()->set_scale( Vector2D(dimensions) / rect_size_.x );
	node_->modifier()->set_offset( gamecontroller->Tile(*(occupying_tiles.begin()))->node()->modifier()->offset() );
}

} // namespace component
} // namespace game