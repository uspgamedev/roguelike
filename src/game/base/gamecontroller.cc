
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
#include <ugdk/script/virtualobj.h>
#include <ugdk/script/scriptmanager.h>

// Internal Dependencies
#include "game/component/vision.h"
#include "game/base/gameobject.h"
#include "game/base/gametile.h"
#include "game/builder/objectbuilder.h"
#include "game/component/energy.h"
#include "game/component/shape.h"

// Using
using std::list;
using std::set;
using std::vector;
using ugdk::math::Integer2D;
using ugdk::script::VirtualObj;
using ugdk::Vector2D;
using game::builder::ObjectBuilder;

namespace game {
namespace base {

/*static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}*/
    
const Integer2D GameController::TILE_SIZE = Integer2D(23, 23);

GameController* GameController::reference_ = nullptr;

GameController* GameController::reference() {
    return reference_ == nullptr ? (reference_ = new GameController()) : reference_;
}

static bool actor_less(const GameObject* a, const GameObject* b) {
    double mean_a = a->energy_component()->Mean();
    double mean_b = b->energy_component()->Mean();
    return mean_a > mean_b || ( mean_a == mean_b && a < b );
}

GameController::GameController() : super(), monster_spawn_counter_(0), map_size_(50, 40), hero_(nullptr),
                                   actors_(actor_less), time_since_beggining_(0.0) {
	TEXT_MANAGER()->AddFont("MAH FONTI", "fonts/FUTRFW.TTF", 15, 0, 0);
}

GameController::~GameController() {
    if(hero_) delete hero_;
    reference_ = nullptr;
}

void GameController::Spawn() {
    monster_spawn_counter_++;
    if(monster_spawn_counter_ < 250)
        return;
    monster_spawn_counter_ = 0;
    ObjectBuilder& objb = ObjectBuilder();
    GameObject* new_enemy = objb.BuildEnemy();
    int x, y;
    do {
        x = rand()%60;
        y = rand()%60;
    } while(!new_enemy->shape_component()->TryPlace(Integer2D(x,y)));
    new_enemy->shape_component()->PlaceAt(Integer2D(x,y));
    AddGameObject(new_enemy);
}

void GameController::AddGameObject(GameObject* game_object) {
    this->QueuedAddEntity(game_object);
    if( game_object->controller_component() != nullptr )
        actors_.insert(game_object);
}

bool GameController::TilesNeededBlackout() {
    if(!needs_blackout_) return false;
    BlackoutTiles();
    return true;
}

void GameController::BlackoutTiles() {
    for(auto j = tiles_.begin(); j != tiles_.end(); ++j)
        for(auto i = (*j).begin(); i != (*j).end(); ++i)
            (*i)->SetVisibility(false);
    needs_blackout_ = false;
}

void GameController::MarkVisible(GameObject* viewer, const Integer2D tile) {
    if(viewer == hero_)
        Tile(tile)->SetVisibility(true);
    else
        viewer->vision_component()->see_tile(tile);
}

void GameController::RemoveActor(GameObject* actor) {
    actors_.erase(actor);
}

const set<GameObject*>& GameController::ObjectsAt(const Integer2D& coords) {
    return Tile(coords)->objects_here();
}

} // namespace base
} // namespace game