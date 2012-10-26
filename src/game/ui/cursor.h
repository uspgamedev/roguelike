#ifndef ROGUELIKE_UI_CURSOR_H_
#define ROGUELIKE_UI_CURSOR_H_

// Inheritance
// (none)

// External Dependencies
#include <ugdk/math/integer2D.h> // tile_

// Internal Dependencies
// (none)

// Forward Declarations
#include <ugdk/graphic.h>
#include "game/base.h"

namespace game {
namespace ui {

class Cursor {
  public:
    Cursor();
    ~Cursor() {}

    ugdk::math::Integer2D tile() const { return tile_; }
    void ChangeTile(const ugdk::math::Integer2D& tile);
    void ChangeTile(int x, int y) { ChangeTile(ugdk::math::Integer2D(x,y)); }

    bool IsActive();
    void ToggleActive();

  protected:
    ugdk::math::Integer2D tile_;
    ugdk::graphic::Modifier* node_modifier_;
};

} // namespace ui
} // namespace game

#endif // ROGUELIKE_UI_CURSOR_H_