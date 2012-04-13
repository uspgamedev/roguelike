#ifndef BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_
#define BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_

// Inheritance
#include "game/components/shape.h"

// External Dependencies
#include <ugdk/math/vector2D.h> // needed for dimensions_

// Internal Dependencies
#include "game/action/movement.h"   // needed for Movement::Direction

// Forward Declarations
#include "game/base.h"

namespace game {
namespace component {

class ShapeRectangular : public Shape {
  typedef Shape super;
  public:
    ShapeRectangular(size_t size_x = 1, size_t size_y = 1, size_t size_class = 10)
      : super(size_class),
        dimensions_(ugdk::Vector2D(size_x,size_y)) {}
    ~ShapeRectangular() {}

    game::base::GameTile* PlaceAt(game::base::GameTile* destination);
    game::base::GameTile* Move(game::action::Movement& mov);
    game::base::GameTile* Step(game::action::Movement::Direction dir);

    const ugdk::Vector2D& dimensions() const { return dimensions_; }

  private:
    ugdk::Vector2D dimensions_;
};

} // namespace component
} // namespace game

#endif // BADGAME_COMPONENT_SHAPE_RECTANGULAR_H_