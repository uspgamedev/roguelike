#ifndef ROGUELIKE_BASE_GAMECONTROLLER_H_
#define ROGUELIKE_BASE_GAMECONTROLLER_H_

// Inheritance
#include <ugdk/action/scene.h>

// External Dependencies
#include <cassert>
#include <list>                  // template class, also needed for push_back(-)
#include <set>
#include <vector>                // template class, also needed for size(-)
#include <ugdk/math/integer2D.h> // needed for Tile
#include <ugdk/math/vector2D.h>  // needed for map_size_

// Internal Dependencies
#include "game/action/time/timemanager.h"

// Forward Declarations
#include "game/base.h"

namespace game {
namespace base {

class GameController : public ugdk::action::Scene {
  typedef ugdk::action::Scene super;
  static GameController* reference_;

  public:
    static GameController* reference();
    ~GameController();


    void AddGameObject(GameObject* game_object);

    const ugdk::math::Integer2D& map_size() const { return map_size_; }

    bool TileOutOfBounds(int x, int y) const {
        return y < 0 || y >= (int)(tiles_.size()) || x < 0 || x >= (int)(tiles_[y].size());
    }
    bool TileOutOfBounds(const ugdk::math::Integer2D& coords) const {
        return TileOutOfBounds(coords.x, coords.y);
    }

    GameTile* Tile(int x, int y) const {
        if( !TileOutOfBounds(x,y) )
            return tiles_[y][x];
        return nullptr;
    }
    GameTile* Tile(const ugdk::math::Integer2D& coords) const {
        return Tile(coords.x, coords.y);
    }

    const std::set<GameObject*>& ObjectsAt(const ugdk::math::Integer2D& coords);
    const std::set<GameObject*>& ObjectsAt(int x, int y) { return ObjectsAt(ugdk::math::Integer2D(x,y)); }


    void RequireBlackout() { needs_blackout_ = true; }
    bool TilesNeededBlackout();
    void BlackoutTiles();
    void MarkVisible(const ugdk::math::Integer2D& tile);
    void PassTime(double dt) { time_since_beggining_ += dt; }
    void RemoveActor(GameObject* actor);

    void set_hero(GameObject* hero) { hero_ = hero; }

  private:
    GameController();
    
    void clearDeadGameObjects();
    void addPendingGameObjects();

    ugdk::math::Integer2D map_size_;
	std::vector< std::vector<GameTile*> > tiles_;

    GameObject* hero_;
    action::time::ObjectQueue actors_;
    
    double time_since_beggining_;
    bool needs_blackout_;
};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_GAMECONTROLLER_H_