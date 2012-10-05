
// Header File
#include "game/base/gamecontroller.h"

// External Dependencies
#include <cassert>
#include <cstdlib>
#include <set>
#include <ugdk/action/generictask.h>
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/text.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/textmanager.h>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/component/energy.h"
//#include "game/component/graphic.h"

// Using
using std::list;
using std::vector;
using ugdk::math::Integer2D;
using ugdk::Vector2D;

namespace game {
namespace base {

/*static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}*/

GameController* GameController::reference_ = nullptr;

GameController* GameController::reference() {
    return reference_ == nullptr ? (reference_ = new GameController()) : reference_;
}

static bool actor_less(const GameObject* a, const GameObject* b) {
    return a->energy_component()->Mean() < b->energy_component()->Mean();
}

GameController::GameController() : super(), map_size_(500.0, 500.0), hero_(nullptr), actors_(actor_less), time_since_beggining_(0.0) {
	TEXT_MANAGER()->AddFont("MAH FONTI", "fonts/FUTRFW.TTF", 15, 0, 0);

	Vector2D pos = Vector2D();
	for(int y = 0; y < 40; ++y) {
		vector<GameTile*> vect;
		pos.x = 0;
		for(int x = 0; x < 50; ++x) {
			GameTile* gt = new GameTile(x, y);
            gt->node()->set_zindex(-1.0);
			gt->node()->modifier()->set_offset(pos);
			content_node()->AddChild(gt->node());
			vect.push_back(gt);

			pos.x += GameTile::TILE_SIZE.x;
		}
		tiles_.push_back(vect);
		pos.y += GameTile::TILE_SIZE.y;
	}

    this->AddTask(new action::time::TimeManager(actors_));

    BlackoutTiles();   
}

GameController::~GameController() {
    if(hero_) delete hero_;
    reference_ = nullptr;
}

void GameController::AddGameObject(GameObject* game_object) {
    this->QueuedAddEntity(game_object);
    if( game_object == hero_ ) actors_.insert(hero_);
}

void GameController::BlackoutTiles() {
    for(auto j = tiles_.begin(); j != tiles_.end(); ++j)
        for(auto i = (*j).begin(); i != (*j).end(); ++i)
            (*i)->node()->modifier()->set_visible(false);
}

} // namespace base
} // namespace game