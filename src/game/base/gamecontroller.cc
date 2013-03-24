
// Header File
#include "game/base/gamecontroller.h"

// External Dependencies
#include <cstdlib>
#include <queue>
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
#include "game/component/sound.h"

// Using
using std::list;
using std::set;
using std::vector;
using ugdk::Engine;
using ugdk::action::GenericTask;
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

GameController::GameController() : super(), current_tick_(0), monster_spawn_counter_(0), map_size_(50, 40),
                                   hero_(nullptr), actors_(), time_since_beggining_(0.0) {
	TEXT_MANAGER()->AddFont("MAH FONTI", "fonts/FUTRFW.TTF", 15, 0, 0);
}

GameController::~GameController() {
    if(hero_) delete hero_;
    reference_ = nullptr;
}

void GameController::Spawn() {
    //TODO: fix monster AI and spawning times so that this doesn't lag as much.
    if(monster_spawn_counter_ > 0)
        return;
    monster_spawn_counter_++;

    ObjectBuilder objb = ObjectBuilder();
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
        actors_.push_back(game_object);
}

bool GameController::TilesNeededBlackout(GameObject* owner) {
    if(!needs_blackout_) return false;
    if(owner == hero_)
        BlackoutTiles();
    return true;
}

void GameController::BlackoutTiles() {
    for(auto j = tiles_.begin(); j != tiles_.end(); ++j)
        for(auto i = (*j).begin(); i != (*j).end(); ++i)
            (*i)->SetVisibility(false);
    needs_blackout_ = false;
}

void GameController::ShowTileAsVisible(const Integer2D& tile) {
    Tile(tile)->SetVisibility(true);
}

void GameController::ShowHeroTilesAsVisible() {
    auto tiles_to_show = hero_->vision_component()->visible_tiles();
    for(auto tt = tiles_to_show.begin(); tt != tiles_to_show.end(); ++tt)
        ShowTileAsVisible(*tt);
}

void GameController::RemoveActor(GameObject* actor) {
    this->RemoveEntity(actor);
}

void GameController::PropagateSound(const Integer2D& origin, int noise_level) {
    std::vector<std::vector<int>> map;
    map.resize(map_size_.x);

    for(int i = 0; i < map_size_.x ; ++i)
        map[i].resize(map_size_.y);
    for(int i = 0; i < map_size_.x ; ++i)
        for(int j = 0; j < map_size_.y ; ++j)
            map[i][j] = 0;
    map[origin.x][origin.y] = noise_level;

    std::queue<Integer2D> targets;
    std::queue<int>       noise;
    targets.push(origin);
    noise.push(noise_level);

    while(!targets.empty()) {
        Integer2D tile = targets.front();
        int tile_noise = noise.front();
        targets.pop();
        noise.pop();

        for(int i = -1; i < 2; ++i) {
            for(int j = -1; j < 2; ++j) {
                if(i == 0 && j == 0)
                    continue;
                if( map[tile.x + i][tile.y + j] < tile_noise )
                    map[tile.x + i][tile.y + j] = tile_noise;
                else
                    continue;
                const std::set<GameObject*>& obj_list = ObjectsAt(tile + Integer2D(i, j));
                //TODO: make work
                /*for(auto it = obj_list.begin(); it != obj_list.end(); ++it)
                    if((*it)->sound_component())
                        if((*it)->sound_component()->TryListen(tile_noise))
                            (*it)->TryTarget(*/
            }
        }
    }
}

const set<GameObject*>& GameController::ObjectsAt(const Integer2D& coords) {
    return Tile(coords)->objects_here();
}

void GameController::AdjustCamera() {
    if(hero_ == nullptr) return;

    //TODO: const
    Engine* engine = Engine::reference();
    const Vector2D& window_size = engine->window_size();

    int camera_x = (*hero_->shape_component()->occupying_tiles().begin()).get_x()*GameController::TILE_SIZE.x;
    int camera_y = (*hero_->shape_component()->occupying_tiles().begin()).get_y()*GameController::TILE_SIZE.y;
    ugdk::math::Integer2D camera_offset = ugdk::math::Integer2D(camera_x, camera_y);
    ugdk::Vector2D offset = ugdk::Vector2D(- camera_x + window_size.x/2, - camera_y + window_size.y/2);
    this->content_node()->modifier()->set_offset(offset);
}

} // namespace base
} // namespace game