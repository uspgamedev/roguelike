#ifndef BADGAME_BASE_GAMEOBJECT_H_
#define BADGAME_BASE_GAMEOBJECT_H_

// Inheritance
#include <ugdk/action/entity.h>

// External Dependencies
#include <list>                 // template class

#include <ugdk/math/vector2D.h> // needed for ???

// Forward Declarations
#include <ugdk/time.h>
#include "game/base.h"
#include "game/component.h"

namespace game {
namespace base {

class GameObject : public ugdk::Entity {
  typedef ugdk::Entity super;
  public:
    GameObject(size_t scale_x, size_t scale_y, component::Graphic*, component::Controller* controller, component::Collision* collision, component::Damageable* = nullptr);
    ~GameObject();

    void Initialize();

    void Update(double dt);

	void UpdateNode();

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Controller* controller_component() { return controller_component_; }
    component::Damageable* damageable_component() { return damageable_component_; }
	component::Collision*   collision_component() { return  collision_component_; }

    void Die() { dead_ = true; }
    bool dead() const { return dead_; }

    //GameController* game_controller() { return game_controller_; }
    //void set_game_controller(GameController* game) { game_controller_ = game; }

    void set_timed_life(ugdk::time::TimeAccumulator* timed_life) { timed_life_ = timed_life; }

          std::list<GameTile*>& occupying_tiles()       { return occupying_tiles_; };
    const std::list<GameTile*>& occupying_tiles() const { return occupying_tiles_; };

    const ugdk::Vector2D& dimensions() const { return dimensions_; }

  private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
    component::Collision*   collision_component_;
    component::Damageable* damageable_component_;
    
    ugdk::time::TimeAccumulator* timed_life_;
    bool dead_;
	std::list<GameTile*> occupying_tiles_;

private:
    ugdk::Vector2D dimensions_;

};

} // namespace base
} // namespace game

#endif // BADGAME_BASE_GAMEOBJECT_H_