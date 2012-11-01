#ifndef ROGUELIKE_COMPONENT_GRAPHIC_RECTANGULAR_H_
#define ROGUELIKE_COMPONENT_GRAPHIC_RECTANGULAR_H_

// Inheritance
#include "game/component/graphic.h"

// External Dependencies
#include <set>
#include <ugdk/math/vector2D.h>

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/math.h>
#include "game/base.h"

namespace game {
namespace component {

class GraphicRectangular : public Graphic {
  typedef Graphic super;
  public:
    GraphicRectangular(game::base::GameObject* owner, const std::string& visual_representation, double zindex);
    ~GraphicRectangular();

    void Update(double dt);
	void NodeLogic(const std::set<ugdk::math::Integer2D>& occupying_tiles);

    const ugdk::Vector2D& rect_size() const { return rect_size_; }

  private:
    ugdk::Vector2D rect_size_;
};

} // namespace component
} // namespace game

#endif // ROGUELIKE_COMPONENT_GRAPHIC_RECTANGULAR_H_