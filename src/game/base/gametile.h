#ifndef ROGUELIKE_BASE_GAMETILE_H_
#define ROGUELIKE_BASE_GAMETILE_H_

// Inheritance
// (none)

// External Dependencies
#include <set> // template class
#include <ugdk/math/integer2D.h> // coords_

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/ui.h>
#include "game/base.h"

namespace game {
namespace base {

class GameTile {
  // Lacks operator=
  GameTile& operator=(const GameTile&);

  public:
	GameTile(const ugdk::math::Integer2D& coords);
    GameTile(int x, int y);
	~GameTile();

	ugdk::ui::Node* node() const { return node_; }

	void PushObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
    void SetVisibility(bool visibility);
	
	int x() const { return coords_.x; }
	int y() const { return coords_.y; }

    const ugdk::math::Integer2D& coords() const { return coords_; }

	ugdk::ui::Node* node() { return node_; }
    
    const std::set<GameObject*>& objects_here() const { return objects_here_; }
          std::set<GameObject*>& objects_here()       { return objects_here_; }

  private:
	const ugdk::math::Integer2D coords_;

	ugdk::ui::Node* node_;
	std::set<GameObject*> objects_here_;
	ugdk::ui::Drawable* ground_;

};

} // namespace base
} // namespace game

#endif // ROGUELIKE_BASE_GAMETILE_H_